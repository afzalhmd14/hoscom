#include <RF24Network_config.h>
#include <RF24Network.h>
#include <Sync.h>
#include<SoftwareSerial.h>

SoftwareSerial mySerial(2,3);

#include <RF24_config.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <SPI.h>

const uint16_t this_node=0;
const uint16_t other_node=1;

unsigned long last_sent=0;
unsigned long packets_sent=0;

RF24 radio(9,10);
RF24Network network(radio);

struct payload_t
{
  int lol;
  char packet;
};

RF24NetworkHeader header(other_node);
payload_t payload={0,' '};

int omg=0;

void setup()
{
  Serial.begin(115200);
  SPI.begin();
  mySerial.begin(115200);

  radio.begin();
  network.begin(120,this_node);
  Serial.read();
  
}

bool success=0;

void loop()
{

  network.update();
  if(Serial.available())
  {
    
   // payload.lol=27;
    payload.packet=Serial.read();
    //mySerial.write(payload.packet);
    success=network.write(header,&payload,sizeof(payload));
    if(omg==0)
    {
      payload.lol=0;
      for(int i=0;i<100;++i)
      {
        network.update();
        network.write(header,&payload,sizeof(payload));
      }
      omg=10;
    }
    payload.lol=27;
    if(!success)
    {
      while(!success)
        network.write(header,&payload,sizeof(payload));
      //Serial.println("Packet sent successfully ");
    }
  }
}

