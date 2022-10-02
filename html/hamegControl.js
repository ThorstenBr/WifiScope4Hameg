/*
*  hamegControl.js - Hameg scope display utilities.
*
* Copyright (c) 2014-2022 Thorsten Brehm, brehmt (at) gmail.com
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

var ChartConfigs = [];
var Charts = [];
var FileLoaderNames = [];
var FileLoaders = [];
var GuiCells = {};
var BlockGuiCallbacks = false;

var XResolutionPerDiv = 200;
var YResolutionPerDiv = 25;

var ConnectionError = false;
var HamegSetting = {};

function timeNow()
{
	return Math.round(((new Date()).getTime())/1000);
}

function toSecondDisplay(v)
{
	if (v<0.001)
		return (v*1000.0*1000).toFixed(3)+" \x00\xB5s";
	if (v<0.01)
		return (v*1000).toFixed(3)+" ms";
	return v.toFixed(3)+" s";
}

function toTimebaseStrNS(v)
{
	if (v<1000)
		return ""+v+"ns";
	v /= 1000;
	if (v<1000)
		return ""+v+"\x00\xB5s";
	v /= 1000;
	if (v<1000)
		return ""+v+"ms";
	v /= 1000;
	return ""+v+"s";
}

// custom callback for plotter x-axis labels
function xAxisTicks(value, index, ticks)
{
	return toTimebaseStrNS(index*HamegSetting.tba_nS);
}

var WideView=false;
function toggleWideView()
{
	WideView = !WideView;
	if (WideView)
		document.getElementById("scope1").style.width = window.innerWidth-250;
	else
		document.getElementById("scope1").style.width = "850px";
	Charts[0].resize();
}

function getVoltageSelector(ChannelId)
{
	return ("<select id=\"ch"+ChannelId+"VoltDiv\" title=\"Select channel voltage settings\" onchange=\"guiCallback(this)\">"+
		"<option value=\"10mV\">10mV</option>"+
		"<option value=\"20mV\">20mV</option>"+
		"<option value=\"50mV\">50mV</option>"+
		"<option value=\"100mV\">100mV</option>"+
		"<option value=\"200mV\">200mV</option>"+
		"<option value=\"500mV\">500mV</option>"+
		"<option value=\"1V\">1V</option>"+
		"<option value=\"2V\">2V</option>"+
		"<option value=\"5V\">5V</option>"+
		"<option value=\"10V\">10V</option>"+
		"<option value=\"20V\">20V</option>"+
		"<option value=\"50V\">50V</option>"+
		"<option value=\"100V\">100V</option>"+
		"<option value=\"200V\">200V</option>"+
		"<option value=\"DC\">DC</option>"+
		"<option value=\"AC\">AC</option>"+
		"<option value=\"GND\">GND</option>"+
		// Invert option is only supported for channel 2...
		((ChannelId==1) ? "" : "<option value=\"INVERT\">INVERT</option>")+
		"<option value=\"OFF\">OFF</option>"+
		"</select>");
}

function getTimeSelector()
{
	var s = ("<select id=\"time_div\" title=\"Select channel voltage settings\" onchange=\"guiCallback(this)\">");
	var Opts = [
			"50ns", "100ns", "200ns",
			"500ns", "1&micro;s", "2&micro;s",
			"5&micro;s", "10&micro;s", "20&micro;s",
			"50&micro;s", "100&micro;s", "200&micro;s",
			"500&micro;s", "1ms", "2ms",
			"5ms", "10ms", "20ms",
			"50ms", "100ms", "200ms",
			"500ms", "1s", "2s",
			"5s", "10s", "20s",
			"50s", "100s"
		   ];
	for (var i=0;i<Opts.length;i++)
	{
		s+="<option value=\""+i+"\">"+Opts[i]+"</option>\n";
	}
	s += "</select>";
	return s;
}

function getStoreModeSelector()
{
	return ("<select id=\"store_mode\" title=\"Select storage mode\" onchange=\"guiCallback(this)\">"+
		"<option value=\"RFR\">RFR</option>"+
		"<option value=\"SGL\">SGL</option>"+
		"<option value=\"ROL\">ROL</option>"+
		"<option value=\"ENV\">ENV</option>"+
		"<option value=\"AVR\">AVR</option>"+
		"</select>");
}

function getPreTriggerSelector()
{
	return ("<select class=\"touch\" id=\"pre_trigger\" title=\"Select pre-trigger\" onchange=\"guiCallback(this)\">"+
		"<option value=\"-75%\">-75%</option>"+
		"<option value=\"-50%\">-50%</option>"+
		"<option value=\"-25%\">-25%</option>"+
		"<option value=\"0%\">0%</option>"+
		"<option value=\"25%\">25%</option>"+
		"<option value=\"50%\">50%</option>"+
		"<option value=\"75%\">75%</option>"+
		"<option value=\"100%\">100%</option>"+
		"</select>");
}

function getTriggerSourceSelector()
{
	return ("<select class=\"touch\" id=\"trigger_source\" title=\"Select trigger source\" onchange=\"guiCallback(this)\">"+
		"<option value=\"CH1\">CH1</option>"+
		"<option value=\"CH2\">CH2</option>"+
		"<option value=\"EXT\">EXT</option>"+
		"</select>");
}

function getTriggerCouplingSelector()
{
	return ("<select class=\"touch\" id=\"trigger_coupling\" title=\"Select trigger coupling\" onchange=\"guiCallback(this)\">"+
		"<option value=\"AC\">AC</option>"+
		"<option value=\"DC\">DC</option>"+
		"<option value=\"HF\">HF</option>"+
		"<option value=\"LF\">LF</option>"+
		"<option value=\"TVLine\">TVL</option>"+
		"<option value=\"TVField\">TVF</option>"+
		"<option value=\"LINE\">LINE</option>"+
		"</select>");
}

function getReferenceSelector()
{
	return ("<select id=\"ref\" title=\"Select reference to display\" onchange=\"guiCallback(this)\">"+
		"<option value=\"NO REF\">NO REF</option>"+
		"<option value=\"REF1\">REF1</option>"+
		"<option value=\"REF2\">REF2</option>"+
		"</select>");
}

function addGuiElements(ScopeTable)
{
	var TopRow    = ScopeTable.rows[0];
	var MiddleRow = ScopeTable.rows[1];
	var BottomRow = ScopeTable.rows[2];
	
	GuiCells.DeviceID = TopRow.insertCell(0);
	GuiCells.Trigger = TopRow.insertCell(1);
	GuiCells.Note = TopRow.insertCell(2);
	GuiCells.Note.innerHTML = "<textarea rows='2' cols='60' spellcheck='false' title='comments, notes, free text area...'></textarea>";
	GuiCells.Note.colSpan = 2;

	GuiCells.Hold = TopRow.insertCell(3);
	GuiCells.Hold.style.fontWeight = "bold";
	GuiCells.Hold.style.fontSize = "24px";

	GuiCells.ButtonsLeft = MiddleRow.cells[0];
	GuiCells.ButtonsRight = MiddleRow.cells[2];
	
	
	var wide = "<button id=\"wide\" onclick=\"toggleWideView();\" title=\"Toggle wide display\">&#10231;</button>";
	var autoset = '<button type="button" id="autoset" onclick="guiCallback(this);" title=\"Automaticaly adapt oscilloscope settings to signals\">AUTOSET</button>'; 
	var reset_single = '<button type="button" id="reset_single" onclick="guiCallback(this);" title="Reset trigger (in single mode only)">RES</button>';
	var trigger_edge = '<button type="button" id="trigger_edge" onclick="guiCallback(this);" title="Trigger on rising or falling edge">TRIG &uarr;</button>'; 
	
	var update = '<button type="button" id="update" onclick="updateData();" title=\"Refresh display\">UPDATE</button>';
	var ref = getReferenceSelector();
	var hold = '<button type="button" id="hold" onclick="guiCallback({\'id\':\'hold\', \'value\':\'0\'});" title=\"Hold current scope measurement data\">HOLD</button>';
	
	GuiCells.ButtonsRight.innerHTML = autoset+"<br>"+trigger_edge+"<br>"+getPreTriggerSelector()+"<br>"+getTriggerCouplingSelector()+"<br>"+getTriggerSourceSelector()+"<br>"+reset_single;
	GuiCells.ButtonsLeft.innerHTML  = wide+"<br>"+hold+"<br>"+update+"<br>"+ref;

	GuiCells.Y1 = BottomRow.insertCell(0);
	GuiCells.Y1.innerHTML = "<font id='ch_info1'></font>"+getVoltageSelector(1);
	GuiCells.Y2 = BottomRow.insertCell(1);
	GuiCells.Y2.innerHTML = "<font id='ch_info2'></font>"+getVoltageSelector(2);

	GuiCells.StoreMode = BottomRow.insertCell(2);
	GuiCells.StoreMode.innerHTML = "<font class='label'>Store Mode</font><br>"+getStoreModeSelector();
		
	GuiCells.TDiv = BottomRow.insertCell(3);
	GuiCells.TDiv.innerHTML = "<font class='label'>T/DIV</font><br>"+getTimeSelector();
}

function updateData()
{
	for (var i=0;i<FileLoaders.length;i++)
	{
		FileLoaders[i].load();
	}
	return true;
}

function scopeLoader(Chart, Url, Callback)
{
	if (FileLoaderNames.indexOf(Url)==-1)
	{
		var FileLoader = new DynamicLoader(Url, Callback, Chart);
		FileLoaderNames.push(Url);
		FileLoaders.push(FileLoader);
		return FileLoader;
	}
	return null;
}

function newScope(ChartConfig, TableId, ChartId, Url)
{
	var ctx = document.getElementById(ChartId).getContext('2d');
	ScopeTable = document.getElementById(TableId);
	addGuiElements(ScopeTable);

	ChartConfigs.push(ChartConfig);
	var Ch = new Chart(ctx, ChartConfig);
	Ch.DataFiles = {};
	Ch.Files = [];
	Ch.Url = Url;
	Ch.ChartConfig = ChartConfig;
	Charts.push(Ch);

	scopeLoader(Ch, Url);

	return Ch;
}

function getRequestObject()
{
	var xmlHttp = null;
	try {
		// Mozilla, Opera, Safari, >=IE7
		xmlHttp = new XMLHttpRequest();
	} catch(e) {
		try {
		    // IE >= v6
		    xmlHttp  = new ActiveXObject("Microsoft.XMLHTTP");
		} catch(e) {
		    try {
		        // IE >= v5
		        xmlHttp  = new ActiveXObject("Msxml2.XMLHTTP");
		    } catch(e) {
		        xmlHttp  = null;
		    }
		}
	}
	return xmlHttp;
}

function DynamicLoader(Url, Chart)
{
	this.Url = Url;
	this.Active = 0;
	this.Chart = Chart;
	this.Client = getRequestObject();
	this.Client.dynLoader = this;
}

DynamicLoader.prototype.callback = function()
{
	if (this.Client.readyState == 4)
	{
		var TextData = this.Client.responseText;
		this.Active = 0;
		ConnectionError = (this.Client.status != 200);
		if (ConnectionError)
		{
			TextData = null;
		}
		processData(Charts[0], TextData);
	}
};

DynamicLoader.prototype.load = function(cb)
{
	if (this.Active)
		return 0;
	this.Active = 1;
	this.Client.open("GET", this.Url+"/data?nocache="+timeNow());
	this.Client.timeout = 4000;
	this.Client.onreadystatechange = function() {this.dynLoader.callback();};
	this.Client.send(null);
};

function convertWaveform(StrData)
{
	if(StrData === undefined)
		return null;

	var l = (StrData.length)>>1;
	
	var Data = new Array(l);
	for (var i=0;i<l;i++)
	{
		var v = ""+StrData.charAt(i*2) + StrData.charAt(i*2+1);
		Data[i] = parseInt(v, 16);
	}

	return Data;
}

function pushDataSet(ChartConfig, ChannelData, DataSet)
{
	if (ChannelData != null)
	{
		var TimebaseFactor = HamegSetting.tba_nS/XResolutionPerDiv*1e-9;
		var YFactor = 1.0/YResolutionPerDiv;
		for (var i = 0; (i < ChannelData.length)&&(i < 2000); ++i)
		{
			var Y = (ChannelData[i]-128)*YFactor;
			DataSet.data.push({x:(i*TimebaseFactor),y:Y});
		}
		if (ChannelData.length>0)
		{
			ChartConfig.data.datasets.push(DataSet);
			return true;
		}
	}
	return false;
}

function doRequest(ArgumentList)
{
	var Client = getRequestObject();
	var Url = Charts[0].Url+"/set?";
	for (i=0;i<ArgumentList.length/2;i++)
	{
		if (i>0)
			Url += "&";
		Url += ArgumentList[2*i];
		Url += "="+ArgumentList[2*i+1];
	}
	Client.open("POST", Url);
	Client.timeout = 4000;
	Client.onreadystatechange = function() {updateData();};
	Client.send(null);
}

function guiCallback(element)
{
	if (BlockGuiCallbacks)
		return;

	if ((element.id == "ch1VoltDiv")||
	    (element.id == "ch2VoltDiv"))
	{
		var Channel = 1;
		var chobj = HamegSetting.ch1;
		if (element.id == "ch2VoltDiv")
		{
			Channel = 2;
			chobj = HamegSetting.ch2;
		}
		var Value = element.value;
		var chEnabled = 1;
		if (["10mV", "20mV", "50mV", "100mV", "200mV", "500mV", "1V", "2V", "5V", "10V", "20V", "50V", "100V", "200V"].indexOf(Value)>=0)
		{
			chobj.gnd = 0;
			chobj.voltDiv = Value;
		}
		else
		if (Value == "OFF")
		{
			chEnabled = 0;
		}
		else
		if (Value == "GND")
		{
			chobj.gnd = 1;
		}
		else
		if (Value == "AC")
		{
			chobj.ac = 1;
		}
		else
		if (Value == "DC")
		{
			chobj.ac = 0;
		}
		else
		if (Value == "INVERT")
		{
			chobj.inverted = 1-chobj.inverted;
		}
		else
		{
			console.log("invalid", Value);
			return;
		}

		chobj.enabled = chEnabled;
		updateGuiElements();
		doRequest(["CH", Channel, "voltDiv", chobj.voltDiv, "enabled", chobj.enabled, "gnd", chobj.gnd, "ac", chobj.ac, "inverted", chobj.inverted]);
	}
	else
	if (element.id == "time_div")
	{
		doRequest(["TBA", 0, "timeDiv", element.value, "single", HamegSetting.trigger.singleShot, "zInput", HamegSetting.zInput]);
	}
	else
	if (element.id == "autoset")
	{
		doRequest(["AUTOSET", 0]);
	}
	else
	if (element.id == "reset_single")
	{
		doRequest(["RESET_SINGLE", 0]);
	}
	else
	if (element.id == "hold")
	{
		HamegSetting.hold = 1-HamegSetting.hold;
		doRequest(["HOLD", HamegSetting.hold]);
		updateGuiElements();
	}
	else
	if ((element.id == "store_mode")||
	    (element.id == "pre_trigger"))
	{
		var Value = element.value;
		var Mode = HamegSetting.trigger.storeMode;
		var Ref1 = (HamegSetting.data.reference1===undefined) ? 0 : 1;
		var Ref2 = (HamegSetting.data.reference2===undefined) ? 0 : 1;

		if (["-75%", "-50%", "-25%", "0%", "25%", "50%", "75%", "100%"].indexOf(Value)>-1)
		{
			doRequest(["STORE_MODE", 0, "mode", Mode, "preTrigger", Value, "ref1", Ref1, "ref2", Ref2]);
		}
		else
		if (["RFR", "AVR", "ROL", "ENV", "SGL"].indexOf(Value)>-1)
		{
			Mode = Value;
			if (((HamegSetting.trigger.singleShot)&&(Value != "SGL"))||
			    ((!HamegSetting.trigger.singleShot)&&(Value == "SGL")))
			{
				// need to enable or disable single shot mode first
				HamegSetting.trigger.singleShot = (Value == "SGL") ? 1 : 0;
				doRequest(["TBA", 0, "timeDiv", HamegSetting.tba, "single", HamegSetting.trigger.singleShot, "zInput", HamegSetting.zInput]);
			}
			if (Value != "SGL")
				doRequest(["STORE_MODE", 0, "mode", Mode, "preTrigger", HamegSetting.trigger.preTrigger, "ref1", Ref1, "ref2", Ref2]);
		}
	}
	else
	if (element.id == "ref")
	{
		if (element.value == "REF1")
			doRequest(["STORE_MODE", 0, "mode", Mode, "preTrigger", HamegSetting.trigger.preTrigger, "ref1", 1, "ref2", 0]);
		else
		if (element.value == "REF2")
			doRequest(["STORE_MODE", 0, "mode", Mode, "preTrigger", HamegSetting.trigger.preTrigger, "ref1", 0, "ref2", 1]);
		else
			doRequest(["STORE_MODE", 0, "mode", Mode, "preTrigger", HamegSetting.trigger.preTrigger, "ref1", 0, "ref2", 0]);
	}
	else
	if ((element.id == "trigger_edge")||
	    (element.id == "trigger_coupling"))
	{
		// toggle rising/falling edge
		if (element.id == "trigger_edge")
			HamegSetting.trigger.negative = 1-HamegSetting.trigger.negative;
		if (element.id == "trigger_coupling")
		{
			HamegSetting.trigger.coupling = element.value;
		}

		updateGuiElements();
		doRequest(["TRIGGER", 0, "coupling", HamegSetting.trigger.coupling, "pp", HamegSetting.trigger.pp,
		           "norm", HamegSetting.trigger.norm, "negative", HamegSetting.trigger.negative]);
	}
}

function updateChInfo(ChannelId, chObj)
{
	var ChVoltage = "";
	var Color = (ChannelId == 1) ? "red" : "blue";
	var Info = "<font color='"+Color+"'>CH"+ChannelId+"</font>";
	if (chObj.inverted)
		Info = "<font style='text-decoration: overline'>"+Info+"</font>";
	Info += " ";
	if (chObj.gnd)
	{
		ChVoltage = "GND";
	}
	else
	{
		ChVoltage = chObj.voltDiv;
		
		if (chObj.ac)
			Info += "~"; // AC
		else
			Info += "="; // DC
		
		// variable voltage div
		var v = chObj["var"];
		if (v != 255) // 100%?
		{
			v = v*100.0/255;
			Info += " (var: "+v.toFixed(0)+"%)";
		}
	}

	var Probe = " <font color='#505050' id='probe"+ChannelId+"'>"+chObj.probe+"</font><br>";

	if (chObj.enabled)
	{
		document.getElementById("ch_info"+ChannelId).innerHTML = "<b>"+Info+"</b>"+Probe;
		document.getElementById("ch"+ChannelId+"VoltDiv").value = ChVoltage;
	}
	else
	{
		document.getElementById("ch_info"+ChannelId).innerHTML = "<font color='#505050'>"+Info+"</font>"+Probe;
		document.getElementById("ch"+ChannelId+"VoltDiv").value = "OFF";
	}
}

function updateGuiElements()
{
	BlockGuiCallbacks = true;

	document.getElementById("trigger_edge").innerHTML = (HamegSetting.trigger.negative) ? "TRIG &darr;" : "TRIG &uarr;";

	document.getElementById("hold").style.background = (HamegSetting.hold) ? "red" : "";

	if (ConnectionError)
	{
		GuiCells.Hold.style.color = "red";
		GuiCells.Hold.innerHTML = "NO CONNECTION";
	}
	else
	{
		GuiCells.Hold.style.color = "magenta";
		GuiCells.Hold.innerHTML = (HamegSetting.hold) ? "HOLD" : "";
	}

	var Title = HamegSetting.deviceId.split(" ")[0];
	document.title = Title;
	GuiCells.DeviceID.innerHTML = "<center><font color=#88f><b>"+Title+"</b></font></center>";
	
	document.getElementById("trigger_coupling").value = HamegSetting.trigger.coupling;
	document.getElementById("pre_trigger").value = HamegSetting.trigger.preTrigger;
	document.getElementById("trigger_source").value = HamegSetting.trigger.source;

	document.getElementById("store_mode").value = HamegSetting.trigger.storeMode;
	document.getElementById("time_div").value = HamegSetting.tba;

	// update details on channel 1+2
	updateChInfo(1, HamegSetting.ch1);
	updateChInfo(2, HamegSetting.ch2);
	
	var ref = document.getElementById("ref");
	if ((HamegSetting.data.reference1 === undefined)&&(HamegSetting.data.reference2 === undefined))
	{
		ref.value = "NO REF";
	}
	else
	{
		ref.value = (HamegSetting.data.reference2 === undefined) ? "REF1" : "REF2";
	}

	var resetSingle = document.getElementById("reset_single");
	if (HamegSetting.trigger.singleShot)
	{
		resetSingle.disabled = 0;
		resetSingle.style.background = (HamegSetting.trigger.status == 2) ? "#00b000" : "";
		resetSingle.style.color = "white";
	}
	else
	{
		resetSingle.disabled = 1;
		resetSingle.style.background = "#202020";
		resetSingle.style.color = "#808080";
	}

	BlockGuiCallbacks = false;
}

function processData(ChartObj, Json)
{
	ChartConfig = ChartObj.ChartConfig;
	ChartConfig.data.datasets = [];

	if (Json != null)
	{
		HamegSetting = JSON.parse(Json);
	}
	updateGuiElements();

	if (Json == null)
		return;

	Y1Position = HamegSetting.ch1.yPosition/1000.0;
	Y2Position = HamegSetting.ch2.yPosition/1000.0;

	var TriggerInfo = "";
	if (HamegSetting.trigger.norm)
		TriggerInfo += "NORM";
	GuiCells.Trigger.innerHTML = TriggerInfo;

	var datasetChannel1 = {
				label: 'Channel 1',
				backgroundColor: "red",
				borderColor: "red",
				borderWidth: 1,
				pointRadius: 0,
				spanGaps: false,
				fill: false,
				showLine:true,
				borderDash: [],
				yAxisID: 'y-axis',
				data: []
			};

	var datasetChannel2 = {
				label: 'Channel 2',
				backgroundColor: "blue",
				borderColor: "blue",
				borderWidth: 1,
				pointRadius: 1,
				spanGaps: false,
				fill: false,
				showLine:true,
				borderDash: [],
				yAxisID: 'y-axis',
				data: []
			};
			
	var datasetRef1 = {
				label: 'Reference 1',
				backgroundColor: "green",
				borderColor: "green",
				borderWidth: 1,
				pointRadius: 1,
				spanGaps: false,
				fill: false,
				showLine:true,
				borderDash: [],
				yAxisID: 'y-axis',
				data: []
			};

	var datasetRef2 = {
				label: 'Reference 2',
				backgroundColor: "yellow",
				borderColor: "yellow",
				display:false,
				borderWidth: 1,
				pointRadius: 1,
				spanGaps: false,
				fill: false,
				showLine:true,
				borderDash: [],
				yAxisID: 'y-axis',
				data: []
			};

	// scope data for channel 1
	if (HamegSetting.ch1.enabled)
	{
		var ch1  = convertWaveform(HamegSetting.data.channel1);
		pushDataSet(ChartConfig, ch1, datasetChannel1);
	}

	// scope data for channel 2
	if (HamegSetting.ch2.enabled)
	{
		var ch2  = convertWaveform(HamegSetting.data.channel2);
		pushDataSet(ChartConfig, ch2, datasetChannel2);
	}

	// reference1 signal
	var ref1 = convertWaveform(HamegSetting.data.reference1);
	pushDataSet(ChartConfig, ref1, datasetRef1);

	// reference2 signal
	var ref2 = convertWaveform(HamegSetting.data.reference2);
	pushDataSet(ChartConfig, ref2, datasetRef2);

	ChartObj.update();
}

function toolTipTimeValue(ItemList)
{
	return toSecondDisplay(ItemList[0].xLabel);
}

function toolTipFunc(tooltipItem, data)
{
	var ChannelName = data.datasets[tooltipItem.datasetIndex].label || '';

	var Factor = HamegSetting.ch1.voltDiv_mV;;
	var YPosition = HamegSetting.ch1.yPosition/1000.0;
	if (ChannelName === "Channel 2")
	{
		Factor = HamegSetting.ch2.voltDiv_mV;;
		YPosition = HamegSetting.ch2.yPosition/1000.0;
	}

	label = (tooltipItem.yLabel-YPosition) * Factor;
	if (label>=500.0)
		return ChannelName+": "+(label/1000.0).toFixed(3)+" V";
	return ChannelName+": "+label.toFixed(2)+" mV";
}

