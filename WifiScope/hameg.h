#pragma once
#include "utypes.h"
#include <string>

// enable/disable debug output
#define DEBUG 0

// status code: ok
#define HAMEG_OK                    0

// general communication error
#define HAMEG_COMM_ERROR           -1

// error code when we're not receiving a reply with the expected number of
// bytes within the given timeout
#define HAMEG_REPLY_TIMEOUT       -10

// error when we're receiving an invalid response code (not even a valid
// error code)
#define HAMEG_RESPONSE_CODE_ERROR -11

class Hameg
{
  public:
    static void setup(HardwareSerial* pSerial);
    static Hameg* getSingleton();

    bool connect();
    int  disconnect();
    void check();
    
    const char* getDeviceID();
    const char* getFrontControllerVersion();

    bool getHoldWaveForm();
    int  setHoldWaveForm(UInt8 Hold);
    
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

    int  setErrorDisplay(UInt8 ReadoutEnabled);
    int  setCH(UInt8 Channel, UInt8 VoltDiv, UInt8 Enabled, UInt8 AC, UInt8 Inverted, UInt8 GND);
    int  setTBA(UInt8 TimeDiv, UInt8 Single, UInt8 ZInput);
    int  setStoreMode(UInt8 Mode, UInt8 PreTrigger, UInt8 Ref1, UInt8 Ref2);
    int  setTrigger(UInt8 FallingEdge, UInt8 PeakPeak, UInt8 Norm, UInt8 Coupling);
    int  setVerticalMode(UInt8 AltTrigger, UInt8 Ch1_10_1, UInt8 Ch2_10_1, UInt8 Bwl, UInt8 Chop, UInt8 Add, UInt8 TriggerSource);
    int  setHorizontalMode(UInt8 CT, UInt8 XY, UInt8 X10, UInt8 Store, UInt8 PPDetect, UInt8 TbMode);

    int  autoset();
    int  resetSingle();

  protected:
    HardwareSerial* m_pSerial;
    char   m_Buffer[2048+20];
    UInt32 m_BufferByteCount;
    String m_DeviceId;
    String m_FrontControllerVersion;

    bool _hasPrefix(const char* pPrefix, const char* pBuffer=NULL);
    void _write(UInt32 ByteCount, const char* pData);
    int  _read(UInt32 ByteCount, char* pBuffer=NULL, UInt32 TimeoutMs=500);
    int  _command(UInt32 WriteByteCount, const char* pData, UInt32 ReadByteCount, bool CheckStatusByte=false, char* pBuffer=NULL, UInt32 TimeoutMs=500);

  private:
    bool   m_Connected;
    UInt32 m_ConnectionTimeout;

    Hameg(HardwareSerial* pSerial);
};

// debug output methods
extern void debugPrint(const char* pMsg);
extern void debugPrintValue(UInt32 value);
extern void debugPrintlnParam(const char* pStr, UInt32 Value);
extern void debugPrintHex(UInt32 Value, UInt8 Width);
