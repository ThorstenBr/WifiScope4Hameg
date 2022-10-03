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
#include "strings.h"
#include <ESP8266WebServer.h>

/***********************************************************************/
/* global variables                                                    */
/***********************************************************************/
static Hameg*            g_pHameg     = NULL;
static ESP8266WebServer* g_pWebServer = NULL;

/***********************************************************************/
/* helper methods                                                      */
/***********************************************************************/

// map a string to the index of a matching string array element
static UInt8 mapString(const String& Needle, const char* const StringArray[], UInt8 Default=0)
{
  const char* pNeedle = Needle.c_str();
  for (UInt8 i=0;StringArray[i]!=NULL;i++)
  {
    if (0 == strcmp(pNeedle, StringArray[i]))
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

void bin2HexStr(const UInt8* pData, UInt32 Size, std::string& str)
{
  char s[256];
  UInt32 p=0;
  for (UInt32 i=0;i<Size;i++)
  {
    sprintf(&s[p], "%02x", pData[i]);
    p+=2;
    if (p+2>=256)
    {
      str.append(s);
      p = 0;
      s[0] = 0;
    }
  }
  str.append(s);
}

/***********************************************************************/
/* webserver content handlers                                          */
/***********************************************************************/

void handle_ComError(int ErrorCode)
{
  char Message[80];
  snprintf(Message, sizeof(Message), "ERROR: Unable to communicate with HAMEG scope (%i).", ErrorCode);
  g_pWebServer->send(500, MimeTypePlain, Message);
}

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

  int Status = -3;

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
        UInt8 VoltDiv     = mapString(VoltDivStr, VoltageStrings);
        Status = g_pHameg->setCH(Value, VoltDiv, Enabled, AC, Inverted, GND);
      }
      else
      if (ParamName == "TBA")
      {
        UInt8 TimeDiv = getParameterInt("timeDiv", 3);
        UInt8 Single  = getParameterInt("single", 0);
        UInt8 ZInput  = getParameterInt("zInput", 0);
        Status = g_pHameg->setTBA(TimeDiv, Single, ZInput);
      }
      else
      if (ParamName == "STORE_MODE")
      {
        String ModeStr    = g_pWebServer->arg("mode");
        String PreTrigStr = g_pWebServer->arg("preTrigger");
        UInt8 Ref1        = getParameterInt("ref1", 0);
        UInt8 Ref2        = getParameterInt("ref2", 0);
        
        UInt8 StoreMode  = mapString(ModeStr, StoreModeStrings);
        UInt8 PreTrigger = mapString(PreTrigStr, PreTriggerStrings, 3);

        Status = g_pHameg->setStoreMode(StoreMode, PreTrigger, Ref1, Ref2);
      }
      else
      if (ParamName == "VERTICAL_MODE")
      {
        String TriggerSrc  = g_pWebServer->arg("triggerSource");
        UInt8 TriggerSource = mapString(TriggerSrc, TriggerSrcStrings);
        UInt8 AltTrigger   = 0; 
        if (TriggerSource == 0x4)
        {
          // alternating trigger source (CH1/CH2)
          TriggerSource = 0;
          AltTrigger = 1;
        }
        String Ch1ProbeStr = g_pWebServer->arg("ch1_probe");
        String Ch2ProbeStr = g_pWebServer->arg("ch2_probe");
        UInt8 Ch1_10_1     = mapString(Ch1ProbeStr, ProbeStrings);
        UInt8 Ch2_10_1     = mapString(Ch2ProbeStr, ProbeStrings);
        UInt8 Add          = getParameterInt("add", 0);
        UInt8 Chop         = getParameterInt("chop", 0);
        UInt8 Bwl          = getParameterInt("bwl", 0);

        Status = g_pHameg->setVerticalMode(AltTrigger, Ch1_10_1, Ch2_10_1, Bwl, Chop, Add, TriggerSource);
      }
      else
      if (ParamName == "TRIGGER")
      {
        String CouplingStr = g_pWebServer->arg("coupling");
        UInt8 PeakPeak     = getParameterInt("pp", 3);
        UInt8 Norm         = getParameterInt("norm", 0);
        UInt8 FallingEdge  = getParameterInt("negative", 0);

        UInt8 Coupling     = mapString(CouplingStr, CouplingStrings, 1);

        Status = g_pHameg->setTrigger(FallingEdge, PeakPeak, Norm, Coupling);
      }
      else
      if (ParamName == "AUTOSET")
      {
        Status = g_pHameg->autoset();
      }
      else
      if (ParamName == "RESET_SINGLE")
      {
        Status = g_pHameg->resetSingle();
      }
      else
      if (ParamName == "HOLD")
      {
        Status = g_pHameg->setHoldWaveForm(Value);
      }
      else
      {
        g_pWebServer->send(500, MimeTypePlain, "ERROR: Unknown parameter.");
        return;
      }
    }
  }

  if (DEBUG)
  {
    DebugSerial.print(ParamName.c_str());
    DebugSerial.print(", status=");
    DebugSerial.println(Status);
  }

  if (Status != 0)
  {
    char ErrorMessage[40];
    snprintf(ErrorMessage, sizeof(ErrorMessage), "ERROR: %i\n", Status);
    g_pWebServer->send(500, MimeTypePlain, ErrorMessage);
  }
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
    if (!Ok)
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
    if (!g_pHameg->getJSONData(json))
      g_pHameg->disconnect();
    else
    {
      g_pWebServer->send(200, MimeTypeJSON, json.c_str());
      ok = true;
    }
  }

  if (!ok)
  {
    handle_ComError(-1);
  }
}

void handle_Debug()
{
  int err = 0;
  if (!g_pHameg->connect())
    err = -1;
  else
  {
    std::string json;
    json.append("{\n");

    UInt8 DDF[14];
    if (!g_pHameg->readDDF(DDF))
      err = -1;
    else
    {
      json.append("\"ddf\": \"");
      bin2HexStr(DDF, sizeof(DDF), json);
      json.append("\",\n");
    }

    UInt16 DDF1[8];
    if (!g_pHameg->readDDF1(DDF1))
      err = -1;
    else
    {
      json.append("\"ddf1\": \"");
      bin2HexStr((UInt8*) DDF1, sizeof(DDF1), json);
      json.append("\",\n");
    }

    UInt16 RODDF[5];
    if (!g_pHameg->readRODDF(RODDF))
      err = -1;
    else
    {
      json.append("\"roddf\": \"");
      bin2HexStr((UInt8*)RODDF, sizeof(RODDF), json);
      json.append("\"\n");
    }

    json.append("}");

    if (!err)
      g_pWebServer->send(200, MimeTypeJSON, json.c_str());
  }

  if (err != 0)
  {
    g_pHameg->disconnect();
    handle_ComError(err);
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

  // debugging access
  g_pWebServer->on("/debug",           handle_Debug);

  // error handler
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
  if (g_pHameg)
    g_pHameg->check();
}
