#include "etherShield.h"
#include "ETHER_28J60.h"

int PinoLed = 7;
int PinoLed2 = 6;
int botao1 = 2;
int botao2 = 4;
int botao3 = 3;
int botao4 = 5;
int bot1, bot2, bot3, bot4;
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
  pinMode(PinoLed2, OUTPUT);
  pinMode(botao1, INPUT);
  digitalWrite(botao1, HIGH);
  pinMode(botao2, INPUT);
  digitalWrite(botao2, HIGH);
  pinMode(botao3, INPUT);
  digitalWrite(botao3, HIGH);
  pinMode(botao4, INPUT);
  digitalWrite(botao4, HIGH);
  
}

void loop()
{
  bot1 = digitalRead(botao1);
  bot2 = digitalRead(botao2);
  bot3 = digitalRead(botao3);
  bot4 = digitalRead(botao4);
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


  if (params = server.serviceRequest())
  {

      if (bot1 == 0)
    {
      digitalWrite(PinoLed, HIGH);
     }
     if (bot2 == 0)
    {
      digitalWrite(PinoLed, LOW);
    } 
     if (bot3 == 0)
    {
      digitalWrite(PinoLed2, LOW);
    } 
     if (bot4 == 0)
    {
      digitalWrite(PinoLed2, LOW);
    } 

    server.print("<h1><a href='/?led=off&ar=off'>Controle Remoto</a></h1>"); 
    server.print("<META HTTP-EQUIV='REFRESH' CONTENT='2.5'>");

    server.print(tempC);


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
      server.print("<a href='?led=off&ar=off'><button style='border: 1px solid #ff0000; border-left: 10px solid #ff0000' type='button'>LED LIGADO</button></a>");
      digitalWrite(PinoLed2, LOW);
      server.print("<a href='?led=on&ar=on'><button style='border: 1px solid #000; border-left: 10px solid #000' type='button'>AR DESLIGADO</button></a>");
    }
        else if (strcmp(params, "?led=off&ar=on") == 0)
    {
      digitalWrite(PinoLed, LOW);
      server.print("<a href='?led=on&ar=on'><button style='border: 1px solid #000; border-left: 10px solid #000' type='button'>LED DESLIGADO</button></a>");
      digitalWrite(PinoLed2, HIGH);
      server.print("<a href='?led=off&ar=off'><button style='border: 1px solid #ff0000; border-left: 10px solid #ff0000' type='button'>AR LIGADO</button></a>");
    }    
    
    server.respond();
  }
  }


