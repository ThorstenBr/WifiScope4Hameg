# ESP8266 WiFi Interface for Hameg Oscilloscopes
This project creates a WiFi adapter for Hameg Analog/Digital Oscilloscopes using a ESP8266 WiFi module (Wemos D1 mini).

![Concept](/Images/setup.png)

The German company "Hameg Instruments" made good quality analog oscilloscopes. Eventually their product line included analog/digital combi-scopes. (They have since been acquired by Rohde & Schwarz, who now own but discontinued the Hameg brand).

The later Hameg models feature an RS232 remote interface, which allows controlling the scope and capturing measurement data using a PC. The RS232 interface was originally used by their PC software, which was desgined for Windows 98.

Instead of using the original PC software, I added new life to my Hameg scope by using an ESP8266 WiFi module (Wemos D1 mini), connecting it to the RS232 port of the Hameg scope.
The ESP is programmed using the Arduino environment and provides a simple web API (JSON) and a browser web interface.

The web API provides access to the raw measurement data and allows to control the scope. The browser interface provides a simple GUI to view and control.
Currently, not all scope features are exposed via the browser GUI, though the main features should be available.
I'm adding missing features every now and then, when I need something - but don't expect massive changes.
The interface is easily extended by anyone familiar with the Arduino environment and web/javascript skills.
The documentation of Hameg's RS232 protocol is easily found on the web. The protocol is a little clunky.

According to the Hameg protocol documentation, the following of their scopes did support the RS232 remote control interface:
* HM305-2
* HM404, HM404-2, HM407, HM407-2
* HM1004-2, HM1004-2A, HM1004-3
* HM1505-2
* HM1507, HM1507-2, HM1507-3
* HM2005

Possibly there are further supported Hameg scopes (likely any later Hameg combi-scope models - if there were any...).

# License & Legal
* This project is released under the "GNU General Public License 3.0". See [LICENSE](/LICENSE).
* "Hameg" is a registered trademark now owned by Rohde & Schwarz. This project is not affiliated nor endorsed in any way by Hameg/Rohde & Schwarz.

# How it looks
The WiFi module provide a web API and a simple browser interface. The interface provides push-buttons and drop-down selectors for configuration.

This is an example of how the browser interface looks:
![Example browser GUI](/Images/AppleII_PAL_capture.png)

# Building the Interface

## What you need
To create the WiFi interface you need the following:

* A "Wemos D1 mini", ESP8266 WiFi module.
* An RS232-TTL level shifter, converting the 12V RS232 signals to 3.3V TTL for the ESP8266. Search for "RS232 TTL converter" or "MAX3232 module" on ebay. These modules provide 2 TTL inputs + 2 TTL outputs, connecting to 2 RS232 outputs and 2 RS232 inputs (so it's converting _two_ signals in each direction).
* A DB9 male connector with matching housing.

![Required Parts](/Images/required_parts.jpg)

Oh, and obviously you also need a Hameg oscilloscope...
Hameg's analog/digital combi-scopes did support the RS232 remote control port (see above for supported models).
![Required Parts](/Images/hameg_scope.jpg)

The scope's RS232 connector is at its rear:
![Required Parts](/Images/remote_port.jpg)

## Making Connections
The required connections are pretty simple:
* The MAX3232 level shifter module's power pins are connected to **GND** and **3.3V** of the ESP8266 module.
* The two TTL inputs of the MAX3232 level shifter are connected to the ESP's **D6** and **D8** pins.
* The two RS232 outputs of the MAX3232 are connected to the DB9 connector **pin 7** (RTS) and **pin 3** (TXD) respectively.
* One of the RS232 inputs of the MAX3232 is connected to the DB9 connector **pin 2** (RXD).
* The TTL output of the MAX3232 is connected to ESP's pin **D7**.

| ESP8266                | MAX3232: TTL side     | - | MAX3232: RS232 side      | DB9 RS232 connector |
|------------------------|-----------------------|---|--------------------------|---------------------|
| **GND**                | **GND**               |   | **GND**                  | **pin 5** (GND)
| **3V3** (*not 5V!*)    | **VCC**               |   | -                        | -
| **D8** (TXD)           | **TTL in 1** (top)    |   | **RS232 out 1** (top)    | **pin 3** (TXD)
| **D7** (RXD)           | **TTL out 1** (top)   |   | **RS232 in 1** (top)     | **pin 2** (RXD)
| **D6** (RTS)           | **TTL in 2** (bottom) |   | **RS232 out 2** (bottom) | **pin 7** (RTS)

![Required Parts](/Images/connections.png)

### Important ###
Please note these hints to avoid confusion:

* Do not use 5V to power the level shifter. The ESP8266 expects 3.3V I/O signals. Use the 3V3 pin to connect the MAX3232 module's VCC.
* Do not mix up the TTL and RS232 side of the MAX3232 module. The module is immediately destroyed if a TTL pin was connected to an RS232 (12V) signal (don't ask me how I would know... :-) ).
* Do not use the ESP pins labeled "TX" and "RX". These are already connected to the module's onboard USB host device (CH340). They cannot be used for the Hameg RS232 connection. Hence, D7 and D8 are used for the RXD/TXD connection to the Hameg scope instead.
* A simple two-wire TX/RX connection does not suffice. The Hameg device also requires RTS. The common trick of simply looping CTS + RTS locally at the DB9 connector also does _not_ work. The Hameg interface will not accept commands unless a proper RTS signal is provided.
* The MAX2323 modules ("China modules") have 4 GND and 4 Vcc connector pads (top & bottom side, TTL & RS232 side). All GND and all VCC pads are connected - it doesn't matter which GND or which VCC pads you use.
* These MAX2323 modules also provide one input and one output at each side - on the top and on the bottom. The top/bottom inputs/outputs are _not_ connected and refer to separate input/output signals. Hence, they support _two_ inputs and _two_ outputs in each direction.

## Configuring the Device
The WiFi module needs configuration data: the WiFi SSID & password. You should also set a hostname and configure the port for the web/browser interface (like port 80 or 8080 etc).

There are two options to configure the device:

* Program the prebuilt firmware to your ESP device. Then use a terminal to connect to the emulated UART interface of the ESP to configure the device (115200baud, 8N1). Send "..." (three dots) to enter the interactive configuration mode and the device shows a simple menu. Use the menu options 1-4 to set all properties. These settings are stored in the EEPROM (non-volatile memory) of your device.
![Terminal Configuration Menu](/Images/terminal_config.png)

* _Alternatively_, you can disable the EEPROM configuration and enter all configuration settings directly in the sources. Edit your local file [WifiScopeConfig.h](/WifiScope/WifiScopeConfig.h) to enter the data for your network, and remove (or comment out) the line "#define FEATURE_USE_EEPROM_CONFIG". Then recompile with the Arduino environment.
![Alternate Fixed Configuration](/Images/code_config.png)

# Using the WiFi Adapter

## Browser Interface
Once the device is set up and connected to your WiFi, you can access the browser interface using the IP address (assigned by your WiFi router) or the hostname (configured as described above).
* The default device name is "hameg". You may need to replace it with your custom hostname (or the IP address assigned by your WiFi router) in the URLs below.
* The default server port is 80.
* Make sure to use "http://" rather than "https://" for any connections.

Default URL to the browser interface:
* `http://hameg`
* `http://hameg:80`

## Scripting
You can access the scope's raw data through a web API, returning a JSON data structure.

Default access to the JSON data:
* `http://hameg/data`

Alternatively you can access the measurement data as a CSV data structure:
* `http://hameg/csv` or `http://hameg/csv?channel=1` returns CSV data for channel 1.
* `http://hameg/csv?channel=2` returns CSV data for channel 2.
* `http://hameg/csv?channel=3` returns CSV data for reference storage #1.
* `http://hameg/csv?channel=4` returns CSV data for reference storage #2.

The following URL is used to send commands to the scope. It expects one (or multiple) "parameter=value" style parameters.
* `http://hameg/set?...=...` to change scope settings.

However, I'm currently not documenting these parameters and the value encodings here.
This is *out of scope* (excuse the pun... :-) ).
Please have a look at the Arduino sources or the JavaScript code as an example.

The CSV data (currently) only contains the raw Y-axis data for each measurement (8bit ADC values).
You will need to access the JSON data to obtain the properties for scaling (offset/gain, timebase).
(The ESP8266's memory is a little limited, so it's easier to do the scaling of data on the host PC, rather than on the tiny ESP8266).

# Limitations
The remote control port of the Hameg devices works well (is very stable).
The protocol, however, is a little clunky.

The concept for commands and replies is a bit inconsistent. It mixes an ASCII-style command interface with binary elements. Some commands/replies use line-endings as delimiters (\r\n), others just don't (the controller needs to count the bytes).
The remote protocol exposes many scope properties only in combination with other (unrelated) properties.
All this makes the implementation of even simple settings a little more tricky than you'd expect from modern device protocol.

The scope's internal controller handles the device's frontend and the RS232 communication - and it can only handle either at a time.
So, the scope's buttons/switches do not respond (briefly) whenever the device is communicating over RS232.

Even if the remote control port is running at 115200 baud, the communication with the scope is a little slow. Do not expect instant (real-time) updates of the brower's measurement display. Configuration changes may also need a moment before the effect is visible.

It's pretty clear that Hameg saw the remote interface as a nice addition at the time - and not as a primary feature.
For some complex manual measurement setups you will still find it more convenient to use the scope's native control buttons.
However, the WiFi option to control the device remotely, and to grab measurement data for post-processing, is still a nice addition - and will extend the life of my scope for a while...

