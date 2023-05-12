#include <LoRa.h>
#include <SPI.h>

// define LoRa parameters
#define BAND 433E6
#define SS_PIN 15
#define RST_PIN 16
#define DI0_PIN 4
#define trigPin 0
#define echoPin 5

 long duration;  
 int distance;  
 String data = "";
// define traffic light parameters
#define RED_PIN_Y 2

void setup() 
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Device Activated"); 
  LoRa.setPins(SS_PIN, RST_PIN, DI0_PIN); // initialize LoRa module
  if (! LoRa.begin(433E6)) 
  {
    Serial.println("LoRa init failed");
    delay (100);
    while (1);
  }
   data.reserve(200);

  pinMode (RED_PIN_Y, OUTPUT);
  //pinMode(GREEN_PIN_Y, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output  
  pinMode(echoPin, INPUT); 
}

void loop() 
{ 
  digitalWrite(RED_PIN_Y,LOW);
  int packetSize = LoRa.parsePacket();
  if(packetSize)
  {
    String received = "";
    Serial.print("Message Received : ");
    while(LoRa.available())
    {
      received+=(char)LoRa.read();
    }
    Serial.println(received);
    digitalWrite (RED_PIN_Y, HIGH);
    delay (2000);
  }
}

