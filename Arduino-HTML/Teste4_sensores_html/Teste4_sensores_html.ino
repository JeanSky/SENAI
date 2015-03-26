#include "etherShield.h"
#include "ETHER_28J60.h"

int PinoLed = 7;
int botao1 = 2;
int botao2 = 4;
int bot1, bot2;
int LM = A0;
int LDR = A1;
float tempC, tensaoEq, valorLM, valorLDR;
char* iluminacao;

static uint8_t mac[6] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x24};
static uint8_t ip[4] = {192,168,0,114};
static uint16_t port = 80;

ETHER_28J60 server;

void setup()
{
  server.setup(mac, ip, port);
  pinMode(PinoLed, OUTPUT);
  pinMode(botao1, INPUT);
  digitalWrite(botao1, HIGH);
  pinMode(botao2, INPUT);
  digitalWrite(botao2, HIGH);
}

void loop()
{
  bot1 = digitalRead(botao1);
  bot2 = digitalRead(botao2);
  valorLM = analogRead(LM);  
  tensaoEq = ((valorLM * 5)/1024);
  tempC = ((tensaoEq * 150)/5);
  valorLDR = analogRead(LDR);
  if (valorLDR < 300)
  {
    iluminacao = ("As lampadas estao apagadas!");
  }
  else if (valorLDR > 300)
  {
    iluminacao = ("As lampadas estao acesas!");
  }
  
  
  char* params;

      if (bot1 == 0)
    {
      digitalWrite(PinoLed, HIGH);
    }
     if (bot2 == 0)
    {
      digitalWrite(PinoLed, LOW);
    } 

  if (params = server.serviceRequest())
  {

    server.print("<h1><a href='/?led=off'>Iluminacao</a></h1>");
    server.print("<META HTTP-EQUIV='REFRESH' CONTENT='2.5'>");

     if ((strcmp(params, "?led=on") == 0) && (bot2 == 0))
    {
      digitalWrite(PinoLed, LOW);
      server.print("<META HTTP-EQUIV='REFRESH' CONTENT='0.3; http://192.168.0.114/?led=off'>");
      server.print("<a href='?led=on'><button style='border: 1px solid #000; border-left: 10px solid #000' type='button'>LED DESLIGADO</button></a>");
      server.print("<p>A temperatura eh:  ");
      server.print(tempC);
      server.print("<p>");
      server.print(iluminacao);
    }
  
    else if ((strcmp(params, "?led=on") == 0) || (bot1 == 0))
    {
      digitalWrite(PinoLed, HIGH);
      server.print("<META HTTP-EQUIV='REFRESH' CONTENT='0.3; http://192.168.0.114/?led=on'>");
      server.print("<a href='?led=off'><button style='border: 1px solid #ff0000; border-left: 10px solid #ff0000' type='button'>LED LIGADO</button></a>");
      server.print("<p>A temperatura eh:  ");
      server.print(tempC);
      server.print("<p>");
      server.print(iluminacao);
    }
    else if ((strcmp(params, "?led=off") == 0) || (bot2 == 0))
    {
            digitalWrite(PinoLed, LOW);
      server.print("<META HTTP-EQUIV='REFRESH' CONTENT='0.3; http://192.168.0.114/?led=off'>");
      server.print("<a href='?led=on'><button style='border: 1px solid #000; border-left: 10px solid #000' type='button'>LED DESLIGADO</button></a>");
      server.print("<p>A temperatura eh:  ");
      server.print(tempC);
      server.print("<p>");
      server.print(iluminacao);
    }
  
    server.respond();
  }
}

