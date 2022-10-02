/*
 webserver.ino - Webserver interface for Hameg oscilloscopes.

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

#include "webserver.h"
#include "hameg.h"
#include "resource.h"
#include <ESP8266WebServer.h>

/***********************************************************************/
/* string constants (in program memory to save RAM)                    */
/***********************************************************************/
const PROGMEM char File_ControlJS[]  = HAMEGCONTROL_JS;
const PROGMEM char File_IndexHTML[]  = INDEX_HTML;
const PROGMEM char File_FaviconPNG[] = FAVICON_PNG;
const PROGMEM char MimeTypeHtml[]    = "text/html";
const PROGMEM char MimeTypePlain[]   = "text/plain";
const PROGMEM char MimeTypeCsv[]     = "text/csv";
const PROGMEM char MimeTypePNG[]     = "image/png";
const PROGMEM char MimeTypeJS[]      = "application/javascript";
const PROGMEM char MimeTypeJSON[]    = "application/json";

/***********************************************************************/
/* string arrays (in program memory to save RAM)                       */
/***********************************************************************/

const PROGMEM char* const StoreModeStrings[] = {
  "REF", "SGL", "ROL", "ENV", "AVR",
  NULL
};

const PROGMEM char* const CouplingStrings[] = {
  "AC", "DC", "HF", "LF", "TVLine", "TVField", "LINE",
  NULL
};

const PROGMEM char* const PreTriggerStrings[] = {
  "-75%", "-50%", "-25%", "0%",
  "25%", "50%", "75%", "100%",
  NULL
};

const PROGMEM char* const VoltageStrings[] = {
  "10mV", "20mV", "50mV", "100mV", "200mV", "500mV",
  "1V", "2V", "5V", "10V", "20V", "50V", "100V",
  "200V",
  NULL
};

/***********************************************************************/
/* global variables                                                    */
/***********************************************************************/
static Hameg*            g_pHameg     = NULL;
static ESP8266WebServer* g_pWebServer = NULL;

/***********************************************************************/
/* helper methods                                                      */
/***********************************************************************/

// map a string to the index of a matching string array element
static UInt8 mapString(const char* Needle, const char* const StringArray[], UInt8 Default=0)
{
  for (UInt8 i=0;StringArray[i]!=NULL;i++)
  {
    if (0 == strcmp(Needle, StringArray[i]))
       return i;
  }
  return Default;
}

// get string value of a given web request parameter
static String getParameterString(String Name, String Default)
{
  String s = g_pWebServer->arg(Name);
  if (s=="")
    return Default;
  return s;
}

// get integer value of a given web request parameter
static UInt32 getParameterInt(String Name, UInt32 Default)
{
  String s = g_pWebServer->arg(Name);
  if (s=="")
    return Default;
  return atoi(s.c_str());
}

/***********************************************************************/
/* webserver content handlers                                          */
/***********************************************************************/

// main index page (scope)
void handle_Index()
{
  g_pWebServer->send(200, MimeTypeHtml, File_IndexHTML, sizeof(File_IndexHTML)-1);
}

// javascript file contents
void handle_ControlJS()
{
  g_pWebServer->send(200, MimeTypeJS, File_ControlJS, sizeof(File_ControlJS)-1);
}

void handle_FaviconPNG()
{
  debugPrintHex(sizeof(File_FaviconPNG), 4);
  g_pWebServer->send(200, MimeTypePNG, File_FaviconPNG, sizeof(File_FaviconPNG));
}

// webserver "set" hook, sending commands to the Hameg scope
void handle_Set()
{
  const String ParamName = g_pWebServer->argName(0);
  const String ValueStr  = g_pWebServer->arg(0);
  Int32 Value            = atoi(ValueStr.c_str());

  bool Ok = false;

  if (ParamName != "")
  {
    if (g_pHameg->connect())
    {
      if (ParamName == "CH")
      {
        String VoltDivStr = g_pWebServer->arg("voltDiv");
        UInt8 Enabled     = getParameterInt("enabled", 1);
        UInt8 AC          = getParameterInt("ac", 0);
        UInt8 GND         = getParameterInt("gnd", 0);
        UInt8 Inverted    = getParameterInt("inverted", 0);
        UInt8 VoltDiv     = mapString(VoltDivStr.c_str(), VoltageStrings);
        Ok = g_pHameg->setCH(Value, VoltDiv, Enabled, AC, Inverted, GND);
      }
      else
      if (ParamName == "TBA")
      {
        UInt8 TimeDiv  = getParameterInt("timeDiv", 3);
        UInt8 Single   = getParameterInt("single", 0);
        UInt8 ZEnabled = getParameterInt("z", 0);
        Ok = g_pHameg->setTBA(TimeDiv, Single, ZEnabled);
      }
      else
      if (ParamName == "STORE_MODE")
      {
        String ModeStr    = g_pWebServer->arg("mode");
        String PreTrigStr = g_pWebServer->arg("preTrigger");
        UInt8 Ref1        = getParameterInt("ref1", 0);
        UInt8 Ref2        = getParameterInt("ref2", 0);
        
        UInt8 StoreMode  = mapString(ModeStr.c_str(), StoreModeStrings);
        UInt8 PreTrigger = mapString(PreTrigStr.c_str(), PreTriggerStrings, 3);

        Ok = g_pHameg->setStoreMode(StoreMode, PreTrigger, Ref1, Ref2);
      }
      else
      if (ParamName == "TRIGGER")
      {
        String CouplingStr = g_pWebServer->arg("coupling");
        UInt8 PeakPeak     = getParameterInt("pp", 3);
        UInt8 Norm         = getParameterInt("norm", 0);
        UInt8 FallingEdge  = getParameterInt("negative", 0);

        UInt8 Coupling     = mapString(CouplingStr.c_str(), CouplingStrings, 1);

        Ok = g_pHameg->setTrigger(FallingEdge, PeakPeak, Norm, Coupling);
      }
      else
      if (ParamName == "AUTOSET")
      {
        Ok = g_pHameg->autoSet();
      }
      else
      if (ParamName == "RESET_SINGLE")
      {
        Ok = g_pHameg->resetSingle();
      }
      else
      if (ParamName == "HOLD")
      {
        Ok = g_pHameg->setHoldWaveForm(Value);
      }
      else
      {
        g_pWebServer->send(500, MimeTypePlain, "ERROR: Unknown parameter.");
        return;
      }
      g_pHameg->disconnect();
    }
  }
    
  if (!Ok)
    g_pWebServer->send(500, MimeTypePlain, "ERROR");
  else
    g_pWebServer->send(200, MimeTypePlain, "OK");
}

// obtain raw scope measurement data as CSV
void handle_Csv()
{
  std::string CsvData;
  bool Ok = false;

  UInt8 Channel = getParameterInt("channel", 1);
  if (g_pHameg->connect())
  {
    Ok = g_pHameg->getCsvWaveForm(Channel, CsvData);
    g_pHameg->disconnect();
  }
  
  if (!Ok)
    g_pWebServer->send(500, MimeTypePlain, "ERROR");
  else
    g_pWebServer->send(200, MimeTypeCsv, CsvData.c_str());
}

void handle_Data()
{
  bool ok = false;
  if (g_pHameg->connect())
  {
    std::string json;
    if (g_pHameg->getJSONData(json))
    {
      g_pWebServer->send(200, MimeTypeJSON, json.c_str());
      ok = true;
    }
    g_pHameg->disconnect();
  }

  if (!ok)
  {
    g_pWebServer->send(500, MimeTypePlain, "ERROR: Unable to communicate with HAMEG scope.");
  }
}

// handler for invalid URLs
void handle_NotFound()
{
  g_pWebServer->send(404, MimeTypePlain, "Page not found");
}

/***********************************************************************/
/* webserver external API                                              */
/***********************************************************************/

// setup the webserver
void WebServer_setup(UInt32 PortNumber)
{
  g_pHameg = Hameg::getSingleton();

  g_pWebServer = new ESP8266WebServer(PortNumber);

#ifdef FEATURE_ALLOW_CORS
  g_pWebServer->enableCORS(true);
#endif

  // configure content callbacks
  g_pWebServer->on("/",                handle_Index);
  g_pWebServer->on("/hamegControl.js", handle_ControlJS);
  g_pWebServer->on("/favicon.png",     handle_FaviconPNG);
  g_pWebServer->on("/data",            handle_Data);
  g_pWebServer->on("/csv",             handle_Csv);
  g_pWebServer->on("/set",             handle_Set);
  g_pWebServer->onNotFound(            handle_NotFound);

  // ... and go!
  g_pWebServer->begin();
  
  DebugSerial.print("HTTP server running on port ");
  DebugSerial.println(PortNumber);
}

// process web requests
void WebServer_loop()
{
  if (g_pWebServer)
    g_pWebServer->handleClient();
}
