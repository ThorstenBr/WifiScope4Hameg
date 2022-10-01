/*******************************************************
 * GENERATED FILE
 *******************************************************/
#define INDEX_HTML \
    "<html>\n" \
    "<head>\n" \
    "<title>Scope</title>\n" \
    "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"/>\n" \
    "<link rel=\"shortcut icon\" type=\"image/png\" href=\"favicon.png\"/>\n" \
    "<link rel=\"stylesheet\" type=\"text/css\" href=\"https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.9.4/Chart.min.css\">\n" \
    "<script type=\"text/JavaScript\" src=\"https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.9.4/Chart.min.js\"></script>\n" \
    "<style>\n" \
    "canvas {\n" \
    "-moz-user-select: none;\n" \
    "-webkit-user-select: none;\n" \
    "-ms-user-select: none;\n" \
    "margin:0px;\n" \
    "border: 3px solid rgba(0, 0, 0, 0.8);\n" \
    "border-radius: .5rem;\n" \
    "box-sizing: border-box;\n" \
    "background: #000;\n" \
    "}\n" \
    ".display {\n" \
    "box-shadow: 10px 10px 5px gray;\n" \
    "border: 3px solid rgba(0, 0, 0, 0.8);\n" \
    "border-radius: .5rem;\n" \
    "box-sizing: border-box;\n" \
    "text-align: center;\n" \
    "padding: 10px;\n" \
    "width: 7rem;\n" \
    "}\n" \
    "a.linkright {\n" \
    "float: right;\n" \
    "font-weight: bold;\n" \
    "color: blue;\n" \
    "text-decoration: none;\n" \
    "font-size: 30px;\n" \
    "}\n" \
    "h1 {\n" \
    "margin-top: 0;\n" \
    "}\n" \
    "body {\n" \
    "background-color: #002;\n" \
    "color: #a0a0a0;\n" \
    "font-family: Roboto, Arial, Helvetica, sans-serif;\n" \
    "}\n" \
    "table.scope {\n" \
    "background-color: #000;\n" \
    "border: 1px solid #888;\n" \
    "text-align: center;\n" \
    "}\n" \
    "table.scope button {\n" \
    "width: 80px;\n" \
    "height: 50px;\n" \
    "margin-bottom: 25px;\n" \
    "margin-left: 10px;\n" \
    "margin-right: 10px;\n" \
    "background-color: #444;\n" \
    "color: white;\n" \
    "border: 1px solid #202020;\n" \
    "}\n" \
    "table.scope button:hover {\n" \
    "background-color: #448;\n" \
    "}\n" \
    "select {\n" \
    "width: 80px;\n" \
    "height: 50px;\n" \
    "margin-bottom: 25px;\n" \
    "margin-left: 10px;\n" \
    "margin-right: 10px;\n" \
    "background-color: #444;\n" \
    "color: white;\n" \
    "text-align: center;\n" \
    "border: 1px solid #202020;\n" \
    "}\n" \
    "select:hover {\n" \
    "background-color: #448;\n" \
    "}\n" \
    "textarea\n" \
    "{\n" \
    "background-color: black;\n" \
    "color: yellow;\n" \
    "border: 1px solid #404040;\n" \
    "}\n" \
    "font.label\n" \
    "{\n" \
    "font-weight: bold;\n" \
    "color: #404040;\n" \
    "}\n" \
    "</style>\n" \
    "</head>\n" \
    "<body>\n" \
    "<script type=\"text/JavaScript\" src=\"hamegControl.js\"></script>\n" \
    "<center>\n" \
    "<script>\n" \
    "var Scales = {\n" \
    "xAxes: [{\n" \
    "type: 'linear',\n" \
    "scaleLabel: {\n" \
    "display: true\n" \
    "},\n" \
    "gridLines: {\n" \
    "drawOnChartArea: true,\n" \
    "color: '#c0c0c0'\n" \
    "},\n" \
    "ticks: {\n" \
    "min:  0,\n" \
    "color: '#142ffc',\n" \
    "callback: xAxisTicks\n" \
    "},\n" \
    "}],\n" \
    "yAxes: [\n" \
    "{\n" \
    "type: 'linear',\n" \
    "display: true,\n" \
    "position: 'left',\n" \
    "id: 'y-axis',\n" \
    "gridLines: {\n" \
    "drawOnChartArea: true,\n" \
    "color: '#c0c0c0'\n" \
    "},\n" \
    "ticks: {\n" \
    "min:  -4,\n" \
    "max:  4,\n" \
    "stepSize: 1,\n" \
    "display: false\n" \
    "}\n" \
    "}\n" \
    "],\n" \
    "};\n" \
    "var ScopeConfig = {\n" \
    "type: 'line',\n" \
    "hoverMode: 'index',\n" \
    "stacked: false,\n" \
    "data: {\n" \
    "labels: [],\n" \
    "datasets: []\n" \
    "},\n" \
    "options: {\n" \
    "resizeDelay: 500,\n" \
    "maintainAspectRatio: false,\n" \
    "title: {\n" \
    "display: false,\n" \
    "text: \"Scope\"\n" \
    "},\n" \
    "scales: Scales,\n" \
    "tooltips: {\n" \
    "enabled: true,\n" \
    "callbacks: {label: toolTipFunc, title: toolTipTimeValue}\n" \
    "},\n" \
    "plugins: {\n" \
    "zoom: {\n" \
    "zoom: {\n" \
    "wheel: {\n" \
    "enabled: true,\n" \
    "},\n" \
    "pinch: {\n" \
    "enabled: true\n" \
    "},\n" \
    "mode: 'xy',\n" \
    "}\n" \
    "}\n" \
    "},\n" \
    "animation: false\n" \
    "},\n" \
    "};\n" \
    "</script>\n" \
    "<center>\n" \
    "<table class=\"scope\" id=\"scope\">\n" \
    "<tr>\n" \
    "</tr>\n" \
    "<tr>\n" \
    "<td rowspan=2>\n" \
    "</td>\n" \
    "<td id=\"tdScope1\" colspan=5 style=\"width: 750px; height: 650px;\">\n" \
    "<canvas class=\"scope\" id=\"scope1\"></canvas>\n" \
    "</td>\n" \
    "<td>\n" \
    "</td>\n" \
    "<td rowspan=2>\n" \
    "</td>\n" \
    "</tr>\n" \
    "<tr></tr>\n" \
    "</table>\n" \
    "</center>\n" \
    "<script>\n" \
    "window.onload = function()\n" \
    "{\n" \
    "Chart.defaults.global.defaultFontColor = \"#fff\";\n" \
    "Chart.defaults.scale.gridLines.zeroLineColor = \"#fff\";\n" \
    "var Chart1a = newScope(ScopeConfig, \"scope\", \"scope1\",  \"http://hm407:8080\");\n" \
    "updateData();\n" \
    "};\n" \
    "</script>\n" \
    "</center>\n" \
    "</body>\n" \
    "</html>\n" \

/*******************************************************
 * GENERATED FILE
 *******************************************************/
#define HAMEGCONTROL_JS \
    "/*\n" \
    "*  hamegControl.js - Hameg scope display utilities.\n" \
    "*\n" \
    "* Copyright (c) 2014-2022 Thorsten Brehm, brehmt (at) gmail.com\n" \
    "*\n" \
    "* This library is free software; you can redistribute it and/or\n" \
    "* modify it under the terms of the GNU Lesser General Public\n" \
    "* License as published by the Free Software Foundation; either\n" \
    "* version 2.1 of the License, or (at your option) any later version.\n" \
    "* This library is distributed in the hope that it will be useful,\n" \
    "* but WITHOUT ANY WARRANTY; without even the implied warranty of\n" \
    "* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU\n" \
    "* Lesser General Public License for more details.\n" \
    "* You should have received a copy of the GNU Lesser General Public\n" \
    "* License along with this library; if not, write to the Free Software\n" \
    "* Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA\n" \
    "*/\n" \
    "var ChartConfigs = [];\n" \
    "var Charts = [];\n" \
    "var FileLoaderNames = [];\n" \
    "var FileLoaders = [];\n" \
    "var GuiCells = {};\n" \
    "var BlockGuiCallbacks = false;\n" \
    "var XResolutionPerDiv = 200;\n" \
    "var YResolutionPerDiv = 25;\n" \
    "var HamegSetting = {};\n" \
    "function timeNow()\n" \
    "{\n" \
    "return Math.round(((new Date()).getTime())/1000);\n" \
    "}\n" \
    "function toSecondDisplay(v)\n" \
    "{\n" \
    "if (v<0.001)\n" \
    "return (v*1000.0*1000).toFixed(3)+\" \\x00\\xB5s\";\n" \
    "if (v<0.01)\n" \
    "return (v*1000).toFixed(3)+\" ms\";\n" \
    "return v.toFixed(3)+\" s\";\n" \
    "}\n" \
    "function toTimebaseStrNS(v)\n" \
    "{\n" \
    "if (v<1000)\n" \
    "return \"\"+v+\"ns\";\n" \
    "v /= 1000;\n" \
    "if (v<1000)\n" \
    "return \"\"+v+\"\\x00\\xB5s\";\n" \
    "v /= 1000;\n" \
    "if (v<1000)\n" \
    "return \"\"+v+\"ms\";\n" \
    "v /= 1000;\n" \
    "return \"\"+v+\"s\";\n" \
    "}\n" \
    "function xAxisTicks(value, index, ticks)\n" \
    "{\n" \
    "return toTimebaseStrNS(index*HamegSetting.tba_nS);\n" \
    "}\n" \
    "var WideView=false;\n" \
    "function toggleWideView()\n" \
    "{\n" \
    "WideView = !WideView;\n" \
    "if (WideView)\n" \
    "document.getElementById(\"scope1\").style.width = window.innerWidth-250;\n" \
    "else\n" \
    "document.getElementById(\"scope1\").style.width = \"850px\";\n" \
    "Charts[0].resize();\n" \
    "}\n" \
    "function getVoltageSelector(ChannelId)\n" \
    "{\n" \
    "return (\"<select id=\\\"ch\"+ChannelId+\"VoltDiv\\\" title=\\\"Select channel voltage settings\\\" onchange=\\\"guiCallback(this)\\\">\"+\n" \
    "\"<option value=\\\"\\\"></option>\"+\n" \
    "\"<option value=\\\"10mV\\\">10mV</option>\"+\n" \
    "\"<option value=\\\"20mV\\\">20mV</option>\"+\n" \
    "\"<option value=\\\"50mV\\\">50mV</option>\"+\n" \
    "\"<option value=\\\"100mV\\\">100mV</option>\"+\n" \
    "\"<option value=\\\"200mV\\\">200mV</option>\"+\n" \
    "\"<option value=\\\"500mV\\\">500mV</option>\"+\n" \
    "\"<option value=\\\"1V\\\">1V</option>\"+\n" \
    "\"<option value=\\\"2V\\\">2V</option>\"+\n" \
    "\"<option value=\\\"5V\\\">5V</option>\"+\n" \
    "\"<option value=\\\"10V\\\">10V</option>\"+\n" \
    "\"<option value=\\\"20V\\\">20V</option>\"+\n" \
    "\"<option value=\\\"50V\\\">50V</option>\"+\n" \
    "\"<option value=\\\"100V\\\">100V</option>\"+\n" \
    "\"<option value=\\\"200V\\\">200V</option>\"+\n" \
    "\"<option value=\\\"DC\\\">DC</option>\"+\n" \
    "\"<option value=\\\"AC\\\">AC</option>\"+\n" \
    "\"<option value=\\\"GND\\\">GND</option>\"+\n" \
    "\"<option value=\\\"OFF\\\">OFF</option>\"+\n" \
    "\"</select>\");\n" \
    "}\n" \
    "function getTimeSelector()\n" \
    "{\n" \
    "var s = (\"<select id=\\\"time_div\\\" title=\\\"Select channel voltage settings\\\" onchange=\\\"guiCallback(this)\\\">\");\n" \
    "var Opts = [\n" \
    "\"50ns\", \"100ns\", \"200ns\",\n" \
    "\"500ns\", \"1&micro;s\", \"2&micro;s\",\n" \
    "\"5&micro;s\", \"10&micro;s\", \"20&micro;s\",\n" \
    "\"50&micro;s\", \"100&micro;s\", \"200&micro;s\",\n" \
    "\"500&micro;s\", \"1ms\", \"2ms\",\n" \
    "\"5ms\", \"10ms\", \"20ms\",\n" \
    "\"50ms\", \"100ms\", \"200ms\",\n" \
    "\"500ms\", \"1s\", \"2s\",\n" \
    "\"5s\", \"10s\", \"20s\",\n" \
    "\"50s\", \"100s\"\n" \
    "];\n" \
    "for (var i=0;i<Opts.length;i++)\n" \
    "{\n" \
    "s+=\"<option value=\\\"\"+i+\"\\\">\"+Opts[i]+\"</option>\\n\";\n" \
    "}\n" \
    "s += \"</select>\";\n" \
    "return s;\n" \
    "}\n" \
    "function getStoreModeSelector()\n" \
    "{\n" \
    "return (\"<select id=\\\"store_mode\\\" title=\\\"Select storage mode\\\" onchange=\\\"guiCallback(this)\\\">\"+\n" \
    "\"<option value=\\\"RFR\\\">RFR</option>\"+\n" \
    "\"<option value=\\\"SGL\\\">SGL</option>\"+\n" \
    "\"<option value=\\\"ROL\\\">ROL</option>\"+\n" \
    "\"<option value=\\\"ENV\\\">ENV</option>\"+\n" \
    "\"<option value=\\\"AVR\\\">AVR</option>\"+\n" \
    "\"</select>\");\n" \
    "}\n" \
    "function getPreTriggerSelector()\n" \
    "{\n" \
    "return (\"<select class=\\\"touch\\\" id=\\\"pre_trigger\\\" title=\\\"Select pre-trigger\\\" onchange=\\\"guiCallback(this)\\\">\"+\n" \
    "\"<option value=\\\"-75%\\\">-75%</option>\"+\n" \
    "\"<option value=\\\"-50%\\\">-50%</option>\"+\n" \
    "\"<option value=\\\"-25%\\\">-25%</option>\"+\n" \
    "\"<option value=\\\"0%\\\">0%</option>\"+\n" \
    "\"<option value=\\\"25%\\\">25%</option>\"+\n" \
    "\"<option value=\\\"50%\\\">50%</option>\"+\n" \
    "\"<option value=\\\"75%\\\">75%</option>\"+\n" \
    "\"<option value=\\\"100%\\\">100%</option>\"+\n" \
    "\"</select>\");\n" \
    "}\n" \
    "function getTriggerSourceSelector()\n" \
    "{\n" \
    "return (\"<select class=\\\"touch\\\" id=\\\"trigger_source\\\" title=\\\"Select trigger source\\\" onchange=\\\"guiCallback(this)\\\">\"+\n" \
    "\"<option value=\\\"CH1\\\">CH1</option>\"+\n" \
    "\"<option value=\\\"CH2\\\">CH2</option>\"+\n" \
    "\"<option value=\\\"EXT\\\">EXT</option>\"+\n" \
    "\"</select>\");\n" \
    "}\n" \
    "function getTriggerCouplingSelector()\n" \
    "{\n" \
    "return (\"<select class=\\\"touch\\\" id=\\\"trigger_coupling\\\" title=\\\"Select trigger coupling\\\" onchange=\\\"guiCallback(this)\\\">\"+\n" \
    "\"<option value=\\\"AC\\\">AC</option>\"+\n" \
    "\"<option value=\\\"DC\\\">DC</option>\"+\n" \
    "\"<option value=\\\"HF\\\">HF</option>\"+\n" \
    "\"<option value=\\\"LF\\\">LF</option>\"+\n" \
    "\"<option value=\\\"TVLine\\\">TVL</option>\"+\n" \
    "\"<option value=\\\"TVField\\\">TVF</option>\"+\n" \
    "\"<option value=\\\"LINE\\\">LINE</option>\"+\n" \
    "\"</select>\");\n" \
    "}\n" \
    "function addGuiElements(ScopeTable)\n" \
    "{\n" \
    "var TopRow    = ScopeTable.rows[0];\n" \
    "var MiddleRow = ScopeTable.rows[1];\n" \
    "var BottomRow = ScopeTable.rows[2];\n" \
    "GuiCells.DeviceID = TopRow.insertCell(0);\n" \
    "GuiCells.Trigger = TopRow.insertCell(1);\n" \
    "GuiCells.Note = TopRow.insertCell(2);\n" \
    "GuiCells.Note.innerHTML = \"<textarea rows='2' cols='60' spellcheck='false' title='comments, notes, free text area...'></textarea>\";\n" \
    "GuiCells.Note.colSpan = 2\n" \
    "GuiCells.Hold = TopRow.insertCell(3);\n" \
    "GuiCells.ButtonsLeft = MiddleRow.cells[0];\n" \
    "GuiCells.ButtonsRight = MiddleRow.cells[2];\n" \
    "var wide = \"<button id=\\\"wide\\\" onclick=\\\"toggleWideView();\\\" title=\\\"Toggle wide display\\\">&#10231;</button>\";\n" \
    "var autoset = '<button type=\"button\" id=\"autoset\" onclick=\"guiCallback(this);\" title=\\\"Automaticaly adapt oscilloscope settings to signals\\\">AUTOSET</button>';\n" \
    "var reset_single = '<button type=\"button\" id=\"reset_single\" onclick=\"guiCallback(this);\" title=\"Reset single trigger\">RES</button>';\n" \
    "var trigger_edge = '<button type=\"button\" id=\"trigger_edge\" onclick=\"guiCallback(this);\" title=\"Trigger on rising or falling edge\">TRIG &uarr;</button>';\n" \
    "var update = '<button type=\"button\" id=\"update\" onclick=\"updateData();\" title=\\\"Refresh display\\\">UPDATE</button>';\n" \
    "var ref = '<button type=\"button\" id=\"ref\" onclick=\"guiCallback({\\'id\\':\\'store_mode\\', \\'value\\':\\'REF\\'});\" title=\\\"Toggle display of reference signals\\\">REF</button>';\n" \
    "var hold = '<button type=\"button\" id=\"hold\" onclick=\"guiCallback({\\'id\\':\\'hold\\', \\'value\\':\\'0\\'});\" title=\\\"Hold current scope measurement data\\\">HOLD</button>';\n" \
    "GuiCells.ButtonsRight.innerHTML = autoset+\"<br>\"+trigger_edge+\"<br>\"+getPreTriggerSelector()+\"<br>\"+getTriggerCouplingSelector()+\"<br>\"+getTriggerSourceSelector()+\"<br>\"+reset_single;\n" \
    "GuiCells.ButtonsLeft.innerHTML  = wide+\"<br>\"+hold+\"<br>\"+update+\"<br>\"+ref;\n" \
    "GuiCells.Y1 = BottomRow.insertCell(0);\n" \
    "GuiCells.Y1.innerHTML = \"<font id='ch_info1'></font>\"+getVoltageSelector(1);\n" \
    "GuiCells.Y2 = BottomRow.insertCell(1);\n" \
    "GuiCells.Y2.innerHTML = \"<font id='ch_info2'></font>\"+getVoltageSelector(2);\n" \
    "GuiCells.StoreMode = BottomRow.insertCell(2);\n" \
    "GuiCells.StoreMode.innerHTML = \"<font class='label'>Store Mode</font><br>\"+getStoreModeSelector();\n" \
    "GuiCells.TDiv = BottomRow.insertCell(3);\n" \
    "GuiCells.TDiv.innerHTML = \"<font class='label'>T/DIV</font><br>\"+getTimeSelector();\n" \
    "}\n" \
    "function updateData()\n" \
    "{\n" \
    "for (var i=0;i<FileLoaders.length;i++)\n" \
    "{\n" \
    "FileLoaders[i].load();\n" \
    "}\n" \
    "return true;\n" \
    "}\n" \
    "function scopeLoader(Chart, Url, Callback)\n" \
    "{\n" \
    "if (FileLoaderNames.indexOf(Url)==-1)\n" \
    "{\n" \
    "var FileLoader = new DynamicLoader(Url, Callback, Chart);\n" \
    "FileLoaderNames.push(Url);\n" \
    "FileLoaders.push(FileLoader);\n" \
    "return FileLoader;\n" \
    "}\n" \
    "return null;\n" \
    "}\n" \
    "function newScope(ChartConfig, TableId, ChartId, Url)\n" \
    "{\n" \
    "var ctx = document.getElementById(ChartId).getContext('2d');\n" \
    "ScopeTable = document.getElementById(TableId);\n" \
    "addGuiElements(ScopeTable);\n" \
    "ChartConfigs.push(ChartConfig);\n" \
    "var Ch = new Chart(ctx, ChartConfig);\n" \
    "Ch.DataFiles = {};\n" \
    "Ch.Files = [];\n" \
    "Ch.Url = Url;\n" \
    "Ch.ChartConfig = ChartConfig;\n" \
    "Charts.push(Ch);\n" \
    "scopeLoader(Ch, Url);\n" \
    "return Ch;\n" \
    "}\n" \
    "function getRequestObject()\n" \
    "{\n" \
    "var xmlHttp = null;\n" \
    "try {\n" \
    "xmlHttp = new XMLHttpRequest();\n" \
    "} catch(e) {\n" \
    "try {\n" \
    "xmlHttp  = new ActiveXObject(\"Microsoft.XMLHTTP\");\n" \
    "} catch(e) {\n" \
    "try {\n" \
    "xmlHttp  = new ActiveXObject(\"Msxml2.XMLHTTP\");\n" \
    "} catch(e) {\n" \
    "xmlHttp  = null;\n" \
    "}\n" \
    "}\n" \
    "}\n" \
    "return xmlHttp;\n" \
    "}\n" \
    "function DynamicLoader(Url, Chart)\n" \
    "{\n" \
    "this.Url = Url;\n" \
    "this.Active = 0;\n" \
    "this.Chart = Chart;\n" \
    "this.Client = getRequestObject();\n" \
    "this.Client.dynLoader = this;\n" \
    "}\n" \
    "DynamicLoader.prototype.callback = function()\n" \
    "{\n" \
    "if (this.Client.readyState == 4)\n" \
    "{\n" \
    "var TextData = this.Client.responseText;\n" \
    "this.Active = 0;\n" \
    "if (this.Client.status == 200)\n" \
    "processData(Charts[0], TextData);\n" \
    "}\n" \
    "}\n" \
    "DynamicLoader.prototype.load = function(cb)\n" \
    "{\n" \
    "if (this.Active)\n" \
    "return 0;\n" \
    "this.Active = 1;\n" \
    "this.Client.open(\"GET\", this.Url+\"/data?nocache=\"+timeNow());\n" \
    "this.Client.onreadystatechange = function() {this.dynLoader.callback();};\n" \
    "this.Client.send(null);\n" \
    "};\n" \
    "function convertWaveform(StrData)\n" \
    "{\n" \
    "if(StrData === undefined)\n" \
    "return null;\n" \
    "var l = (StrData.length)>>1;\n" \
    "var Data = new Array(l);\n" \
    "for (var i=0;i<l;i++)\n" \
    "{\n" \
    "var v = \"\"+StrData.charAt(i*2) + StrData.charAt(i*2+1);\n" \
    "Data[i] = parseInt(v, 16);\n" \
    "}\n" \
    "return Data;\n" \
    "}\n" \
    "function pushDataSet(ChartConfig, ChannelData, DataSet)\n" \
    "{\n" \
    "if (ChannelData != null)\n" \
    "{\n" \
    "var TimebaseFactor = HamegSetting.tba_nS/XResolutionPerDiv*1e-9;\n" \
    "var YFactor = 1.0/YResolutionPerDiv;\n" \
    "for (var i = 0; (i < ChannelData.length)&&(i < 2000); ++i)\n" \
    "{\n" \
    "var Y = (ChannelData[i]-128)*YFactor;\n" \
    "DataSet.data.push({x:(i*TimebaseFactor),y:Y});\n" \
    "}\n" \
    "if (ChannelData.length>0)\n" \
    "{\n" \
    "ChartConfig.data.datasets.push(DataSet);\n" \
    "return true;\n" \
    "}\n" \
    "}\n" \
    "return false;\n" \
    "}\n" \
    "function doRequest(ArgumentList)\n" \
    "{\n" \
    "var Client = getRequestObject();\n" \
    "var Url = Charts[0].Url+\"/set?\";\n" \
    "for (i=0;i<ArgumentList.length/2;i++)\n" \
    "{\n" \
    "if (i>0)\n" \
    "Url += \"&\";\n" \
    "Url += ArgumentList[2*i];\n" \
    "Url += \"=\"+ArgumentList[2*i+1];\n" \
    "}\n" \
    "Client.open(\"POST\", Url);\n" \
    "Client.onreadystatechange = function() {updateData();};\n" \
    "Client.send(null);\n" \
    "}\n" \
    "function guiCallback(element)\n" \
    "{\n" \
    "if (BlockGuiCallbacks)\n" \
    "return;\n" \
    "if ((element.id == \"ch1VoltDiv\")||\n" \
    "(element.id == \"ch2VoltDiv\"))\n" \
    "{\n" \
    "var Channel = 1;\n" \
    "var chobj = HamegSetting.ch1;\n" \
    "if (element.id == \"ch2VoltDiv\")\n" \
    "{\n" \
    "Channel = 2;\n" \
    "chobj = HamegSetting.ch2;\n" \
    "}\n" \
    "var Value = element.value;\n" \
    "var ac = chobj.ac;\n" \
    "if ([\"10mV\", \"20mV\", \"50mV\", \"100mV\", \"200mV\", \"500mV\", \"1V\", \"2V\", \"5V\", \"10V\", \"20V\", \"50V\", \"100V\", \"200V\"].indexOf(Value)>=0)\n" \
    "doRequest([\"CH\", Channel, \"voltDiv\", element.value, \"enabled\", 1, \"gnd\", 0, \"ac\", ac]);\n" \
    "else\n" \
    "if (Value == \"OFF\")\n" \
    "doRequest([\"CH\", Channel, \"voltDiv\", chobj.voltDiv, \"enabled\", 0, \"gnd\", chobj.gnd, \"ac\", ac]);\n" \
    "else\n" \
    "if (Value == \"GND\")\n" \
    "doRequest([\"CH\", Channel, \"voltDiv\", chobj.voltDiv, \"enabled\", 1, \"gnd\", 1, \"ac\", ac]);\n" \
    "else\n" \
    "if (Value == \"AC\")\n" \
    "doRequest([\"CH\", Channel, \"voltDiv\", chobj.voltDiv, \"enabled\", 1, \"gnd\", chobj.gnd, \"ac\", 1]);\n" \
    "else\n" \
    "if (Value == \"DC\")\n" \
    "doRequest([\"CH\", Channel, \"voltDiv\", chobj.voltDiv, \"enabled\", 1, \"gnd\", chobj.gnd, \"ac\", 0]);\n" \
    "else\n" \
    "console.log(\"invalid\", Value);\n" \
    "}\n" \
    "else\n" \
    "if (element.id == \"time_div\")\n" \
    "{\n" \
    "doRequest([\"TBA\", 0, \"timeDiv\", element.value, \"single\", 0]);\n" \
    "}\n" \
    "else\n" \
    "if (element.id == \"autoset\")\n" \
    "{\n" \
    "doRequest([\"AUTOSET\", 0]);\n" \
    "}\n" \
    "else\n" \
    "if (element.id == \"reset_single\")\n" \
    "{\n" \
    "doRequest([\"RESET_SINGLE\", 0]);\n" \
    "}\n" \
    "else\n" \
    "if (element.id == \"hold\")\n" \
    "{\n" \
    "HamegSetting.hold = 1-HamegSetting.hold;\n" \
    "doRequest([\"HOLD\", HamegSetting.hold]);\n" \
    "updateGuiElements();\n" \
    "}\n" \
    "else\n" \
    "if ((element.id == \"store_mode\")||\n" \
    "(element.id == \"pre_trigger\"))\n" \
    "{\n" \
    "var Value = element.value;\n" \
    "var Mode = HamegSetting.trigger.storeMode;\n" \
    "var Ref1 = (HamegSetting.data.reference1===undefined) ? 0 : 1;\n" \
    "var Ref2 = (HamegSetting.data.reference2===undefined) ? 0 : 1;\n" \
    "if ([\"-75%\", \"-50%\", \"-25%\", \"0%\", \"25%\", \"50%\", \"75%\", \"100%\"].indexOf(Value)>-1)\n" \
    "{\n" \
    "doRequest([\"STORE_MODE\", 0, \"mode\", Mode, \"preTrigger\", Value, \"ref1\", Ref1, \"ref2\", Ref2]);\n" \
    "}\n" \
    "else\n" \
    "if ([\"RFR\", \"AVR\", \"ROL\", \"ENV\", \"SGL\"].indexOf(Value)>-1)\n" \
    "{\n" \
    "Mode = Value;\n" \
    "doRequest([\"STORE_MODE\", 0, \"mode\", Mode, \"preTrigger\", HamegSetting.trigger.preTrigger, \"ref1\", Ref1, \"ref2\", Ref2]);\n" \
    "}\n" \
    "else\n" \
    "if (Value == \"REF\")\n" \
    "{\n" \
    "if ((HamegSetting.data.reference1===undefined)&&(HamegSetting.data.reference2===undefined))\n" \
    "doRequest([\"STORE_MODE\", 0, \"mode\", Mode, \"preTrigger\", HamegSetting.trigger.preTrigger, \"ref1\", 1, \"ref2\", 0]);\n" \
    "else\n" \
    "if (HamegSetting.data.reference2===undefined)\n" \
    "doRequest([\"STORE_MODE\", 0, \"mode\", Mode, \"preTrigger\", HamegSetting.trigger.preTrigger, \"ref1\", 0, \"ref2\", 1]);\n" \
    "else\n" \
    "doRequest([\"STORE_MODE\", 0, \"mode\", Mode, \"preTrigger\", HamegSetting.trigger.preTrigger, \"ref1\", 0, \"ref2\", 0]);\n" \
    "}\n" \
    "}\n" \
    "else\n" \
    "if ((element.id == \"trigger_edge\")||\n" \
    "(element.id == \"trigger_coupling\"))\n" \
    "{\n" \
    "if (element.id == \"trigger_edge\")\n" \
    "HamegSetting.trigger.negative = 1-HamegSetting.trigger.negative;\n" \
    "if (element.id == \"trigger_coupling\")\n" \
    "{\n" \
    "HamegSetting.trigger.coupling = element.value;\n" \
    "}\n" \
    "updateGuiElements();\n" \
    "doRequest([\"TRIGGER\", 0, \"coupling\", HamegSetting.trigger.coupling, \"pp\", HamegSetting.trigger.pp,\n" \
    "\"norm\", HamegSetting.trigger.norm, \"negative\", HamegSetting.trigger.negative]);\n" \
    "}\n" \
    "}\n" \
    "function updateChInfo(ChannelId, chObj)\n" \
    "{\n" \
    "var ChVoltage = \"\";\n" \
    "var Color = (ChannelId == 1) ? \"red\" : \"blue\";\n" \
    "var Info = \"<font color='\"+Color+\"'>CH\"+ChannelId+\"</font> \";\n" \
    "if (chObj.inverted)\n" \
    "Info = \"<font style='text-decoration: overline'>\"+Info+\"</font>\";\n" \
    "if (chObj.gnd)\n" \
    "{\n" \
    "ChVoltage = \"GND\";\n" \
    "}\n" \
    "else\n" \
    "{\n" \
    "ChVoltage = chObj.voltDiv;\n" \
    "if (chObj.ac)\n" \
    "Info += \"~\"; // AC\n" \
    "else\n" \
    "Info += \"=\"; // DC\n" \
    "var v = chObj[\"var\"];\n" \
    "if (v != 255) // 100%?\n" \
    "{\n" \
    "v = v*100.0/255;\n" \
    "Info += \" (var: \"+v.toFixed(0)+\"%)\";\n" \
    "}\n" \
    "}\n" \
    "var Probe = \" <font color='#505050' id='probe\"+ChannelId+\"'>\"+chObj.probe+\"</font><br>\";\n" \
    "console.log(\"ChVoltage\", ChVoltage);\n" \
    "if (chObj.enabled)\n" \
    "{\n" \
    "document.getElementById(\"ch_info\"+ChannelId).innerHTML = \"<b>\"+Info+\"</b>\"+Probe;\n" \
    "document.getElementById(\"ch\"+ChannelId+\"VoltDiv\").value = ChVoltage;\n" \
    "}\n" \
    "else\n" \
    "{\n" \
    "document.getElementById(\"ch_info\"+ChannelId).innerHTML = \"<font color='#505050'>\"+Info+\"</font>\"+Probe;\n" \
    "document.getElementById(\"ch\"+ChannelId+\"VoltDiv\").value = \"\";\n" \
    "}\n" \
    "}\n" \
    "function updateGuiElements()\n" \
    "{\n" \
    "BlockGuiCallbacks = true;\n" \
    "document.getElementById(\"trigger_edge\").innerHTML = (HamegSetting.trigger.negative) ? \"TRIG &darr;\" : \"TRIG &uarr;\";\n" \
    "document.getElementById(\"hold\").style.background = (HamegSetting.hold) ? \"red\" : \"\";\n" \
    "GuiCells.Hold.innerHTML = (HamegSetting.hold) ? \"<b><font color='#ff00ff' size=+2>HOLD</font></b>\" : \"<b><font color='#000' size=+2>HOLD</font></b>\";\n" \
    "var Title = HamegSetting.deviceId.split(\" \")[0];\n" \
    "document.title = Title;\n" \
    "GuiCells.DeviceID.innerHTML = \"<center><font color=#88f><b>\"+Title+\"</b></font></center>\";\n" \
    "document.getElementById(\"trigger_coupling\").value = HamegSetting.trigger.coupling;\n" \
    "document.getElementById(\"pre_trigger\").value = HamegSetting.trigger.preTrigger;\n" \
    "document.getElementById(\"trigger_source\").value = HamegSetting.trigger.source;\n" \
    "document.getElementById(\"store_mode\").value = HamegSetting.trigger.storeMode;\n" \
    "document.getElementById(\"time_div\").value = HamegSetting.tba;\n" \
    "updateChInfo(1, HamegSetting.ch1);\n" \
    "updateChInfo(2, HamegSetting.ch2);\n" \
    "BlockGuiCallbacks = false;\n" \
    "}\n" \
    "function processData(ChartObj, Json)\n" \
    "{\n" \
    "ChartConfig = ChartObj.ChartConfig;\n" \
    "ChartConfig.data.datasets = [];\n" \
    "var obj = JSON.parse(Json);\n" \
    "HamegSetting = obj;\n" \
    "updateGuiElements();\n" \
    "Y1Position = HamegSetting.ch1.yPosition/1000.0;\n" \
    "Y2Position = HamegSetting.ch2.yPosition/1000.0;\n" \
    "var TriggerInfo = \"\";\n" \
    "if (obj.trigger.norm)\n" \
    "TriggerInfo += \"NORM\";\n" \
    "GuiCells.Trigger.innerHTML = TriggerInfo;\n" \
    "var datasetChannel1 = {\n" \
    "label: 'Channel 1',\n" \
    "backgroundColor: \"red\",\n" \
    "borderColor: \"red\",\n" \
    "borderWidth: 1,\n" \
    "pointRadius: 0,\n" \
    "spanGaps: false,\n" \
    "fill: false,\n" \
    "showLine:true,\n" \
    "borderDash: [],\n" \
    "yAxisID: 'y-axis',\n" \
    "data: []\n" \
    "};\n" \
    "var datasetChannel2 = {\n" \
    "label: 'Channel 2',\n" \
    "backgroundColor: \"blue\",\n" \
    "borderColor: \"blue\",\n" \
    "borderWidth: 1,\n" \
    "pointRadius: 1,\n" \
    "spanGaps: false,\n" \
    "fill: false,\n" \
    "showLine:true,\n" \
    "borderDash: [],\n" \
    "yAxisID: 'y-axis',\n" \
    "data: []\n" \
    "};\n" \
    "var datasetRef1 = {\n" \
    "label: 'Reference 1',\n" \
    "backgroundColor: \"green\",\n" \
    "borderColor: \"green\",\n" \
    "borderWidth: 1,\n" \
    "pointRadius: 1,\n" \
    "spanGaps: false,\n" \
    "fill: false,\n" \
    "showLine:true,\n" \
    "borderDash: [],\n" \
    "yAxisID: 'y-axis',\n" \
    "data: []\n" \
    "};\n" \
    "var datasetRef2 = {\n" \
    "label: 'Reference 2',\n" \
    "backgroundColor: \"yellow\",\n" \
    "borderColor: \"yellow\",\n" \
    "display:false,\n" \
    "borderWidth: 1,\n" \
    "pointRadius: 1,\n" \
    "spanGaps: false,\n" \
    "fill: false,\n" \
    "showLine:true,\n" \
    "borderDash: [],\n" \
    "yAxisID: 'y-axis',\n" \
    "data: []\n" \
    "};\n" \
    "if (obj.ch1.enabled)\n" \
    "{\n" \
    "var ch1  = convertWaveform(obj.data.channel1);\n" \
    "pushDataSet(ChartConfig, ch1, datasetChannel1);\n" \
    "}\n" \
    "if (obj.ch2.enabled)\n" \
    "{\n" \
    "var ch2  = convertWaveform(obj.data.channel2);\n" \
    "pushDataSet(ChartConfig, ch2, datasetChannel2);\n" \
    "}\n" \
    "var ref1 = convertWaveform(obj.data.reference1);\n" \
    "pushDataSet(ChartConfig, ref1, datasetRef1);\n" \
    "var ref2 = convertWaveform(obj.data.reference2);\n" \
    "pushDataSet(ChartConfig, ref2, datasetRef2);\n" \
    "ChartObj.update();\n" \
    "}\n" \
    "function toolTipTimeValue(ItemList)\n" \
    "{\n" \
    "return toSecondDisplay(ItemList[0].xLabel);\n" \
    "}\n" \
    "function toolTipFunc(tooltipItem, data)\n" \
    "{\n" \
    "var ChannelName = data.datasets[tooltipItem.datasetIndex].label || '';\n" \
    "var Factor = HamegSetting.ch1.voltDiv_mV;;\n" \
    "var YPosition = HamegSetting.ch1.yPosition/1000.0;\n" \
    "if (ChannelName === \"Channel 2\")\n" \
    "{\n" \
    "Factor = HamegSetting.ch2.voltDiv_mV;;\n" \
    "YPosition = HamegSetting.ch2.yPosition/1000.0;\n" \
    "}\n" \
    "label = (tooltipItem.yLabel-YPosition) * Factor;\n" \
    "if (label>=500.0)\n" \
    "return ChannelName+\": \"+(label/1000.0).toFixed(3)+\" V\";\n" \
    "return ChannelName+\": \"+label.toFixed(2)+\" mV\";\n" \
    "}\n" \

