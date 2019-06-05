# WirelessMeshNetwork_RemoteLightControl
WirelessMeshNetwork_RemoteLightControl Implemented on Arduino development board

System Architecture

The system is made up of the following hardware components Multiprotocol Radio Shield, Arduino development board, XBee S2 module, XBee Explorer boards, XCTU tool, LCD Screen (compatible with Hitachi HD44780 driver), LDR (Light Dependent Resistor), Resistor (100k; 220-ohm;330ohm) and LED (Light Emitting Diode).


The ZigBee Mesh Kit (Part Number: XKB2-Z7T-WZM) from www.digi.com is used in this project.  The XBee radios Series 2 model (note that a series 1 model only allows communication between a maximum of 2 modules) is used. The kit comes with 3 XBee radios included. In terms of expansion, the system is modular making it possible to add more radios as needed. The second part involves the use of Arduino development board to implement the ZigBee Network using the XBees RF modules. The program XCTU is used to configure the XBee radios to create the ZigBee Mesh Network. Once the XCTU program is installed, next step is to plug one of your XBee radios into one of the explorer boards provided in the mesh kit, then connect the explorer board to your PC with the included cable and you can configure the radio.


Arduino and ZigBee Interface

Coordinator and End-device – The coordinator and end-device XBee configured modules are implemented on the Arduino development board. The Coordinator is implemented as a receiver, while the end-device is implemented as a transmitter to which a sensor (temperature or LDR) is connected. The Routers are mounted on the XBee explorer board.

In total we have six (6) XBee Radios, one XBee is configured as a Coordinator in API mode with API enable set to 2 (it will use escape characters along with the data) and interfaced with the Arduino. Another XBee device is configured as an End-Device in AT mode (Transparent mode) and interfaced with the Arduino. SoftwareSerial of Arduino is used for communication with XBee. Serial of Arduino is used to display the received data on the serial monitor.

The Routers are configured in API mode with API enable set to 2 (it will use escape charac-ters along with the data). The same API enable setting must be used for all the XBee devices configured in API mode. The Routers are left mounted on the XBee explorer board.
