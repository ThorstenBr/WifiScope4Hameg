/*
 interactive.ino - Interactive RS232 console for device configuration.

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

#include "WifiScopeConfig.h"
#include "utypes.h"
#include "eepromConfig.h"

extern SoftwareSerial DebugSerial;

const char* PROGMEM pMenu[] = {
  "0: Reboot",
#ifdef FEATURE_USE_EEPROM_CONFIG
  "1: Set WIFI SSID",
  "2: Set WIFI Password",
  "3: Set Hostname",
  "4: Set Web Server Port",
#endif // FEATURE_USE_EEPROM_CONFIG
  NULL
};

static bool g_InteractiveMode = false;
static bool g_Echo = true;

// enable interactive mode (i.e. missing configuration data,
// so user has to configure something)
void Interactive_force()
{
  g_InteractiveMode = true;
}

static const char* uartInput(bool CurrentBuffer)
{
   // static message buffers
  static char s_TextMessage[128];
  static unsigned int s_InputIndex = 0;

  // process any incoming characters
  while (DebugSerial.available() > 0)
  {
    char inChar = DebugSerial.read();
    // map TAB to normal whitespace
    if (inChar==9)
       inChar = ' ';
    // backspace: delete one character
    if (inChar==8)
    {
       if (s_InputIndex)
         s_InputIndex--;
       // skip character
       continue;
    }
    // LF or CR completes the line
    if ((inChar == 10)||(inChar==13))
    {
       DebugSerial.println("");
       if (s_InputIndex > 0) // ignore empty lines
       {
        s_TextMessage[s_InputIndex] = 0;   // add sentinel
        s_InputIndex = 0;
        return s_TextMessage;
       }
    }
    else
    {
       if (g_Echo)
           DebugSerial.write(inChar);
       s_TextMessage[s_InputIndex++] = inChar;
       if (s_InputIndex == sizeof(s_TextMessage)-1)
       {
          // Line too long: ignore
          s_InputIndex = 0;
          DebugSerial.println("\m\nERROR: Line too long");
       }
    }
  }
  if ((CurrentBuffer)&&(s_InputIndex))
  {
     s_TextMessage[s_InputIndex] = 0;   // add sentinel
     s_InputIndex = 0;
     return s_TextMessage;
  }
  return NULL;
}

static const char* readLine()
{
  const char* pInputData;
  do
  {
    pInputData = uartInput(false);
    //loopLedToggle(50);
  } while ((pInputData==NULL)||(pInputData[0]==0));
  return pInputData;
}

static void processInput(const char* pInputData)
{
  DebugSerial.println("");
  int s;

  switch(pInputData[0])
  {
    case '0':
      DebugSerial.println(pMenu[0]);
      DebugSerial.println("Rebooting...");
      ESP.restart();
      break;

#ifdef FEATURE_USE_EEPROM_CONFIG
    case '1': // set WIFI SSID
      DebugSerial.println(pMenu[1]);
      DebugSerial.print("Current WIFI SSID: ");
      DebugSerial.println(g_ConfigData.WifiSSID);
      DebugSerial.print("Set WIFI SSID: ");
      pInputData = readLine();
      if ((strlen(pInputData) > 1)&&(strlen(pInputData) < sizeof(g_ConfigData.WifiSSID)))
      {
        strncpy(g_ConfigData.WifiSSID, pInputData, sizeof(g_ConfigData.WifiSSID));
        ConfigData_write();
      }
      break;

    case '2': // set WIFI password
      DebugSerial.println(pMenu[2]);
      DebugSerial.print("Set WIFI password: ");
      pInputData = readLine();
      if ((strlen(pInputData) > 1)&&(strlen(pInputData) < sizeof(g_ConfigData.WifiPassword)))
      {
        strncpy(g_ConfigData.WifiPassword, pInputData, sizeof(g_ConfigData.WifiPassword));
        ConfigData_write();
      }
      break;

    case '3': // set hostname
      DebugSerial.println(pMenu[3]);
      DebugSerial.print("Set hostname: ");
      pInputData = readLine();
      if ((strlen(pInputData) > 1)&&(strlen(pInputData) < sizeof(g_ConfigData.WifiHostname)))
      {
        strncpy(g_ConfigData.WifiHostname, pInputData, sizeof(g_ConfigData.WifiHostname));
        ConfigData_write();
      }
      break;

    case '4': // set WebServer port number
      DebugSerial.println(pMenu[4]);
      DebugSerial.print("Set port number: ");
      pInputData = readLine();
      if (strlen(pInputData) > 1)
      {
        UInt16 WebPortNumber = atol(pInputData);
        if ((g_ConfigData.WebPortNumber == 0)||(g_ConfigData.WebPortNumber > 65535))
        {
          DebugSerial.println("Invalid port number!");
        }
        else
        {
          g_ConfigData.WebPortNumber = WebPortNumber;
          ConfigData_write();
        }
      }
      break;
#endif // FEATURE_USE_EEPROM_CONFIG

    default:
      break;
  }
}

bool Interactive_check()
{
  if (g_InteractiveMode)
      return true;

  const char* InputData = uartInput(true);
  if (InputData)
  {
    int i=0;
    int dots=0;
    while (InputData[i]!=0)
    {
      if (InputData[i] == '.')
      {
        dots++;
      }
      else
      {
        dots=0;
      }
      i++;
    }
    if (dots>=3)
    {
      g_InteractiveMode = true;
    }
  }
  return g_InteractiveMode;
}

void Interactive_loop()
{
  static bool ShowHelp=true;

  // read UART input data (if available)
  const char* pInputData = uartInput(true);

  // process input data (if available)
  if (pInputData)
  {
    ShowHelp = true;
    processInput(pInputData);
  }
  else
  {
    if (ShowHelp)
    {
      ShowHelp = false;
      DebugSerial.println("\r\nConfiguration Menu\r\n");
      for (int i=0;pMenu[i]!=NULL;i++)
      {
        DebugSerial.println(pMenu[i]);
      }
      DebugSerial.println("\r\nSelect number to configure?");
    }
  }
}
