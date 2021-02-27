#include <SPI.h>
#include <MFRC522.h>
#include "SoftwareSerial.h"
#define SS_PIN 2
#define RST_PIN 0
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create a MFRC522 object.

#include<ESP8266WiFi.h>
#include"Adafruit_MQTT_Client.h"
char attendance1[100] = "Rishikesh(RA1911003010720) is present!";
char attendance2[100] = "Aditya(RA1911003010710) is present!";
#define wifi "OnePlus 8T"
#define password "12345678"
#define server "io.Adafruit.com"
#define led 16
#define port 1883
#define username "rishusiva"
#define key "aio_CIoK72CNdVcqwnB7AYkpk1B6AqQz"
WiFiClient esp;
Adafruit_MQTT_Client mqtt(&esp,server,port,username,key);
Adafruit_MQTT_Publish feed=Adafruit_MQTT_Publish(&mqtt,username"/feeds/RFID_Attendance");


void setup() 
{
  Serial.begin(9600);   // Initiate the serial communication
  SPI.begin();      // Initiate the SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("PLEASE PUT RFID TAG IN FRONT OF THE SCANNER...");
  Serial.println();

  delay(10);
Serial.println("Adafruit MQTT demo");
Serial.println("Connecting to");
Serial.println(wifi);
WiFi.begin(wifi,password);
while(WiFi.status()!=WL_CONNECTED)
{delay(500);
Serial.println(".");
}
Serial.println("wifi connected");
Serial.println("ip adress");
Serial.println(WiFi.localIP());
Serial.println("connecting to mqtt");

while(mqtt.connect())
{Serial.println(".");}
pinMode(led,OUTPUT);

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Name and Roll number:    ");
  content.toUpperCase();
  if (content.substring(1) == "71 63 FF D3" ) //change here the UID of the card
  {
    Serial.println("Rishikesh(RA1911003010720)");
    Serial.println();
    if(mqtt.connected()){
      Serial.println("sending data");
Serial.println("....");
if(feed.publish(attendance1))
{Serial.println("success");
}
else
{Serial.println("fail");}
delay(2200);
}
    }
    delay(3000);
  
   if (content.substring(1) ==  "A9 F3 CF 83" ) //change here the UID of the card
   { Serial.println("Aditya(RA1911003010710)");
    Serial.println();
    if(mqtt.connected()){
      Serial.println("sending data");
Serial.println("....");
if(feed.publish(attendance2))
{Serial.println("success");
}
else
{Serial.println("fail");}
delay(2200);
}
    delay(3000);
  }
  
  }
