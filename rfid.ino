#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

//This program does the work of recognizing rfid tags using the reader
//The rfid reader/writer module is the mfrc522 rfid module.

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

byte id[4]={0x96, 0x0E, 0xA1, 0x5F};
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
Servo mmservo;
void setup() {
  mmservo.attach(5);
  mmservo.write(0);
	Serial.begin(9600);		// Initialize serial communications with the PC
	while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
	delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void wave()     //The servo motor does a "Hi!" like wave motion on reading a recognized tag.
{
  int i;
  for(int i=0;i<60;i++)
  {mmservo.write(i);delay(1);}
  for(int i=60;i>0;i--)
  {mmservo.write(i);delay(1);}
}

void loop() {
	// Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}

	// Select one of the cards
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}
  if(mfrc522.uid.uidByte[0]==id[0] && mfrc522.uid.uidByte[1]==id[1] && mfrc522.uid.uidByte[2]==id[2] && mfrc522.uid.uidByte[3]==id[3])
  {
    wave();
    Serial.print("This belongs to Sai Harshit Balaji\n");
  }
  else
  {
    Serial.print("Not Recognised\n");
  }
  
	mfrc522.PICC_HaltA();
}
