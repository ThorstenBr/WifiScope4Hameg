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
#include "strings.h"

// timeout after which the remote connection to the Hameg scope is
// automatically dropped (so the user can make manual changes)
#define HAMEG_REMOTE_MODE_TIMEOUT_MS 1000

extern void bin2HexStr(const char* pData, UInt32 Size, std::string& str);

#ifdef DEBUG_JSON
  // separating data with "\n" makes debugging the JSON output so much easier
  #define JSON_LF "\n"
#else
  // normal, compact JSON output to reduce overhead
  #define JSON_LF ""
#endif

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

void stripTrailingWhitespace(char* pString, UInt8 Size)
{
  for (UInt8 i=Size;i>0;i--)
  {
    if ((pString[i-1] != ' ')&&
        (pString[i-1] != '\n')&&
        (pString[i-1] != '\r')&&
        (pString[i-1] != '\t'))
    {
      break;
    }
    pString[i-1] = 0;
  }
}

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
 m_Connected(false),
 m_ConnectionTimeout(0)
{
}

bool Hameg::connect()
{
  // check if we're still connected
  if (m_Connected)
    return true;

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

  if (HAMEG_OK != _read(3, m_Buffer, 2000)) // read response
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

  if (DEBUG)
    debugPrint("Connected...\n");

  return true;
}

int Hameg::disconnect()
{
  if (!m_Connected)
    return true;
  m_Connected = false;
  int Status = _command(5, "RM0\x0d\n", 3);

  if (DEBUG)
  {
    DebugSerial.print("Disconnected... ");
    DebugSerial.println(Status);
  }

  return Status;
}

// automatically disconnec the scope after a timeout,
// when the remote interface was not used (allowing the user to make manual changes)
void Hameg::check()
{
  if (!m_Connected)
    return;

  // see if the remote interface hasn't been used for a while
  UInt32 Millis = millis()-m_ConnectionTimeout;
  if (Millis > HAMEG_REMOTE_MODE_TIMEOUT_MS)
    disconnect();
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

int Hameg::_read(UInt32 ByteCount, char* pBuffer, UInt32 TimeoutMs)
{
  if (pBuffer == NULL)
    pBuffer = m_Buffer;
  Serial.setTimeout(TimeoutMs);
  UInt32 r = Serial.readBytes(pBuffer, ByteCount);
  if (r<=ByteCount)
    pBuffer[r] = 0;
  m_BufferByteCount = r;
  if (r>0)
    m_ConnectionTimeout = millis();
  if (r == ByteCount)
    return HAMEG_OK;
  return HAMEG_REPLY_TIMEOUT;
}

int Hameg::_command(UInt32 WriteByteCount, const char* pData, UInt32 ReadByteCount, bool CheckStatusByte, char* pBuffer, UInt32 TimeoutMs)
{
  _write(WriteByteCount, pData);
  int Status = _read(ReadByteCount, pBuffer, TimeoutMs);
  if (Status != HAMEG_OK)
    return Status;
  if ((CheckStatusByte)&&(ReadByteCount == 3))
  {
    if (!pBuffer)
      pBuffer = m_Buffer;
    if ((pBuffer[0]>='0')and(pBuffer[0]<='9'))
      return pBuffer[0]-'0';
    return HAMEG_RESPONSE_CODE_ERROR;
  }
  return HAMEG_OK;
}

bool Hameg::_hasPrefix(const char* pPrefix, const char* pBuffer)
{
  if (!pBuffer)
    pBuffer = m_Buffer;
  size_t l = strlen(pPrefix);
  return (strncmp(pPrefix, pBuffer, l)==0);
}

int Hameg::setCH(UInt8 Channel, UInt8 VoltDiv, UInt8 Enabled, UInt8 AC, UInt8 Inverted, UInt8 GND)
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
  return _command(5, Buf, 3, true);
}

int Hameg::setTBA(UInt8 TimeDiv, UInt8 Single, UInt8 ZInput)
{
  char Buf[6];
  sprintf(Buf, "TBA=X");
  if (Single)
    Single = 0x20;
  if (ZInput)
    ZInput = 0x80;
  Buf[4] = TimeDiv|Single|ZInput;
  return _command(5, Buf, 3, true);
}

int Hameg::setStoreMode(UInt8 Mode, UInt8 PreTrigger, UInt8 Ref1, UInt8 Ref2)
{
  char Buf[10];
  sprintf(Buf, "STRMODE=X");
  if (Ref1)
    Ref1 = 0x40;
  if (Ref2)
    Ref2 = 0x80;
  PreTrigger = (PreTrigger & 7) << 3;
  Buf[8] = Mode|PreTrigger|Ref1|Ref2;
  return _command(9, Buf, 3, true, NULL, 1000);
}

int Hameg::setTrigger(UInt8 FallingEdge, UInt8 PeakPeak, UInt8 Norm, UInt8 Coupling)
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
  return _command(6, Buf, 3, true, NULL, 1000);
}

int Hameg::setVerticalMode(UInt8 AltTrigger, UInt8 Ch1_10_1, UInt8 Ch2_10_1, UInt8 Bwl, UInt8 Chop, UInt8 Add, UInt8 TriggerSource)
{
  char Buf[10];
  sprintf(Buf, "VERMODE=X");
  if (AltTrigger)
    AltTrigger = 0x80;
  if (Ch1_10_1)
    Ch1_10_1 = 0x40;
  if (Ch2_10_1)
    Ch2_10_1 = 0x4;
  if (Bwl)
    Bwl = 0x20;
  if (Chop)
    Chop = 0x10;
  if (Add)
    Add = 0x08;
  TriggerSource &= 3;
  Buf[8] = AltTrigger | Ch1_10_1 | Ch2_10_1 | Bwl | Chop | Add | TriggerSource;
  return _command(9, Buf, 3, true, NULL, 1000);
}

int Hameg::autoset()
{
  return _command(9, "AUTOSET\x0d\n", 3, true, NULL, 4000);
}

int Hameg::resetSingle()
{
  return _command(5, "RES\x0d\n", 3, true);
}

const char* Hameg::getDeviceID()
{
  if (HAMEG_OK != _command(3, "ID?", 3+27))
    return NULL;
  if (!_hasPrefix("ID:"))
    return NULL;

  // drop \r\n and whitespace at the end of the ID
  stripTrailingWhitespace(m_Buffer, 3+27);
  return &m_Buffer[3];
}

const char* Hameg::getFrontControllerVersion()
{
  if (HAMEG_OK != _command(5, "VERS?", 5+15))
    return NULL;
  if (!_hasPrefix("VERS:"))
    return NULL;

  // drop \r\n and whitespace at the end of the version
  stripTrailingWhitespace(m_Buffer, 5+15);
  return &m_Buffer[5];
}

// Hold Wave Form (signal capture is paused?)
bool Hameg::getHoldWaveForm()
{
  if (HAMEG_OK != _command(7, "HLDWFM?", 7+1))
    return false;
  if (!_hasPrefix("HLDWFM:"))
    return false;
  return (m_Buffer[7] == '1');
}

int Hameg::setHoldWaveForm(UInt8 Hold)
{
  char Buf[9];
  sprintf(Buf, "HLDWFM=%hhu", (Hold) ? 1 : 0);
  return _command(8, Buf, 3, true);
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
    if (HAMEG_OK != _command(11, Cmd, 7+2*2+2048, false, m_Buffer, 2000))
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
  if (HAMEG_OK != _command(4, "DDF?", 4+14))
    return false;
  if (!_hasPrefix("DDF:"))
    return false;
  memcpy(pDDF, &m_Buffer[4], 14);
  return true;
}

bool Hameg::readDDF1(UInt16 pDDF1[8])
{
  if (HAMEG_OK != _command(5, "DDF1?", 5+16))
    return false;
  if (!_hasPrefix("DDF1:"))
    return false;
  memcpy(pDDF1, &m_Buffer[5], 16);
  return true;
}

bool Hameg::readRODDF(UInt16 pRODDF[5])
{
  if (HAMEG_OK != _command(6, "RODDF?", 6+10))
    return false;
  if (!_hasPrefix("RODDF:"))
    return false;
  memcpy(pRODDF, &m_Buffer[6], 10);
  return true;
}

bool Hameg::getTriggerStatus(UInt8* pTriggerStatus)
{
  if (HAMEG_OK != _command(7, "TRGSTA?", 7+1))
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
          "\"ch%hhu\":{" JSON_LF
          "\"voltDiv\":\"%s\"," JSON_LF
          "\"voltDiv_mV\":%u," JSON_LF
          "\"enabled\":%hhu," JSON_LF
          "\"inverted\":%hhu," JSON_LF
          "\"ac\":%hhu," JSON_LF
          "\"gnd\":%hhu," JSON_LF
          "\"probe\":\"1:%hhu\"," JSON_LF
          "\"var\":%hhu," JSON_LF
          "\"yPosition\":%hi"
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

bool triggerDDF2json(UInt8* pDDF, UInt16* pDDF1, UInt8 TriggerStatus, UInt8 Hold, std::string& json)
{
  UInt8 b = pDDF[2];
  
  UInt8 Add  = (b & 0x08)>0;
  UInt8 Chop = (b & 0x10)>0;
  UInt8 BWL  = (b & 0x20)>0;
  UInt8 AltTrigger = (b & 0x80)>0; // alternating CH1,CH2
  UInt8 SingleShot = (pDDF[3] & 0x20)>0;
  UInt8 ZInput = (pDDF[3] & 0x80)>0;

  UInt8 TBA = pDDF[3] & 0x1f;
  ULong64 TBA_nS = hameg_nS(TBA);

  UInt8 TriggerSource = (AltTrigger) ? 0x4 : (b&0x3);
  const char* pTriggerSrc = TriggerSrcStrings[TriggerSource];

  // TRIG byte
  b = pDDF[6];
  
  UInt8 TriggerType = b&7;
  const char* pTriggerType = CouplingStrings[TriggerType];

  UInt8 Norm     = (b & 0x10)>0;
  UInt8 PeakPeak = (b & 0x20)>0;
  UInt8 Negative = (b & 0x80)>0;

  // STRMODE byte
  b = pDDF[7];

  UInt8 StoreMode = b&7;
  if (SingleShot)
    StoreMode = 1; // display "SGL";
  const char* pStoreMode = StoreModeStrings[StoreMode];

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
          "\"trigger\":{" JSON_LF
          "\"status\":%hhu," JSON_LF
          "\"source\":\"%s\"," JSON_LF
          "\"preTrigger\":\"%hhi%%\"," JSON_LF
          "\"singleShot\":%hhu," JSON_LF
          "\"coupling\":\"%s\"," JSON_LF
          "\"norm\":%hhu," JSON_LF
          "\"pp\":%hhu," JSON_LF
          "\"negative\":%hhu," JSON_LF
          "\"holdOff\":%hhu," JSON_LF
          "\"levelA\":%hu," JSON_LF
          "\"levelB\":%hu," JSON_LF
          "\"delayPosition\":%hi," JSON_LF
          "\"storeMode\":\"%s\"," JSON_LF
          "\"hold\":%hhu" JSON_LF
          "}," JSON_LF
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
          Hold
          ) >= sizeof(Buf))
  {
    // string too long
    return false;
  }
  json.append(Buf);

  if (snprintf(Buf, sizeof(Buf),
          "\"general\":{" JSON_LF
          "\"add\":%hhu," JSON_LF
          "\"chop\":%hhu," JSON_LF
          "\"bwl\":%hhu," JSON_LF
          "\"tba\":%hhu," JSON_LF
          "\"tba_nS\":%llu," JSON_LF
          "\"zInput\":%hhu," JSON_LF
          "\"xPosition\":%hi" JSON_LF
          "}"
          ,
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
    return false;
  }

  json.append(Buf);
  return true;
}

bool ddf2json(UInt8* pDDF, UInt16* pDDF1, UInt8 TriggerStatus, UInt8 Hold, std::string& json)
{
  json.append(getChannelDDFData(1, pDDF, pDDF1));
  json.append("," JSON_LF);
  json.append(getChannelDDFData(2, pDDF, pDDF1));
  json.append("," JSON_LF);
  return triggerDDF2json(pDDF, pDDF1, TriggerStatus, Hold, json);
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
  json = "{" JSON_LF;

  {
    char Buf[256];
    snprintf(Buf, sizeof(Buf),
             "\"id\":{" JSON_LF
             "\"device\":\"%s\"," JSON_LF
             "\"fc\":\"%s\"" JSON_LF
             "}," JSON_LF,
             m_DeviceId.c_str(),
             m_FrontControllerVersion.c_str());
    json.append(Buf);

    json.append("\"data\":{" JSON_LF);

    bool HaveData = false;
    if (DDF[0] & 0x10) // CH1 enabled?
    {
      getJsonWaveForm(1, json);
      HaveData = true;
    }

    UInt8 Add  = (DDF[2] & 0x08)>0;

    // CH2 enabled, but not ADD)?
    // (when channels are ADDed, then CH1 contains the valid sum)
    if ((DDF[1] & 0x10)&&
        (!Add))
    {
      if (HaveData)
        json.append("," JSON_LF);
      getJsonWaveForm(2, json);
      HaveData = true;
    }

    if (DDF[7] & 0x40) // REF1 enabled?
    {
      if (HaveData)
        json.append("," JSON_LF);
      getReferenceWaveForm(1, json);
      HaveData = true;
    }

    if (DDF[7] & 0x80) // REF2 enabled?
    {
      if (HaveData)
        json.append("," JSON_LF);
      getReferenceWaveForm(2, json);
      HaveData = true;
    }

    json.append(JSON_LF "}," JSON_LF);
  }

  UInt8 Hold = getHoldWaveForm();
  bool Ok = ddf2json(DDF, DDF1, TriggerStatus, Hold, json);

  json.append(JSON_LF "}" JSON_LF);

  return Ok;
}
