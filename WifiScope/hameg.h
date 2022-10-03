#pragma once
#include "utypes.h"
#include <string>

class Hameg
{
  public:
    static void setup(HardwareSerial* pSerial);
    static Hameg* getSingleton();

    bool connect();
    bool disconnect();
    
    const char* getDeviceID();
    const char* getFrontControllerVersion();

    bool getHoldWaveForm();
    bool setHoldWaveForm(UInt8 Hold);
    
    bool readDDF  (UInt8  pDDF[14]);
    bool readDDF1 (UInt16 pDDF1[8]);
    bool readRODDF(UInt16 pRODDF[5]);

    bool getTriggerStatus(UInt8* pTriggerStatus);

    bool getJSONData(std::string& json);
    UInt8* getChannelWaveForm(UInt8 Channel);
    bool getJsonWaveForm(UInt8 Channel, std::string& json);
    bool getCsvWaveForm(UInt8 Channel, std::string& csv);
    
    UInt8* getReferenceWaveForm(UInt8 RefChannel);
    bool getReferenceWaveForm(UInt8 Channel, std::string& json);

    bool setCH(UInt8 Channel, UInt8 VoltDiv, UInt8 Enabled, UInt8 AC, UInt8 Inverted, UInt8 GND);
    bool setTBA(UInt8 TimeDiv, UInt8 Single, UInt8 ZInput);
    bool setStoreMode(UInt8 Mode, UInt8 PreTrigger, UInt8 Ref1, UInt8 Ref2);
    bool setTrigger(UInt8 FallingEdge, UInt8 PeakPeak, UInt8 Norm, UInt8 Coupling);
    bool setVerticalMode(UInt8 AltTrigger, UInt8 Ch1_10_1, UInt8 Ch2_10_1, UInt8 Bwl, UInt8 Chop, UInt8 Add, UInt8 TriggerSource);

    bool autoSet();
    bool resetSingle();

  protected:
    HardwareSerial* m_pSerial;
    char m_Buffer[2048+20];
    UInt32 m_BufferByteCount;
    String m_DeviceId;
    String m_FrontControllerVersion;

    bool _hasPrefix(const char* pPrefix, const char* pBuffer=NULL);
    void _write(UInt32 ByteCount, const char* pData);
    bool _read(UInt32 ByteCount, char* pBuffer=NULL, UInt32 TimeoutMs=500);
    bool _command(UInt32 WriteByteCount, const char* pData, UInt32 ReadByteCount, char* pBuffer=NULL, UInt32 TimeoutMs=500);

  private:
    bool m_Connected;
    Hameg(HardwareSerial* pSerial);
};

// debug output methods
extern void debugPrint(const char* pMsg);
extern void debugPrintValue(UInt32 value);
extern void debugPrintlnParam(const char* pStr, UInt32 Value);
extern void debugPrintHex(UInt32 Value, UInt8 Width);
