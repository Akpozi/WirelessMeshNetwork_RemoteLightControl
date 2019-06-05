#include <XBee.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <multiprotocolShield.h>
#include <Wire.h>
#include <MCP23008.h>
#define ssRX  2 /* Rx pin for software serial */
#define ssTX  3 /* Tx pin for software serial */
int ledBlink = 10;
#define relay 12
int LED = 10;
int LDR = A0;
String lightON = "It's Dark Outside; Lights status: ON";
String lightOFF = "It's Bright Outside; Lights status: OFF";
LiquidCrystal lcd(9, 8, 7, 6, 5, 4);
/* Create object named xbee_ss of the class SoftwareSerial */ 
/* Define pins for software serial instance named xbee-ss(any name of your choice) to be connected to xbee */
/* ssTx of Arduino connected to Din (pin 3 of xbee) */
/* ssRx of Arduino connected to Dout (pin 2 of xbee) */
SoftwareSerial xbee_ss(ssRX, ssTX); 
// Create an instance of the object
// Variables
long unsigned int rxCANId;
unsigned char len = 0;
unsigned char TxLDRValue[1];
XBeeAddress64 addr64 = XBeeAddress64(0x0013A200, 0xFFFF);
ZBTxRequest zbTx = ZBTxRequest(addr64, TxLDRValue, sizeof(TxLDRValue));

XBee xbee = XBee();

void setup() 
{
Serial.begin(9600);
xbee_ss.begin(9600); /* Define baud rate for software serial communication */
xbee.setSerial(xbee_ss);
pinMode(LED, OUTPUT);
pinMode(relay, OUTPUT);
pinMode(LDR, INPUT);
lcd.begin(16, 2);
XBeeConfigSend();
}

void loop()
{
int LDRValue = analogRead(LDR);
int j,m,index, indi, numb=sizeof(TxLDRValue);
index=0; indi=0;
// Put LDRValue into TxLDRValue
      for(m = 0; m<numb; m++) 
      {
        TxLDRValue[index] = LDRValue;
        index++;
      }
        Serial.print("sensor Value = ");
      for(m = 0; m<numb; m++) 
      {
        Serial.print(TxLDRValue[m]);
      }
        Serial.println(" ");
        xbee.send(zbTx);
        delay(100);
/*****************************************************************
BLINK LED to indicate TRansmission is ONGOING
******************************************************************/
if (LDRValue !=0) 
{
    digitalWrite(ledBlink, HIGH);
    delay(100);
    digitalWrite(ledBlink, LOW);
    Serial.println(" ");
}
/*****************************************************************
Send Command to TURN Lights ON Remotely if LDRValue <=70
******************************************************************/
if (LDRValue <=70) 
{
//digitalWrite(LED, HIGH);
//digitalWrite(relay, HIGH);
Serial.println(lightON);
Serial.println(".......................................................... ");
Serial.println(" ");
/*****************************************************************
LCD Display code
******************************************************************/
    lcd.setCursor(0, 0);
    lcd.print("Light Status: ");
    lcd.setCursor(0, 1);
    lcd.print("Lights are on_");
}
else
/*****************************************************************
Send Command to Turn OFF the Lights Remotely if LDRValue > 70
******************************************************************/ 
  {
Serial.println(lightOFF);
Serial.println(".......................................................... ");
Serial.println(" ");
/*****************************************************************
LCD Display code
******************************************************************/
    lcd.setCursor(0, 0);
    lcd.print("Light Status: ");
    lcd.setCursor(0, 1);
    lcd.print("Lights are off");
  }
}

void XBeeConfigSend()
{
  socket1.ON();
  delay(100);
  socket1.setMUX(); // <------ Configure the MUX at MUX0
  Serial.begin(9600);
  delay(1000);
}
/************************
  END OF FILE
************************/
