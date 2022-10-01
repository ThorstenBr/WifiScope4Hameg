#ifndef _EEPROM_CONFIG_H
#define _EEPROM_CONFIG_H

#include "WifiScopeConfig.h"

#ifdef FEATURE_USE_EEPROM_CONFIG

#include "utypes.h"

// identifier for data in EEPROM
#define EEPROM_MAGIC_WORD 0x8742812

typedef struct
{
  UInt32 MagicWord;        // 0x8742812
  UInt16 StructSize;       // size in bytes (to detect extensions)
  UInt16 WebPortNumber;    // port number for web server
  char   WifiSSID[64];     // WIFI: SSID
  char   WifiPassword[64]; // WIFI: password
  char   WifiHostname[64]; // WIFI: hostname
} EepromConfigData;

// config data
extern EepromConfigData g_ConfigData;

// API
extern void ConfigData_read();
extern void ConfigData_write();
extern bool ConfigData_ok();

#endif // FEATURE_USE_EEPROM_CONFIG

#endif // _EEPROM_CONFIG_H
