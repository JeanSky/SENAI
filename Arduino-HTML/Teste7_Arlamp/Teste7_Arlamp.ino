#include "etherShield.h" //incluindo biblioteca
#include "ETHER_28J60.h" //incluindo biblioteca

const float CELSIUS_BASE = 0.4887585532746823069403714565; //base de conversão para LM35
int PinoLed = 7; 
int PinoLed2 = 6;
int PinoLed3 = 8;
int PinoLed4 = 9;
int botao1 = 2;
int botao2 = 4;
int botao3 = 3;
int botao4 = 5;
int bot1, bot2, bot3, bot4;
int LM = A0;
int LDR = A1;
float tempC, tensaoEq, valorLM, valorLDR;
char* iluminacao;
char* arcondicionado;

static uint8_t mac[6] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x24}; //configurações do shield ethernet - MAC ADDRESS
static uint8_t ip[4] = {192,168,0,114}; //configurações do shield ethernet - IP
static uint16_t port = 80; //configurações do shield ethernet - Porta de comunicação

ETHER_28J60 server; //definição de variável

void setup()
{
  server.setup(mac, ip, port); //inicia o shield ethernet
  pinMode(PinoLed, OUTPUT); //saida para acionamento dos relés
  pinMode(PinoLed2, OUTPUT); //saida para acionamento dos relés
  pinMode(PinoLed3, OUTPUT); //saida para acionamento dos relés
  pinMode(PinoLed4, OUTPUT); //saida para acionamento dos relés
  pinMode(botao1, INPUT); //entrada dos botões
  digitalWrite(botao1, HIGH); //pullup
  pinMode(botao2, INPUT); //entrada dos botões
  digitalWrite(botao2, HIGH); //pullup
  pinMode(botao3, INPUT); //entrada dos botões
  digitalWrite(botao3, HIGH); //pullup
  pinMode(botao4, INPUT); //entrada dos botões
  digitalWrite(botao4, HIGH); //pullup
}

void loop()
{
  bot1 = digitalRead(botao1); //leitura de variáveis - estado do botão 1
  bot2 = digitalRead(botao2); //leitura de variáveis - estado do botão 2
  bot3 = digitalRead(botao3); //leitura de variáveis - estado do botão 3
  bot4 = digitalRead(botao4); //leitura de variáveis - estado do botão 4
  valorLM = analogRead(LM);  //leitura de variáveis - sensor de temperatura
  tensaoEq = (valorLM * CELSIUS_BASE); //conversão do valor de leitura
  tempC = tensaoEq; //valor em ºC da temperatura
  valorLDR = analogRead(LDR); //leitura de variáveis - sensor de luminosidade
  if (valorLDR < 300) //condicional para lâmpada acesa ou apagada
  {
    iluminacao = ("As lampadas estao apagadas!");
  }
  else if (valorLDR > 300)
  {
    iluminacao = ("As lampadas estao acesas!");
  }
  if (tempC <= 25) //condicional para leitura de temperatura
  {
    arcondicionado = ("O Ar Condicionado esta ligado!");
  }
  else if (tempC > 25)
  {
    arcondicionado = ("O Ar Condicionado esta desligado!");
  }  
  
  char* params; //definição para ethernet

      if (bot1 == 0) //comparação do botão 1
    {
      digitalWrite(PinoLed, HIGH); 
      digitalWrite(PinoLed3, LOW);      
    }
     if (bot2 == 0) //comparação do botão 2
    {
      digitalWrite(PinoLed, LOW);
      digitalWrite(PinoLed3, HIGH);      
    } 
      if (bot3 == 0) //comparação do botão 3
    {
      digitalWrite(PinoLed2, HIGH);
      digitalWrite(PinoLed4, LOW);      
    }
     if (bot4 == 0) //comparação do botão 4
    {
      digitalWrite(PinoLed2, LOW);
      digitalWrite(PinoLed4, HIGH);      
    } 


  if (params = server.serviceRequest()) //comparação de requisição do servidor
  {

    server.print("<h1><a href='/?led=off'>Iluminacao</a>    <a href='/?ar=off'>Ar Condicionado</a></h1>"); //código html de abertura
    server.print("<META HTTP-EQUIV='REFRESH' CONTENT='4.5'>"); //código html para atualizar a página web

     if ((strcmp(params, "?led=on") == 0) && (bot2 == 0)) //comparação da página e botão
    {
      digitalWrite(PinoLed, LOW);
      digitalWrite(PinoLed3, HIGH);
      server.print("<META HTTP-EQUIV='REFRESH' CONTENT='0.5; http://192.168.0.114/?led=off'>");
      server.print("<a href='?led=on'><button style='border: 1px solid #000; border-left: 10px solid #000' type='button'>LED DESLIGADO</button></a>");
      server.print("<p>A temperatura eh:  ");
      server.print(tempC);
      server.print(" &degC");
      server.print("<p>");
      server.print(arcondicionado);
    }
  
    else if ((strcmp(params, "?led=on") == 0) || (bot1 == 0)) //comparação da página e botão
    {
      digitalWrite(PinoLed, HIGH);
      digitalWrite(PinoLed3, LOW);
      server.print("<META HTTP-EQUIV='REFRESH' CONTENT='0.5; http://192.168.0.114/?led=on'>");
      server.print("<a href='?led=off'><button style='border: 1px solid #ff0000; border-left: 10px solid #ff0000' type='button'>LED LIGADO</button></a>");
      server.print("<p>A temperatura eh:  ");
      server.print(tempC);
      server.print(" &degC");   
      server.print("<p>");
      server.print(arcondicionado);
    }
    else if ((strcmp(params, "?led=off") == 0) || (bot2 == 0)) //comparação da página e botão
    {
      digitalWrite(PinoLed, LOW);
      digitalWrite(PinoLed3, HIGH);
      server.print("<META HTTP-EQUIV='REFRESH' CONTENT='0.5; http://192.168.0.114/?led=off'>");
      server.print("<a href='?led=on'><button style='border: 1px solid #000; border-left: 10px solid #000' type='button'>LED DESLIGADO</button></a>");
      server.print("<p>A temperatura eh:  ");
      server.print(tempC);
      server.print(" &degC");
      server.print("<p>");
      server.print(arcondicionado);
    }
  
    else if ((strcmp(params, "?ar=on") == 0) && (bot4 == 0)) //comparação da página e botão
    {
      digitalWrite(PinoLed2, LOW);
      digitalWrite(PinoLed4, HIGH);      
      server.print("<META HTTP-EQUIV='REFRESH' CONTENT='0.5; http://192.168.0.114/?ar=off'>");
      server.print("<a href='?ar=on'><button style='border: 1px solid #000; border-left: 10px solid #000' type='button'>AR DESLIGADO</button></a>");
      server.print("<p>A temperatura eh:  ");
      server.print(tempC);
      server.print(" &degC");
      server.print("<p>");
      server.print(iluminacao);
    }
  
    else if ((strcmp(params, "?ar=on") == 0) || (bot3 == 0)) //comparação da página e botão
    {
      digitalWrite(PinoLed2, HIGH);
      digitalWrite(PinoLed4, LOW);      
      server.print("<META HTTP-EQUIV='REFRESH' CONTENT='0.5; http://192.168.0.114/?ar=on'>");
      server.print("<a href='?ar=off'><button style='border: 1px solid #ff0000; border-left: 10px solid #ff0000' type='button'>AR LIGADO</button></a>");
      server.print("<p>A temperatura eh:  ");
      server.print(tempC);
      server.print(" &degC");
      server.print("<p>");
      server.print(iluminacao);
    }
    else if ((strcmp(params, "?ar=off") == 0) || (bot4 == 0)) //comparação da página e botão
    {
      digitalWrite(PinoLed2, LOW);
      digitalWrite(PinoLed4, HIGH);            
      server.print("<META HTTP-EQUIV='REFRESH' CONTENT='0.5; http://192.168.0.114/?ar=off'>");
      server.print("<a href='?ar=on'><button style='border: 1px solid #000; border-left: 10px solid #000' type='button'>AR DESLIGADO</button></a>");
      server.print("<p>A temperatura eh:  ");
      server.print(tempC);
      server.print(" &degC");
      server.print("<p>");
      server.print(iluminacao);
    }

    server.respond(); //espera resposta do servidor
  }
}

