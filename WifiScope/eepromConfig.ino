/*
 eepromConfig.ino - EEPROM support for configuration data.

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

#include "eepromConfig.h"

#ifdef FEATURE_USE_EEPROM_CONFIG

#include <EEPROM.h>

EepromConfigData g_ConfigData;
bool g_ConfigDataValid = false;

bool ConfigData_ok()
{
  return g_ConfigDataValid;
}

void ConfigData_read()
{
  EEPROM.begin(512);                            // access EEPROM
  UInt8* pData = (UInt8*) &g_ConfigData;
  for (UInt32 i=0;i<sizeof(g_ConfigData);i++)
  {
    pData[i] = EEPROM.read(0x40 + i);
  }
  if (g_ConfigData.MagicWord == EEPROM_MAGIC_WORD)
  {
    g_ConfigDataValid = true;
    if (g_ConfigData.StructSize < sizeof(g_ConfigData))
    {
      UInt16 Size = g_ConfigData.StructSize;
      memset(&pData[Size], 0xFF, sizeof(g_ConfigData)-Size);
    }
  }
  else
  {
    g_ConfigDataValid = false;
    memset(&g_ConfigData, 0xFF, sizeof(g_ConfigData));
    
    g_ConfigData.MagicWord           = EEPROM_MAGIC_WORD;
    g_ConfigData.WebPortNumber       = 80;
    g_ConfigData.WifiSSID[0]         = 0;
    g_ConfigData.WifiPassword[0]     = 0;
    strncpy(g_ConfigData.WifiHostname, "HAMEG", sizeof(g_ConfigData.WifiHostname));
  }
  
  // RAM config size always matches the struct
  g_ConfigData.StructSize = sizeof(g_ConfigData);
}

void ConfigData_write()
{
  UInt8* pData = (UInt8*) &g_ConfigData;
  for (UInt32 i=0;i<sizeof(g_ConfigData);i++)
  {
    if (pData[i] != EEPROM.read(0x40 + i))
    {
      EEPROM.write(0x40+i, pData[i]);
    }
  }
  EEPROM.commit();
}
#endif // FEATURE_USE_EEPROM_CONFIG
