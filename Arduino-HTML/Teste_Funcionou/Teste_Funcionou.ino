#include "etherShield.h"
#include "ETHER_28J60.h"

int PinoLed = 7;

static uint8_t mac[6] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x24};
static uint8_t ip[4] = {192,168,0,114};
static uint16_t port = 80;

ETHER_28J60 server;

void setup()
{
  server.setup(mac, ip, port);
  pinMode(PinoLed, OUTPUT);
}

void loop()
{
  char* params;
  if (params = server.serviceRequest())
  {
    server.print("<h1><a href='/?led=off'>Servidor Web Embarcado</a></h1>");
    if (strcmp(params, "?led=on") == 0)
    {
      digitalWrite(PinoLed, HIGH);
      server.print("<a href='?led=off'><button style='border: 1px solid #ff0000; border-left: 10px solid #ff0000' type='button'>LED LIGADO</button></a>");
    }
    else if (strcmp(params, "?led=off") == 0)
    {
      digitalWrite(PinoLed, LOW);
      server.print("<a href='?led=on'><button style='border: 1px solid #000; border-left: 10px solid #000' type='button'>LED DESLIGADO</button></a>");
    }
    server.respond();
  }
}

