#include<SPI.h>
#include<MFRC522.h>
#define SS_PIN 53
#define RST_PIN 49
#define echoPinA 8
#define trigPinA 9
#define echoPinB 10
#define trigPinB 11



const int RELAY_PIN = 3;  
const int RELAY_PIN2 = 5;
int buttonState = 0;
long timpA,timpB,timpC;
int distantaA,distantaB,distantaC;

MFRC522 mfrc522(SS_PIN, RST_PIN);

void Send_RFID_to_BLUETOOTH()
{
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

  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  content.toUpperCase();

  if (content.substring(1) == "65 8F DB 21") //change here the UID of the card/cards that you want to give access
  {
    Serial.print("1");
  }
  if (content.substring(1) == "A9 B9 3B 94") {
    Serial.print("0");

  }
}


void senzorA()
{
  digitalWrite(trigPinA, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPinA, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinA, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  timpA = pulseIn(echoPinA, HIGH);
  // Calculating the distance
  distantaA = timpA * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
}


  void senzorB()
  {
    digitalWrite(trigPinB, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPinB, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinB, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    timpB = pulseIn(echoPinB, HIGH);
    // Calculating the distance
    distantaB = timpB * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  }


void setup() {
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.begin(38400); // Default communication rate of the Bluetooth module
  
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(RELAY_PIN2, OUTPUT);

  pinMode(trigPinA, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPinA, INPUT); // Sets the echoPin as an INPUT
  
  pinMode(trigPinB, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPinB, INPUT); // Sets the echoPin as an INPUT
  
 
}

void loop() {
  
  Send_RFID_to_BLUETOOTH();
  
  if (distantaA <= 15)
  {
    digitalWrite(RELAY_PIN, HIGH);
    delay(10000);
    digitalWrite(RELAY_PIN, LOW);
  }
  else if (distantaB <= 15)
  {
    digitalWrite(RELAY_PIN2, HIGH);
    delay(10000);
    digitalWrite(RELAY_PIN2, LOW);
  }

}
