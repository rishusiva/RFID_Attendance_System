#include <SPI.h>
#include <MFRC522.h>
#include "SoftwareSerial.h"
#define SS_PIN 2
#define RST_PIN 0
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create a MFRC522 object.
void setup() 
{
  Serial.begin(9600);   // Initiate the serial communication
  SPI.begin();      // Initiate the SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("PLEASE PUT RFID TAG IN FRONT OF THE SCANNER...");
  Serial.println();

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
    delay(3000);
  }
   if (content.substring(1) ==  "A9 F3 CF 83" ) //change here the UID of the card
   { Serial.println("Aditya(RA1911003010710)");
    Serial.println();
    delay(3000);
  }
  
  }
