#include "etherShield.h"
#include "ETHER_28J60.h"

int PinoLed = 7;
int PinoLed2 = 6;

static uint8_t mac[6] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x24};
static uint8_t ip[4] = {192,168,0,114};
static uint16_t port = 80;

ETHER_28J60 server;

void setup()
{
  Serial.begin(9600);
  server.setup(mac, ip, port);
  pinMode(PinoLed, OUTPUT);
  pinMode(PinoLed2, OUTPUT);
}

void loop()
{
  int temperatura;
  temperatura = analogRead(A1);
  char* params;
  if (params = server.serviceRequest())
  {
    server.print("<h1><a href='/?led=off&ar=off'>Controle Remoto</a></h1>"); 
    server.print(temperatura);
    Serial.println(temperatura);
    if (strcmp(params, "?led=on&ar=on") == 0)
    {
      digitalWrite(PinoLed, HIGH);
      server.print("<a href='?led=off&ar=on'><button style='border: 1px solid #ff0000; border-left: 10px solid #ff0000' type='button'>LED LIGADO</button></a>");
      digitalWrite(PinoLed2, HIGH);
      server.print("<a href='?led=on&ar=off'><button style='border: 1px solid #ff0000; border-left: 10px solid #ff0000' type='button'>AR LIGADO</button></a>");
    }
    else if (strcmp(params, "?led=off&ar=off") == 0)
    {
      digitalWrite(PinoLed, LOW);
      server.print("<a href='?led=on&ar=off'><button style='border: 1px solid #000; border-left: 10px solid #000' type='button'>LED DESLIGADO</button></a>");
      digitalWrite(PinoLed2, LOW);
      server.print("<a href='?led=off&ar=on'><button style='border: 1px solid #000; border-left: 10px solid #000' type='button'>AR DESLIGADO</button></a>");
    }
    else if (strcmp(params, "?led=on&ar=off") == 0)
    {
      digitalWrite(PinoLed, HIGH);
      server.print("<a href='?led=off&ar=on'><button style='border: 1px solid #ff0000; border-left: 10px solid #ff0000' type='button'>LED LIGADO</button></a>");
      digitalWrite(PinoLed2, LOW);
      server.print("<a href='?led=off&ar=on'><button style='border: 1px solid #000; border-left: 10px solid #000' type='button'>AR DESLIGADO</button></a>");
    }
        else if (strcmp(params, "?led=off&ar=on") == 0)
    {
      digitalWrite(PinoLed, LOW);
      server.print("<a href='?led=on&ar=off'><button style='border: 1px solid #000; border-left: 10px solid #000' type='button'>LED DESLIGADO</button></a>");
      digitalWrite(PinoLed2, HIGH);
      server.print("<a href='?led=on&ar=off'><button style='border: 1px solid #ff0000; border-left: 10px solid #ff0000' type='button'>AR LIGADO</button></a>");
    }
    server.respond();
  }
}

