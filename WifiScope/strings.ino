/*
 strings.ino - String resources.

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

#include "resource.h"

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

const PROGMEM char* const OpModeStrings[] = {
  "ANALOG", "DIGITAL", "XY", "CT",
  NULL
};

const PROGMEM char* const StoreModeStrings[] = {
  "RFR", "SGL", "ROL", "ENV", "AVR", "?5?", "?6?", "?7?",
  NULL
};

const PROGMEM char* const CouplingStrings[] = {
  "AC", "DC", "HF", "LF", "TVLine", "TVField", "LINE", "?",
  NULL
};

const PROGMEM char* const PreTriggerStrings[] = {
  "-75%", "-50%", "-25%", "0%",
  "25%", "50%", "75%", "100%",
  NULL
};

const PROGMEM char* const ProbeStrings[] = {
  "1:1", "1:10",
  NULL
};

const PROGMEM char* const TriggerSrcStrings[] = {
  "CH1", "CH2", "EXT", "EXT",
  "CH1,CH2",
  NULL
};

const PROGMEM char* const VoltageStrings[] = {
  "10mV", "20mV", "50mV", "100mV", "200mV", "500mV",
  "1V", "2V", "5V", "10V", "20V", "50V", "100V",
  "200V",
  NULL
};
