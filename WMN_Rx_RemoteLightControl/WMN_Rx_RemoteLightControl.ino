#include <XBee.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <multiprotocolShield.h>
#include <Wire.h>
#include <MCP23008.h>
#define ssRX  2 /* Rx pin for software serial */
#define ssTX  3 /* Tx pin for software serial */
int motorPin = 12;
#define relay 11
int LED = 10;
int LDR = A0;
int dataLenght = 20;
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
unsigned char len = 0;
XBee xbee = XBee(); /* Create an object named xbee(any name of your choice) of the class XBee */
//>>>>>>>>>>>>>>API Mode Variables starts...
XBeeResponse response = XBeeResponse();
ZBRxResponse rx = ZBRxResponse();

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
  String sample;
  unsigned char RxLDRValue[1];
  /*****************************************************************
        READ and FORMAT Incoming Packets
  ******************************************************************/
  xbee.readPacket(); /* Read until a packet is received or an error occurs */
  if (xbee.getResponse().isAvailable()) /* True if response has been successfully parsed and is complete */
  {
    Serial.println(".......................................................... ");
    Serial.print("receiving End Device Data with ApiId: ");
    Serial.println(xbee.getResponse().getApiId());
    //Serial.println(rx.getDataLength());
    if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE)
    {
      xbee.getResponse().getZBRxResponse(rx);
      for (int i = 0; i < rx.getDataLength() ; i++)
      {
        RxLDRValue [i] = rx.getData(i);
        sample += (char)rx.getData(i);
      }
      /*****************************************************************
        BLINK LED to indicate Reception of Incoming Data
      ******************************************************************/
      if (rx.getDataLength() != 0)
      {
        digitalWrite(relay, HIGH);
        delay(10);
        digitalWrite(relay, LOW);
      }
      /*****************************************************************
          Print "Received LDR Value" to Serial Monitor
      ******************************************************************/
      if ((rx.getDataLength() >= dataLenght))
      {
        for (int i = 0; i < 1; i++)//(int i = 0; i < rx.getDataLength(); i++)
        {
          Serial.println(" ");
          Serial.print("Received LDR Value = ");
          Serial.print(RxLDRValue[i]);
        }
        Serial.println(" ");
        /*****************************************************************
          Turn ON the Lights and motor (Fan) if (RxLDRValue[0] <=70)
        ******************************************************************/
        analogWrite(motorPin, 0);//set to initialize motor speed to zero
        if (RxLDRValue[0] <= 70)
        {
          digitalWrite(LED, HIGH);
          digitalWrite(relay, HIGH);
          analogWrite(motorPin, 130);//set to turn motor
          Serial.println(lightON);
          Serial.println(".......................................................... ");
          Serial.println(" ");
          /*****************************************************************
            LCD Display code
          ******************************************************************/
          lcd.setCursor(0, 0);
          lcd.print("Light Status:   ");
          lcd.setCursor(0, 1);
          lcd.print("Lights are on_  ");
        }
        else
          /*****************************************************************
            Turn OFF the Lights and motor (Fan)if (RxLDRValue[0] > 70)
          ******************************************************************/
        {
          digitalWrite(LED, LOW);
          digitalWrite(relay, LOW);
          Serial.println(lightOFF);
          Serial.println(".......................................................... ");
          Serial.println(" ");
          /*****************************************************************
            LCD Display code Sensor Node Data (LDR)
          ******************************************************************/
          lcd.setCursor(0, 0);
          lcd.print("Light Status:   ");
          lcd.setCursor(0, 1);
          lcd.print("Lights are off  ");
        }
      }
      /*****************************************************************
            Print Router 3 Data to Serial Monitor
      ******************************************************************/
      else if (sample.length() <= 20)
      {
        Serial.println(" ");
        Serial.print("Router 3 Data: ");
        Serial.print(sample);
        Serial.println(" ");
        Serial.println(".......................................................... ");
        /*****************************************************************
          LCD Display of Router 3 Data
        ******************************************************************/
        lcd.setCursor(0, 0);
        lcd.print("Router 3 Data:     ");
        lcd.setCursor(0, 1);
        lcd.print(sample);
        delay(100);
      }
    }
  }
  /* If error detected, print the error code */
  else if (xbee.getResponse().isError())
  {
    Serial.print("Error reading packet.  Error code: ");
    Serial.println(xbee.getResponse().getErrorCode());
  }
  /* error detection ends*/
  //         else
  //         {
  //            Serial.println(".......................................................... ");
  //            Serial.print("No Incoming Data");
  //            lcd.setCursor(0, 0);
  //            lcd.print("No Incoming Data ");
  //            lcd.setCursor(0, 1);
  //            lcd.print("CheckSensorNodes   ");
  //            Serial.println(" ");
  //            Serial.println(".......................................................... ");
  //         }
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
