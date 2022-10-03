/*
 WifiScope.ino - WiFi support for Hameg oscilloscopes.

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
 
/* Arduino Studio Settings:
 *  Board:     "LOLIN(WEMOS) D1 R2 & mini
*/

#include "WifiScopeConfig.h"
#include "utypes.h"
#include "hameg.h"
#include "eepromConfig.h"
#include "interactive.h"
#include "webserver.h"
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

// pins for UART connecting the hameg scope (alternate RX/TX pins of UART0)
#define HAMEG_RTS D6
#define HAMEG_RXD D7 // cannot be changed: fixed alternate UART0 pin
#define HAMEG_TXD D8 // cannot be changed: fixed alternate UART0 pin

SoftwareSerial DebugSerial(RX, TX, false);

void debugPrint(const char* pMsg)
{
  DebugSerial.write(pMsg);
}

void debugPrintValue(UInt32 value)
{
  DebugSerial.print(value);
}

void debugPrintlnParam(const char* pStr, UInt32 Value)
{
  DebugSerial.write(pStr);
  DebugSerial.print(Value);
  DebugSerial.write("\r\n");
}

void debugPrintHex(UInt32 Value, UInt8 Width)
{
   if ((Width>=4)&&(Value < 0x1000))
     DebugSerial.print("0");
   if ((Width>=3)&&(Value < 0x100))
     DebugSerial.print("0");
   if ((Width>=2)&&(Value < 0x10))
     DebugSerial.print("0");
   DebugSerial.print(Value, HEX);
}

// blink LED in intervals of given milliseconds
void blinkLed(long LedBlinkIntervalMs)        
{
  static bool s_LedState = false;
  static UInt32 s_PreviousMillis = 0; // last time LED was toggled

  // check blink interval
  UInt32 currentMillis = millis();
  if (currentMillis - s_PreviousMillis >= LedBlinkIntervalMs)
  {
    // save the last time you blinked the LED
    s_PreviousMillis = currentMillis;

    // toggle LED state
    s_LedState = !s_LedState;

    // set LED
    digitalWrite(BUILTIN_LED, (s_LedState) ? HIGH : LOW);
  }
}
void setupWiFi()
{
  // use WiFi settings from device's config section
#ifdef FEATURE_USE_EEPROM_CONFIG
  if (!ConfigData_ok())
  {
    DebugSerial.println("Configuration data is invalid!");
    Interactive_force();
    return;
  }
  const char* ssid = g_ConfigData.WifiSSID;
  const char* pass = g_ConfigData.WifiPassword;
  const char* host = g_ConfigData.WifiHostname;
#else
  const char* ssid = CONFIG_WIFI_SSID;
  const char* pass = CONFIG_WIFI_PASSWORD;
  const char* host = CONFIG_WIFI_HOSTNAME;
#endif
  
  DebugSerial.print("WiFi: Connecting '");
  DebugSerial.print(ssid);
  DebugSerial.print("'...");

  WiFi.persistent(false);
  WiFi.setAutoConnect(false);
  WiFi.mode(WIFI_STA);
  WiFi.hostname(host);
  //WiFi.setOutputPower(20.4);

  // start wifi connection
  WiFi.begin(ssid, pass);

  // wifi connection phase
  int throttle = millis();
  UInt8 Seconds = 0;
  while ((Seconds <= CONFIG_WIFI_TIMEOUT_S)&&(WiFi.status() != WL_CONNECTED))
  {
    if (Interactive_check())
    {
      while (true)
      {
        // very fast blinking while in interactive mode
        blinkLed(50);
        Interactive_loop();
      }
    }
    else
    {
      // fast LED blinking while waiting for WiFi
      blinkLed(100);

      // count seconds
      if (millis() >= throttle+1000)
      {
        throttle = millis();
        Seconds += 1;
        // show progress on serial console while wifi is not connected yet
        DebugSerial.print(".");
      }
    }
  }

  if (WiFi.status() != WL_CONNECTED)
  {
    DebugSerial.print(" FAILED! status=");
    DebugSerial.println(WiFi.status());
  }
  else
  {
    // show IP address on serial console
    DebugSerial.println("OK");
    DebugSerial.print("Local IP: ");
    DebugSerial.print(WiFi.localIP());
    DebugSerial.print(", hostname: ");
    DebugSerial.println(host);
  }
}

void setup()
{
  // LED
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, LOW);

  // serial interface to hameg (not the debug serial!)
  Serial.begin(115200);

  // Define pin modes for alternate TXD, RXD and RTS pins
  pinMode(HAMEG_RXD, INPUT);
  pinMode(HAMEG_TXD, OUTPUT);
  pinMode(HAMEG_RTS, OUTPUT);
  // set RTS
  digitalWrite(HAMEG_RTS, LOW);
  // swap UART0 to use alternate pins TX=GPIO15(D8), RX=GPIO13(D7)
  Serial.swap();

  // briefly wait after swapping UART pins
  delay(1000);
  digitalWrite(BUILTIN_LED, HIGH);

  // enable software serial for debug output on default TX/RX pins
  // (pins are now unsed, since we swapped UART0)
  pinMode(TX, OUTPUT);
  DebugSerial.begin(115200);

  // here we go: use debug serial
  debugPrint("\r\n\r\nWiFi Interface for Hameg Oscilloscopes " VERSION "\r\n"
#ifdef FEATURE_USE_EEPROM_CONFIG
             "Send three dots ('...') to enter configuration mode.\r\n"
#endif
             );

#ifdef FEATURE_USE_EEPROM_CONFIG
  // read EEPROM data
  ConfigData_read();

  UInt16 WebPortNumber = g_ConfigData.WebPortNumber;
#else
  UInt16 WebPortNumber = CONFIG_WEB_PORT;
#endif

  // configure WIFI
  setupWiFi();

  // create hameg control instance
  Hameg::setup(&Serial);
  
  // configure web server
  WebServer_setup(WebPortNumber);
}

void loop()
{
  static UInt32 ToggleTime = 0;

  if (Interactive_check())
  {
    // very fast blinking while in interactive mode
    blinkLed(50);
    Interactive_loop();
  }
  else
  {
    blinkLed(500);
  }
  
  // web server processing
  WebServer_loop();
}
