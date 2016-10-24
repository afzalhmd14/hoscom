#include <RF24Network_config.h>
#include <RF24Network.h>
#include <Sync.h>

#include <RF24_config.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <SPI.h>

RF24 radio(9,10);
RF24Network network(radio);

const uint16_t this_node=1;

RF24NetworkHeader header;

struct payload_t
{
  int lol;
  char packet;
} payload;

char a=' ';

void setup()
{
  radio.begin();
  network.begin(120,this_node);
  Serial.begin(115200);
  SPI.begin();
  //Serial.print(a);
  //Serial.println("Initialising receiving end.........");
}

void loop()
{
  network.update();
  if(network.available())
  {
    network.read(header,&payload,sizeof(payload));
    if(payload.lol==27)
      Serial.print(payload.packet);
  }
}
