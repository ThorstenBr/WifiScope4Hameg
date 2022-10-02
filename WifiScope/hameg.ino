/*
 hameg.ino - Hameg oscilloscope RS232 interface.

 Copyright (c) 2022 Thorsten Brehm.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "hameg.h"

extern const PROGMEM char* const VoltageStrings[];
extern void bin2HexStr(const char* pData, UInt32 Size, std::string& str);

#if 0
void debugError(UInt32 id)
{
  digitalWrite(BUILTIN_LED, HIGH);
  delay(2000);
  while (id>0)
  {
    digitalWrite(BUILTIN_LED, LOW);
    delay(500);
    digitalWrite(BUILTIN_LED, HIGH);
    delay(500);
    id--;
  }
  delay(2000);
}
#endif

static Hameg* s_pSingleton = NULL;
    
void Hameg::setup(HardwareSerial* pSerial)
{
  if (!s_pSingleton)
    s_pSingleton = new Hameg(pSerial);
}

Hameg* Hameg::getSingleton()
{
  return s_pSingleton;
}

Hameg::Hameg(HardwareSerial* pSerial) :
 m_pSerial(pSerial),
 m_BufferByteCount(0),
 m_Connected(false)
{
}

bool Hameg::connect()
{
  // clear input buffer
  while (m_pSerial->available())
  {
    while (m_pSerial->available())
    {
      m_pSerial->read();
    }
    // wait a bit, maybe more characters pending?
    delay(10);
  }

  m_Connected = true;

  _write(1, "\x20");
  delay(10); // allow some time for baudrate detection
  _write(1, "\x0d");    // init/set baudrate

  if (!_read(3, m_Buffer, 2000)) // read response
  {
    // init failed
    debugPrint("\nERROR: Init response timeout...\n");
    debugPrintValue(m_BufferByteCount);
    disconnect(); // safety: if the device has still received our request
    return false;
  }

  if (strcmp(m_Buffer, "0\x0d\n")!=0)
  {
    debugPrint("\nERROR: Invalid init response received:\n");
    debugPrintValue((UInt32)m_Buffer[0]);
    debugPrintValue((UInt32)m_Buffer[1]);
    debugPrintValue((UInt32)m_Buffer[2]);
    disconnect();
    return false;
  }

  if (m_DeviceId.length() == 0)
  {
    m_DeviceId = getDeviceID();
  }
  if (m_FrontControllerVersion.length() == 0)
  {
    m_FrontControllerVersion = getFrontControllerVersion();
  }

  //debugPrint("Init OK...\n");
  return true;
}

bool Hameg::disconnect()
{
  if (!m_Connected)
    return true;
  m_Connected = false;
  bool ok = _command(5, "RM0\x0d\n", 3);
  return ok;
}
    
void Hameg::_write(UInt32 ByteCount, const char* pData)
{
  while (ByteCount>0)
  {
    UInt32 Count = ByteCount;
    // hameg device only has an input buffer of 8 characters...
    if (Count>8)
      Count = 8;
    Serial.write(pData, Count);
    Serial.flush();
    pData += Count;
    ByteCount -= Count;
    if (ByteCount>0)
      delay(1); // brief delay
  }
}

bool Hameg::_read(UInt32 ByteCount, char* pBuffer, UInt32 TimeoutMs)
{
  if (pBuffer == NULL)
    pBuffer = m_Buffer;
  Serial.setTimeout(TimeoutMs);
  UInt32 r = Serial.readBytes(pBuffer, ByteCount);
  if (r<=ByteCount)
    pBuffer[r] = 0;
  m_BufferByteCount = r;
  return (r == ByteCount);
}

bool Hameg::_command(UInt32 WriteByteCount, const char* pData, UInt32 ReadByteCount, char* pBuffer, UInt32 TimeoutMs)
{
  _write(WriteByteCount, pData);
  return _read(ReadByteCount, pBuffer, TimeoutMs);
}

bool Hameg::_hasPrefix(const char* pPrefix, const char* pBuffer)
{
  if (!pBuffer)
    pBuffer = m_Buffer;
  size_t l = strlen(pPrefix);
  return (strncmp(pPrefix, pBuffer, l)==0);
}

bool Hameg::setCH(UInt8 Channel, UInt8 VoltDiv, UInt8 Enabled, UInt8 AC, UInt8 Inverted, UInt8 GND)
{
  char Buf[6];
  sprintf(Buf, "CH%hhu=X", Channel);
  if (Enabled)
    Enabled = 0x10;
  if (Inverted)
    Inverted = 0x20;
  if (AC)
    AC = 0x40;
  if (GND)
    GND = 0x80;
  Buf[4] = VoltDiv|Enabled|Inverted|AC|GND;
  if (!_command(5, Buf, 3))
    return false;
  return true;
}

bool Hameg::setTBA(UInt8 TimeDiv, UInt8 Single, UInt8 ZInput)
{
  char Buf[6];
  sprintf(Buf, "TBA=X");
  if (Single)
    Single = 0x20;
  if (ZInput)
    ZInput = 0x80;
  Buf[4] = TimeDiv|Single|ZInput;
  if (!_command(5, Buf, 3))
    return false;
  return true;
}

bool Hameg::setStoreMode(UInt8 Mode, UInt8 PreTrigger, UInt8 Ref1, UInt8 Ref2)
{
  char Buf[10];
  sprintf(Buf, "STRMODE=X");
  if (Ref1)
    Ref1 = 0x40;
  if (Ref2)
    Ref2 = 0x80;
  PreTrigger = (PreTrigger & 7) << 3;
  Buf[8] = Mode|PreTrigger|Ref1|Ref2;
  if (!_command(9, Buf, 3, NULL, 1000))
    return false;
  return true;
}

bool Hameg::setTrigger(UInt8 FallingEdge, UInt8 PeakPeak, UInt8 Norm, UInt8 Coupling)
{
  char Buf[7];
  sprintf(Buf, "TRIG=X");
  if (FallingEdge)
    FallingEdge = 0x80;
  if (PeakPeak)
    PeakPeak = 0x20;
  if (Norm)
    Norm = 0x10;
  Coupling &= 0x7;
  Buf[5] = FallingEdge|PeakPeak|Norm|Coupling;
  if (!_command(6, Buf, 3, NULL, 1000))
    return false;
  return true;
}

bool Hameg::autoSet()
{
  if (!_command(9, "AUTOSET\x0d\n", 3, NULL, 4000))
    return false;
  return true;
}

bool Hameg::resetSingle()
{
  if (!_command(5, "RES\x0d\n", 3))
    return false;
  return true;
}

const char* Hameg::getDeviceID()
{
  if (!_command(3, "ID?", 3+27))
    return NULL;
  if (!_hasPrefix("ID:"))
    return NULL;
  
  m_Buffer[3+27-2] = 0; // drop \r\n at the end of the ID
  return &m_Buffer[3];
}

const char* Hameg::getFrontControllerVersion()
{
  if (!_command(5, "VERS?", 5+15))
    return NULL;
  if (!_hasPrefix("VERS:"))
    return NULL;

  UInt8 Size = 5+15;
  // There is usually a \r\n at the end of the reported version.
  // However, the protocol does not specify a line-ending (unlike for the "ID?" command),
  // so these bytes are part of the returned payload - and we cannot be sure if all
  // devices return a \r\n.
  // => So we just add a check and cut it off, if found...
  if (m_Buffer[Size-1] == '\n')
    Size--;
  if (m_Buffer[Size-1] == '\r')
    Size--;
  m_Buffer[Size] = 0; // drop \r\n at the end
  return &m_Buffer[5];
}

// Hold Wave Form (signal capture is paused?)
bool Hameg::getHoldWaveForm()
{
  if (!_command(7, "HLDWFM?", 7+1))
    return false;
  if (!_hasPrefix("HLDWFM:"))
    return false;
  return (m_Buffer[7] == '1');
}

bool Hameg::setHoldWaveForm(UInt8 Hold)
{
  char Buf[9];
  sprintf(Buf, "HLDWFM=%hhu", (Hold) ? 1 : 0);
  if (!_command(8, Buf, 3))
    return false;
  return true;
}

UInt8* Hameg::getChannelWaveForm(UInt8 Channel)
{
    char Cmd[16]={0};
    if ((Channel==1)||(Channel==2))
      sprintf(Cmd, "RDWFM%hhu:", Channel); // "RDWFM1:\x00\x00\x00\x08"
    else
    if ((Channel==3)||(Channel==4))
      sprintf(Cmd, "RDREF%hhu:", Channel-2); // "RDWFM1:\x00\x00\x00\x08"
    else
      return NULL;

    Cmd[10] = '\x08';
    if (!_command(11, Cmd, 7+2*2+2048, m_Buffer, 2000))
      return NULL;
    if (!_hasPrefix(Cmd))
      return NULL;
      
    return (UInt8*) &m_Buffer[11];
}

bool Hameg::getJsonWaveForm(UInt8 Channel, std::string& json)
{
  UInt8* pData = getChannelWaveForm(Channel);
  if (!pData)
    return false;

  switch(Channel)
  {
    case 1:
      json.append("\"channel1\": \"");
      break;
    case 2:
      json.append("\"channel2\": \"");
      break;
    case 3:
      json.append("\"reference1\": \"");
      break;
    case 4:
      json.append("\"reference2\": \"");
      break;
    default:
      return false;
  }

  // convert raw binary data to hex string
  bin2HexStr(pData, 2048, json);

  json.append("\"");
  return true;
}

UInt8* Hameg::getReferenceWaveForm(UInt8 RefChannel)
{
  return getChannelWaveForm(RefChannel+2);
}

bool Hameg::getReferenceWaveForm(UInt8 Channel, std::string& json)
{
  return getJsonWaveForm(Channel+2, json);
}

bool Hameg::getCsvWaveForm(UInt8 Channel, std::string& csv)
{
  UInt8* pData = getChannelWaveForm(Channel);
  if (!pData)
    return false;

  {
    char s[256];
    UInt32 p=0;
    int r = sprintf(s, "y\n");
    if (r>0)
      p += r;
    for (UInt32 x=0;x<2048;x++)
    {
      r = sprintf(&s[p], "%u\n", pData[x]);
      if (r>0)
        p += r;
      
      if (p+(3+1+1)>=256)
      {
        csv.append(s);
        p=0;
        s[0] = 0;
      }
    }
    csv.append(s);
  }
  return true;
}

bool Hameg::readDDF(UInt8 pDDF[14])
{
  if (!_command(4, "DDF?", 4+14))
    return false;
  if (!_hasPrefix("DDF:"))
    return false;
  memcpy(pDDF, &m_Buffer[4], 14);
  return true;
}

bool Hameg::readDDF1(UInt16 pDDF1[8])
{
  if (!_command(5, "DDF1?", 5+16))
    return false;
  if (!_hasPrefix("DDF1:"))
    return false;
  memcpy(pDDF1, &m_Buffer[5], 16);
  return true;
}

bool Hameg::readRODDF(UInt16 pRODDF[5])
{
  if (!_command(6, "RODDF?", 6+10))
    return false;
  if (!_hasPrefix("RODDF:"))
    return false;
  memcpy(pRODDF, &m_Buffer[6], 10);
  return true;
}

bool Hameg::getTriggerStatus(UInt8* pTriggerStatus)
{
  if (!_command(7, "TRGSTA?", 7+1))
    return false;
  if (!_hasPrefix("TRGSTA:"))
    return false;

  UInt8 TriggerStatus = m_Buffer[7];

  // See protocol spec: depending on FC version the result is either binary or ASCII encoded.
  // => we convert '0'..'9' to binary.
  if ((TriggerStatus >= '0')&&(TriggerStatus <= '9'))
    TriggerStatus -= '0';

  *pTriggerStatus = TriggerStatus;
  return true;
}

UInt32 hameg_mV(UInt8 VoltDiv)
{
  UInt32 Voltage_mV = 10;
  UInt8 Step = 0;
  while (VoltDiv-- > 0)
  {
    Voltage_mV *= 2;
    if (++Step == 2)
    {
        Voltage_mV += (Voltage_mV/4);
    }
    if (Step==3)
        Step = 0;
  }
  return Voltage_mV;
}

ULong64 hameg_nS(UInt8 TimeDiv)
{
  ULong64 Timebase_nS = 50;
  UInt8 Step = 0;
  while (TimeDiv-- > 0)
  {
        Timebase_nS *= 2;
        if (++Step == 3)
        {
          Timebase_nS += Timebase_nS/4;
          Step=0;
        }
  }
  return Timebase_nS;
}

std::string getChannelDDFData(UInt8 ChannelId, UInt8* pDDF, UInt16* pDDF1)
{
  UInt8 Ch = pDDF[ChannelId-1];
  UInt8 VoltDiv = Ch & 0xf;

  UInt32 Voltage_mV = hameg_mV(VoltDiv);

  UInt8 Enabled  = (Ch & 0x10)>0;
  UInt8 Inverted = (Ch & 0x20)>0;
  UInt8 AC       = (Ch & 0x40)>0;
  UInt8 GND      = (Ch & 0x80)>0;
  UInt8 Var      = pDDF[(ChannelId == 1) ? 9 : 8]; // Ch1: byte 9, Ch2: byte 8

  UInt8 Probe = pDDF[2];
  if (ChannelId==2)
    Probe >>= 4;
  Probe = (Probe&0x4) ? 10 : 1; // 0x4= 1:10 probe, 0x0: 1:1 probe

  // Y Position
  Int16 YPos = (Int16) (ChannelId==2) ? pDDF1[3] : pDDF1[4]; // yes, Y2Pos is at 3 and Y1Pos at 4...
  
  char Buf[256];
  if (snprintf(Buf, sizeof(Buf),
          "\"ch%hhu\": {\n"
          "\"voltDiv\": \"%s\",\n"
          "\"voltDiv_mV\": %u,\n"
          "\"enabled\": %hhu,\n"
          "\"inverted\": %hhu,\n"
          "\"ac\": %hhu,\n"
          "\"gnd\": %hhu,\n"
          "\"probe\": \"1:%hhu\",\n"
          "\"var\": %hhu,\n"
          "\"yPosition\": %hi"
          "}",
          ChannelId,
          VoltageStrings[VoltDiv],
          Voltage_mV,
          Enabled,
          Inverted,
          AC,
          GND,
          Probe,
          Var,
          YPos) >= sizeof(Buf))
    {
      // string too long
      Buf[0] = 0;            
    }
          
  return std::string(Buf);
}

std::string getTriggerDDF(UInt8* pDDF, UInt16* pDDF1, UInt8 TriggerStatus)
{
  UInt8 b = pDDF[2];
  
  UInt8 Add  = (b & 0x08)>0;
  UInt8 Chop = (b & 0x10)>0;
  UInt8 BWL  = (b & 0x20)>0;
  UInt8 AltTrig = (b & 0x80)>0;
  UInt8 SingleShot = (pDDF[3] & 0x20)>0;
  UInt8 ZInput = (pDDF[3] & 0x80)>0;
  UInt8 TBA = pDDF[3] & 0x1f;
  ULong64 TBA_nS = hameg_nS(TBA);

  // Trigger Source
  const char* pTriggerSrc;
  if (AltTrig)
    pTriggerSrc = "CH1,CH2"; // alternating trigger source
  else
  switch(b&0x3)
  {
    case 0x0:
      pTriggerSrc = "CH1";
      break;
    case 0x1:
      pTriggerSrc = "CH2";
      break;
    default:
      pTriggerSrc = "EXT";
      break;
  }

  // TRIG byte
  b = pDDF[6];
  const char* pTriggerType;
  switch(b&7)
  {
    case 0:pTriggerType="AC";break;
    case 1:pTriggerType="DC";break;
    case 2:pTriggerType="HF";break;
    case 3:pTriggerType="LF";break;
    case 4:pTriggerType="TVLine";break;
    case 5:pTriggerType="TVField";break;
    case 6:pTriggerType="LINE";break;
    case 7:pTriggerType="?";break;
  }
  UInt8 Norm     = (b & 0x10)>0;
  UInt8 PeakPeak = (b & 0x20)>0;
  UInt8 Negative = (b & 0x80)>0;

  // STRMODE byte
  b = pDDF[7];
  const char* pStoreMode="";
  switch(b & 7)
  {
    case 0:pStoreMode = "RFR";break;
    case 1:pStoreMode = "SGL";break;
    case 2:pStoreMode = "ROL";break;
    case 3:pStoreMode = "ENV";break;
    case 4:pStoreMode = "AVR";break;
    case 5:pStoreMode = "?5?";break;
    case 6:pStoreMode = "?6?";break;
    case 7:pStoreMode = "?7?";break;
  }
  if (SingleShot)
    pStoreMode = "SGL";

  UInt8 PreTrigger = (b>>3)&0x7;
  Int8 PreTriggerP = -75;
  {
    UInt8 v = PreTrigger;
    while (v-->0)
    {
      PreTriggerP += 25;
    }
  }

  // HOLD OFF byte
  UInt8 HoldOff = pDDF[11];

  // X Position
  Int16 XPos  = (Int16) pDDF1[2];
  
  // Trigger Level
  UInt16 TriggerLevelA = pDDF1[0];
  UInt16 TriggerLevelB = pDDF1[5];
  Int16  DelPos        = (Int16) pDDF1[7];

  char Buf[512];
  if (snprintf(Buf, sizeof(Buf),
          "\"trigger\": {\n"
          "\"status\": %hhu,\n"
          "\"source\": \"%s\",\n"
          "\"preTrigger\": \"%hhi%%\",\n"
          "\"singleShot\": %hhu,\n"
          "\"coupling\": \"%s\",\n"
          "\"norm\": %hhu,\n"
          "\"pp\": %hhu,\n"
          "\"negative\": %hhu,\n"
          "\"holdOff\": %hhu,\n"
          "\"levelA\": %hu,\n"
          "\"levelB\": %hu,\n"
          "\"delayPosition\": %hi,\n"
          "\"storeMode\": \"%s\"\n"
          "},\n"

          "\"add\": %hhu,\n"
          "\"chop\": %hhu,\n"
          "\"bwl\": %hhu,\n"
          "\"tba\": %hhu,\n"
          "\"tba_nS\": %llu,\n"
          "\"zInput\": %hhu,\n"
          "\"xPosition\": %hi"
          ,
          TriggerStatus,
          pTriggerSrc,
          PreTriggerP,
          SingleShot,
          pTriggerType,
          Norm,
          PeakPeak,
          Negative,
          HoldOff,
          TriggerLevelA,
          TriggerLevelB,
          DelPos,
          pStoreMode,
          
          Add,
          Chop,
          BWL,
          TBA,
          TBA_nS,
          ZInput,
          XPos
          ) >= sizeof(Buf))
  {
    // string too long
    Buf[0] = 0;
  }
  return std::string(Buf);
}

void ddf2json(UInt8* pDDF, UInt16* pDDF1, UInt8 TriggerStatus, std::string& json)
{
  json.append(getChannelDDFData(1, pDDF, pDDF1));
  json.append(",\n");
  json.append(getChannelDDFData(2, pDDF, pDDF1));
  json.append(",\n");
  json.append(getTriggerDDF(pDDF, pDDF1, TriggerStatus));
}

bool Hameg::getJSONData(std::string& json)
{
  UInt8  DDF[14];
  UInt16 DDF1[8];
  UInt8  TriggerStatus;
  
  if (!readDDF(DDF))
    return false;
  if (!readDDF1(DDF1))
    return false;
  if (!getTriggerStatus(&TriggerStatus))
    return false;
  json = "{\n";

  {
    char Buf[256];
    snprintf(Buf, sizeof(Buf),
             "\"deviceId\": \"%s\",\n"
             "\"FcVersion\": \"%s\",\n",
             m_DeviceId.c_str(),
             m_FrontControllerVersion.c_str());
    json.append(Buf);
    json.append("\"data\": {\n");

    bool HaveData = false;
    if (DDF[0] & 0x10) // CH1 enabled?
    {
      getJsonWaveForm(1, json);
      HaveData = true;
    }

    if (DDF[1] & 0x10) // CH2 enabled?
    {
      if (HaveData)
        json.append(",\n");
      getJsonWaveForm(2, json);
      HaveData = true;
    }

    if (DDF[7] & 0x40) // REF1 enabled?
    {
      if (HaveData)
        json.append(",\n");
      getReferenceWaveForm(1, json);
      HaveData = true;
    }

    if (DDF[7] & 0x80) // REF2 enabled?
    {
      if (HaveData)
        json.append(",\n");
      getReferenceWaveForm(2, json);
      HaveData = true;
    }

    json.append("\n},\n");
  }

  ddf2json(DDF, DDF1, TriggerStatus, json);

  json.append(",\n");
  if (getHoldWaveForm())
      json.append("\"hold\": 1");
  else
      json.append("\"hold\": 0");

  json.append("\n}\n");
}
