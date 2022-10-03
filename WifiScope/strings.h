/*
 strings.h - String resources.

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

/***********************************************************************/
/* string constants (in program memory to save RAM)                    */
/***********************************************************************/
extern const PROGMEM char File_ControlJS[];
extern const PROGMEM char File_IndexHTML[];
extern const PROGMEM char File_FaviconPNG[];
extern const PROGMEM char MimeTypeHtml[];
extern const PROGMEM char MimeTypePlain[];
extern const PROGMEM char MimeTypeCsv[];
extern const PROGMEM char MimeTypePNG[];
extern const PROGMEM char MimeTypeJS[];
extern const PROGMEM char MimeTypeJSON[];

/***********************************************************************/
/* string arrays (in program memory to save RAM)                       */
/***********************************************************************/
extern const PROGMEM char* const StoreModeStrings[];
extern const PROGMEM char* const CouplingStrings[];
extern const PROGMEM char* const PreTriggerStrings[];
extern const PROGMEM char* const ProbeStrings[];
extern const PROGMEM char* const TriggerSrcStrings[];
extern const PROGMEM char* const VoltageStrings[];
