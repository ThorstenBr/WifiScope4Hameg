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
    "var ConnectionError = false;\n" \
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
    "function getReferenceSelector()\n" \
    "{\n" \
    "return (\"<select id=\\\"ref\\\" title=\\\"Select reference to display\\\" onchange=\\\"guiCallback(this)\\\">\"+\n" \
    "\"<option value=\\\"NO REF\\\">NO REF</option>\"+\n" \
    "\"<option value=\\\"REF1\\\">REF1</option>\"+\n" \
    "\"<option value=\\\"REF2\\\">REF2</option>\"+\n" \
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
    "GuiCells.Note.colSpan = 2;\n" \
    "GuiCells.Hold = TopRow.insertCell(3);\n" \
    "GuiCells.Hold.style.fontWeight = \"bold\";\n" \
    "GuiCells.Hold.style.fontSize = \"24px\";\n" \
    "GuiCells.ButtonsLeft = MiddleRow.cells[0];\n" \
    "GuiCells.ButtonsRight = MiddleRow.cells[2];\n" \
    "var wide = \"<button id=\\\"wide\\\" onclick=\\\"toggleWideView();\\\" title=\\\"Toggle wide display\\\">&#10231;</button>\";\n" \
    "var autoset = '<button type=\"button\" id=\"autoset\" onclick=\"guiCallback(this);\" title=\\\"Automaticaly adapt oscilloscope settings to signals\\\">AUTOSET</button>';\n" \
    "var reset_single = '<button type=\"button\" id=\"reset_single\" onclick=\"guiCallback(this);\" title=\"Reset single trigger\">RES</button>';\n" \
    "var trigger_edge = '<button type=\"button\" id=\"trigger_edge\" onclick=\"guiCallback(this);\" title=\"Trigger on rising or falling edge\">TRIG &uarr;</button>';\n" \
    "var update = '<button type=\"button\" id=\"update\" onclick=\"updateData();\" title=\\\"Refresh display\\\">UPDATE</button>';\n" \
    "var ref = getReferenceSelector();\n" \
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
    "ConnectionError = (this.Client.status != 200);\n" \
    "if (ConnectionError)\n" \
    "{\n" \
    "TextData = null;\n" \
    "}\n" \
    "processData(Charts[0], TextData);\n" \
    "}\n" \
    "};\n" \
    "DynamicLoader.prototype.load = function(cb)\n" \
    "{\n" \
    "if (this.Active)\n" \
    "return 0;\n" \
    "this.Active = 1;\n" \
    "this.Client.open(\"GET\", this.Url+\"/data?nocache=\"+timeNow());\n" \
    "this.Client.timeout = 4000;\n" \
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
    "Client.timeout = 4000;\n" \
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
    "}\n" \
    "else\n" \
    "if (element.id == \"ref\")\n" \
    "{\n" \
    "if (element.value == \"REF1\")\n" \
    "doRequest([\"STORE_MODE\", 0, \"mode\", Mode, \"preTrigger\", HamegSetting.trigger.preTrigger, \"ref1\", 1, \"ref2\", 0]);\n" \
    "else\n" \
    "if (element.value == \"REF2\")\n" \
    "doRequest([\"STORE_MODE\", 0, \"mode\", Mode, \"preTrigger\", HamegSetting.trigger.preTrigger, \"ref1\", 0, \"ref2\", 1]);\n" \
    "else\n" \
    "doRequest([\"STORE_MODE\", 0, \"mode\", Mode, \"preTrigger\", HamegSetting.trigger.preTrigger, \"ref1\", 0, \"ref2\", 0]);\n" \
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
    "if (chObj.enabled)\n" \
    "{\n" \
    "document.getElementById(\"ch_info\"+ChannelId).innerHTML = \"<b>\"+Info+\"</b>\"+Probe;\n" \
    "document.getElementById(\"ch\"+ChannelId+\"VoltDiv\").value = ChVoltage;\n" \
    "}\n" \
    "else\n" \
    "{\n" \
    "document.getElementById(\"ch_info\"+ChannelId).innerHTML = \"<font color='#505050'>\"+Info+\"</font>\"+Probe;\n" \
    "document.getElementById(\"ch\"+ChannelId+\"VoltDiv\").value = \"OFF\";\n" \
    "}\n" \
    "}\n" \
    "function updateGuiElements()\n" \
    "{\n" \
    "BlockGuiCallbacks = true;\n" \
    "document.getElementById(\"trigger_edge\").innerHTML = (HamegSetting.trigger.negative) ? \"TRIG &darr;\" : \"TRIG &uarr;\";\n" \
    "document.getElementById(\"hold\").style.background = (HamegSetting.hold) ? \"red\" : \"\";\n" \
    "if (ConnectionError)\n" \
    "{\n" \
    "GuiCells.Hold.style.color = \"red\";\n" \
    "GuiCells.Hold.innerHTML = \"NO CONNECTION\";\n" \
    "}\n" \
    "else\n" \
    "{\n" \
    "GuiCells.Hold.style.color = \"magenta\";\n" \
    "GuiCells.Hold.innerHTML = (HamegSetting.hold) ? \"HOLD\" : \"\";\n" \
    "}\n" \
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
    "var ref = document.getElementById(\"ref\");\n" \
    "if ((HamegSetting.data.reference1 === undefined)&&(HamegSetting.data.reference2 === undefined))\n" \
    "{\n" \
    "ref.value = \"NO REF\";\n" \
    "}\n" \
    "else\n" \
    "{\n" \
    "ref.value = (HamegSetting.data.reference2 === undefined) ? \"REF1\" : \"REF2\";\n" \
    "}\n" \
    "BlockGuiCallbacks = false;\n" \
    "}\n" \
    "function processData(ChartObj, Json)\n" \
    "{\n" \
    "ChartConfig = ChartObj.ChartConfig;\n" \
    "ChartConfig.data.datasets = [];\n" \
    "if (Json != null)\n" \
    "{\n" \
    "HamegSetting = JSON.parse(Json);\n" \
    "}\n" \
    "updateGuiElements();\n" \
    "if (Json == null)\n" \
    "return;\n" \
    "Y1Position = HamegSetting.ch1.yPosition/1000.0;\n" \
    "Y2Position = HamegSetting.ch2.yPosition/1000.0;\n" \
    "var TriggerInfo = \"\";\n" \
    "if (HamegSetting.trigger.norm)\n" \
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
    "if (HamegSetting.ch1.enabled)\n" \
    "{\n" \
    "var ch1  = convertWaveform(HamegSetting.data.channel1);\n" \
    "pushDataSet(ChartConfig, ch1, datasetChannel1);\n" \
    "}\n" \
    "if (HamegSetting.ch2.enabled)\n" \
    "{\n" \
    "var ch2  = convertWaveform(HamegSetting.data.channel2);\n" \
    "pushDataSet(ChartConfig, ch2, datasetChannel2);\n" \
    "}\n" \
    "var ref1 = convertWaveform(HamegSetting.data.reference1);\n" \
    "pushDataSet(ChartConfig, ref1, datasetRef1);\n" \
    "var ref2 = convertWaveform(HamegSetting.data.reference2);\n" \
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

/*******************************************************
 * GENERATED FILE
 *******************************************************/
#define FAVICON_PNG \
    "\x89\x50\x4e\x47\x0d\x0a\x1a\x0a\x00\x00\x00\x0d\x49\x48\x44\x52\x00\x00\x00\x20\x00" \
    "\x00\x00\x20\x08\x06\x00\x00\x00\x73\x7a\x7a\xf4\x00\x00\x01\x84\x69\x43\x43\x50\x49" \
    "\x43\x43\x20\x70\x72\x6f\x66\x69\x6c\x65\x00\x00\x28\x91\x7d\x91\x3d\x48\xc3\x50\x14" \
    "\x85\x4f\x53\xa5\x52\x2a\x0e\x76\x10\x71\xc8\x50\x5d\xb4\x20\x2a\xe2\xa8\x55\x28\x42" \
    "\x85\x50\x2b\xb4\xea\x60\xf2\xd2\x3f\x68\xd2\x90\xa4\xb8\x38\x0a\xae\x05\x07\x7f\x16" \
    "\xab\x0e\x2e\xce\xba\x3a\xb8\x0a\x82\xe0\x0f\x88\xa3\x93\x93\xa2\x8b\x94\x78\x5f\x52" \
    "\x68\x11\xe3\x83\xc7\xfb\x38\xef\x9d\xc3\xbd\xf7\x01\x42\xa3\xc2\x34\xab\x6b\x1c\xd0" \
    "\x74\xdb\x4c\x27\x13\x62\x36\xb7\x2a\x86\x5e\x11\x86\x80\x28\x80\x51\x99\x59\xc6\x9c" \
    "\x24\xa5\xe0\xbb\xbe\xee\x11\xe0\xe7\x5d\x9c\x67\xf9\xbf\xfb\x73\xf5\xaa\x79\x8b\x01" \
    "\x01\x91\x78\x96\x19\xa6\x4d\xbc\x41\x3c\xbd\x69\x1b\x9c\xf7\x89\xa3\xac\x24\xab\xc4" \
    "\xe7\xc4\x63\x26\x15\x48\xfc\xc8\x75\xc5\xe3\x37\xce\x45\x97\x05\x9e\x19\x35\x33\xe9" \
    "\x79\x62\x5e\xbf\x58\xec\x60\xa5\x83\x59\xc9\xd4\x88\xa7\x88\x63\xaa\xa6\x53\xbe\x90" \
    "\xf5\x58\xe5\xbc\xc5\x59\xab\xd4\x58\xab\x4e\xde\x61\x24\xaf\xaf\x2c\x73\x9d\xf6\x10" \
    "\x92\x58\xc4\x12\x24\x88\x50\x50\x43\x19\x15\xd8\x88\xd3\xa9\x93\x62\x21\x4d\xf7\x09" \
    "\x1f\xff\xa0\xeb\x97\xc8\xa5\x90\xab\x0c\x46\x8e\x05\x54\xa1\x41\x76\xfd\xe0\x7f\xf0" \
    "\x7b\xb6\x56\x61\x72\xc2\x4b\x8a\x24\x80\xee\x17\xc7\xf9\x18\x06\x42\xbb\x40\xb3\xee" \
    "\x38\xdf\xc7\x8e\xd3\x3c\x01\x82\xcf\xc0\x95\xde\xf6\x57\x1b\xc0\xcc\x27\xe9\xf5\xb6" \
    "\x16\x3b\x02\xfa\xb6\x81\x8b\xeb\xb6\xa6\xec\x01\x97\x3b\xc0\xc0\x93\x21\x9b\xb2\x2b" \
    "\x05\x69\x0b\x85\x02\xf0\x7e\x46\xdf\x94\x03\xfa\x6f\x81\xf0\x9a\x37\xb7\xd6\x3d\x4e" \
    "\x1f\x80\x0c\xcd\x2a\x75\x03\x1c\x1c\x02\x23\x45\xca\x5e\xf7\xe9\xbb\xa7\x73\x6e\xff" \
    "\xbe\x69\xcd\xef\x07\x2a\x78\x72\x8a\xa5\xfb\x65\x0e\x00\x00\x00\x06\x62\x4b\x47\x44" \
    "\x00\x00\x00\x00\x00\x00\xf9\x43\xbb\x7f\x00\x00\x00\x09\x70\x48\x59\x73\x00\x00\x2e" \
    "\x23\x00\x00\x2e\x23\x01\x78\xa5\x3f\x76\x00\x00\x00\x07\x74\x49\x4d\x45\x07\xe6\x0a" \
    "\x02\x14\x24\x35\x50\x04\xac\x3c\x00\x00\x00\x19\x74\x45\x58\x74\x43\x6f\x6d\x6d\x65" \
    "\x6e\x74\x00\x43\x72\x65\x61\x74\x65\x64\x20\x77\x69\x74\x68\x20\x47\x49\x4d\x50\x57" \
    "\x81\x0e\x17\x00\x00\x02\x76\x49\x44\x41\x54\x58\xc3\xed\x96\xcd\x6e\xd3\x40\x14\x85" \
    "\xbf\xf1\xd8\x8e\x9d\x3a\xad\x53\x60\x0b\xea\x86\x9f\x47\x40\xa2\x4b\x16\x5d\x52\xc4" \
    "\x0e\xb5\xcf\xc5\xb2\x08\xb1\x82\x4a\xa8\x3c\x01\x0b\xd6\x48\x6c\x10\x8b\x52\xf1\x00" \
    "\x8d\x93\xb8\x71\xe3\x78\x3c\x2c\x3c\x49\xec\xb4\x6e\x43\x82\x68\x11\x9d\x8d\xc7\xc7" \
    "\xbe\xbe\x33\xe7\x9e\x73\xc7\x70\x33\xae\x78\x08\x40\x5f\xe5\x02\x6c\x00\xde\x77\x00" \
    "\xf0\xfb\xc7\x24\xad\xf5\xe2\xc9\xf3\x76\x09\xef\x90\xb4\xda\x67\x70\x37\xe9\x03\x90" \
    "\xfa\xad\xb9\x63\x66\x73\xd8\x4b\xd1\xa7\xd4\x9f\x61\xc0\x8b\xcd\x8e\x4e\xba\x68\x21" \
    "\x00\x38\xad\xe0\x11\xba\x80\x2b\xb8\x93\xc4\xa6\x8e\x7a\xee\x98\xd9\x1c\x36\xc0\xc8" \
    "\x92\xb8\xcd\x16\x4a\x6b\x46\x41\x48\xc3\x7c\x50\x04\x6b\xa4\x08\xa4\xd6\x88\x20\x24" \
    "\x33\xab\xce\x82\x10\x07\x50\xd2\x26\x07\x72\x3f\x98\xec\x28\xd9\xd9\x38\xcb\xd4\x6e" \
    "\x3d\x6e\x03\xe4\xae\x47\x82\xc0\x07\x14\x82\x01\xc5\x0a\x13\x2c\x00\x72\x04\x89\xc1" \
    "\x00\x32\x04\x19\xe0\xa9\x62\x49\x29\x02\xbd\x1d\x22\x00\xb9\x1f\x91\xcf\x6a\x00\x10" \
    "\xfb\xd1\x59\x0d\xfc\xf3\x2e\x68\xc4\xc5\xae\x9e\xde\x59\xe7\x60\x6b\x15\x21\xc4\x5f" \
    "\x76\x81\x21\xef\x60\x6b\x95\x87\x6f\x7f\x2e\xce\x80\x5f\x52\x28\x62\x5c\xff\x32\x1e" \
    "\x31\x96\x40\x19\x97\xe9\x90\x5b\xb2\xc0\x2d\xc3\xc6\x65\x31\xb3\x39\x6c\x80\x24\x30" \
    "\x54\x69\x3d\x9d\x57\x70\xce\xc5\xbd\xb8\xc3\xd1\xce\x06\x8f\x3e\x74\xc9\x57\xc2\xb9" \
    "\x62\x66\x73\x58\xcb\x94\x40\x1b\xf9\x7e\x53\xfa\x3f\x3d\x0b\xf4\x76\x88\xf7\xfa\x07" \
    "\xc3\xa0\xcd\xfd\xa4\xc7\xf7\x97\xf7\x7e\xdb\x05\x0b\x97\x60\xd3\x2d\x84\xa4\xa5\xb3" \
    "\x3c\x03\x7e\xbf\xec\xeb\x92\x0b\xfa\x63\xe5\x76\xa6\x62\x32\xf8\xa7\xdd\x0d\x6e\xbf" \
    "\xfa\x8a\x87\x46\x66\x23\xe4\xb0\x0f\x97\xc4\x9c\x97\xa3\x70\xc1\xa4\x65\xea\x4a\xfb" \
    "\xac\x9b\xbb\xab\xc5\xfc\xc4\x2b\xce\x80\xd3\x56\x1b\x65\xcb\x0b\x63\xea\x72\x2c\xd4" \
    "\x88\xa2\x67\x21\x4f\x3e\x76\xc9\x6d\x67\x69\x11\x5e\x13\x17\xbc\x3b\x06\x21\xe6\x76" \
    "\x81\xd6\x1a\xb1\x1f\xe1\x9a\xff\x81\xd4\x0f\x16\x76\x81\x0d\xf0\x38\xef\xf3\xf9\xc5" \
    "\x5d\x20\xac\x52\xb3\x3d\xbe\xaf\xe2\x0f\xde\x1c\x11\x34\xd7\x10\x2a\x45\x29\x85\x76" \
    "\x5c\x24\x79\xd1\x9e\xf3\x0c\xa9\x14\x02\xcd\x0a\x9a\x51\x36\x22\x05\x9a\x2a\x23\x93" \
    "\x12\xd7\x60\x8e\xb4\xa6\x22\xfc\x32\xc8\x68\xee\x1d\xd2\x88\x23\x86\xc1\x34\x59\x73" \
    "\xef\x70\xa2\xdc\x32\x6e\x0d\x7a\x28\x95\xe3\x24\x31\x36\xa0\x2d\x09\xc6\x05\xee\x49" \
    "\xaf\xb8\xc6\x11\x43\x40\x8e\xa5\x37\xe8\x21\x01\x11\x77\x71\x4a\xff\x16\xc6\x05\xeb" \
    "\x93\xfd\x55\x95\x6b\x70\x21\x2a\xfd\x3b\x0f\xda\x24\x5e\x0b\x65\xbb\x93\x12\x28\xc7" \
    "\xbe\x30\xa6\x2e\xc7\x8c\x0b\x6a\xf4\xa8\xcf\x07\xac\x6c\x54\xff\x4e\xad\xb4\xf5\xf5" \
    "\x72\xc1\xcd\xb8\x19\xbf\x00\xd2\x2a\x78\xc0\xf3\x9d\xc6\x10\x00\x00\x00\x00\x49\x45" \
    "\x4e\x44\xae\x42\x60\x82" \

