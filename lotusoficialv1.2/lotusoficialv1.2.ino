#include <bibliotecamotor.h>
#include <Ultrasonic.h>

#define sd 7
#define scd 11
#define sf 8
#define sce 12
#define se 13

#define r 2
#define g 3
#define b 4

#define cord A0
#define core A1

motor me(6, 5);
motor md(9, 10);

int limiarbd = 710;
int limiarvd = 670;
int limiarpd = 450;

int limiarbe = 750;
int limiarve = 710;
int limiarpe = 490;
Ultrasonic ultraf(A5, A4);

int sensor[5] = {digitalRead(se), digitalRead(sce), digitalRead(sf), digitalRead(scd), digitalRead(sd)};

void setup()
{
  // put your setup code here, to run once:
  // Pinos dos sensores de faixa
  pinMode(sd, INPUT);
  pinMode(scd, INPUT);
  pinMode(sf, INPUT);
  pinMode(sce, INPUT);
  pinMode(se, INPUT);

  // pinos leds rgbs
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);

  // pinos dos sensores de cor
  pinMode(cord, INPUT);
  pinMode(core, INPUT);

  digitalWrite(g, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(r, HIGH);

  // digitalWrite(g, LOW);
  Serial.begin(9600);
}
#define leitura (PIND & 1 << 4 | PIND & 1 << 3 | PIND & 1 << 2 | (PIND & 1) << 1 | PINB & 1 << 8)
byte leitura = 0;
void loop()
{
  // leitura = PINC << 13|(PINB & 0b11111) << 8 |PIND
  // leitura = PIND & 1 << 4 | PIND & 1 << 3 | PIND & 1 << 2 | (PIND & 1) << 1 | PINB & 1 << 8;
  //  cores();
  //  segue_faixa();
  // leituratodos();

  /*
    digitalWrite(g,LOW);
    digitalWrite(b,HIGH);
    digitalWrite(r,HIGH);
    Serial.print("Sensor de cor esquerdo:");
    Serial.println(analogRead(A1));
    Serial.print("Sensor de cor direito:");
    Serial.println(analogRead(A0));
  */
}
void frente(int d, int e)
{
  md.frente(d);
  me.frente(e);
}
void re(int d, int e)
{
  md.re(d);
  me.re(e);
}
void esquerda(int d, int e)
{
  md.frente(d);
  me.re(e);
}
void direita(int d, int e)
{
  me.frente(e);
  md.re(d);
}
void para(int t)
{
  md.para();
  me.para();
  delay(t);
}
void segue_faixa()
{
  // int sensor[5] = {digitalRead(se), digitalRead(sce), digitalRead(sf), digitalRead(scd), digitalRead(sd)};
  int cont = 0;
  // giro esquerdo central curto
  while (leitura == 0b10111)
  {
    while (digitalRead(scd) == 1)
    {
      esquerda(250, 250);
    }
  }
  // giro direito central curto
  while (leitura == 0b11101)
  {
    while (digitalRead(sce) == 1)
    {
      direita(250, 250);
    }
  }
  swith(leitura)
  {
  // giro direita externo
  case 0b11110:
  {
    para(100);
    frente(150, 150);
    delay(300);
    while (digitalRead(sf) == 1)
    {
      direita(150, 150);
    }
  }
  break;
  // giro esquerda externo
  case 0b01111:
  {
    para(100);
    frente(150, 150);
    delay(300);
    while (digitalRead(sf) == 1)
    {
      esquerda(150, 150);
    }
  }
  break;
  // giro 90 direita
  case 0b10000:
  {
    para(100);
    digitalWrite(g, LOW);
    while (digitalRead(sf) == 0)
    {
      frente(80, 80);
    }
    para(400);

    if ((analogRead(cord) >= limiarpd && analogRead(cord) <= limiarbd) && analogRead(core) >= 720)
    {
      frente(150, 150);
      delay(800);
      direita(150, 150);
      delay(1000);
      while (digitalRead(sf) == 1)
      {
        direita(150, 150);
      }
    }
    else if ((analogRead(cord) <= limiarbd && analogRead(cord) > limiarpd) && (analogRead(core) <= limiarbe && analogRead(core) > limiarpe))
    {
      para(100);
      re(150, 150);
      delay(500);
      direita(150, 150);
      delay(1000);
      while (digitalRead(sf) == 1)
      {
        direita(150, 150);
      }
    }
    para(100);
    digitalWrite(g, HIGH);
  }
  break;
  // giro 90 esquerda
  case 0b00001:
  {
    para(100);
    digitalWrite(g, LOW);
    while (digitalRead(sf) == 0)
    {
      frente(80, 80);
    }
    para(1000);
    if ((analogRead(core) >= limiarpe && analogRead(core) <= limiarbe) && analogRead(cord) >= 700)
    {
      frente(150, 150);
      delay(800);
      esquerda(150, 150);
      delay(1000);
      while (digitalRead(sf) == 1)
      {
        esquerda(150, 150);
      }
    }
    else if ((analogRead(cord) <= limiarbd && analogRead(cord) > limiarpd) && (analogRead(core) <= limiarbe && analogRead(core) > limiarpe))
    {
      para(100);
      re(150, 150);
      delay(500);
      direita(150, 150);
      delay(2000);
      while (digitalRead(sf) == 1)
      {
        direita(150, 150);
      }
    }
    para(1000);
    digitalWrite(g, HIGH);
  }
  break;
  // encruzilhada
  case 0b00000:
  {
    cores();
    para(1000);
    frente(100, 100);
    delay(1000);
  }
  break;
  // esquerda curva
  case 0b00011:
  {
    para(2000);
    frente(150, 150);
    delay(200);
    while (digitalRead(sf) == 1)
    {
      esquerda(150, 150);
    }
  }
  break;
  // direita curva
  case 0b11000:
  {
    para(2000);
    frente(150, 150);
    delay(200);
    while (digitalRead(sf) == 1)
    {
      direita(150, 150);
    }
  }
    brea;
  // esquerda curva 2
  case 0b00001:
  {
    para(100);
    frente(150, 150);
    delay(200);
    while (digitalRead(sf) == 1)
    {
      esquerda(150, 150);
    }
  }
  break;
  // direita curva 2
  case 0b10000:
  {
    para(100);
    frente(150, 150);
    delay(200);
    while (digitalRead(sf) == 1)
    {
      direita(150, 150);
    }
  }
  break;
  default:
  {
    frente(120, 120);
    cores();
    cont++;
  }
  }
  if (cont == 2000)
  {
    para(1000);
    re(150, 150);
    delay(cont);
    para(1000);
    cont = 0;
  }
}
void cores()
{
  /*
    //giro para esquerda em caso de só um
    if (digitalRead(se) == 0 && digitalRead(sce) == 0 && digitalRead(sf) == 0 && digitalRead(scd) == 0 && digitalRead(sd) == 1) {
    para(100);
    frente(150, 150);
    delay(100);
    digitalWrite(g, LOW);
    para(1000);
    if ((analogRead(core) <= limiarbe && analogRead(core) > limiarpe) && analogRead(cord) > 700) {
      para(100);
      frente(150, 150);
      delay(1000);
      esquerda(150, 150);
      delay(1000);
      while (digitalRead(sf) == 1) {
        esquerda(150, 150);
      }
    }
    digitalWrite(g, HIGH);
    }
    //giro para direita em caso de só um
    else if (digitalRead(se) == 1 && digitalRead(sce) == 0 && digitalRead(sf) == 0 && digitalRead(scd) == 0 && digitalRead(sd) == 0) {
    para(100);
    frente(150, 150);
    delay(100);
    digitalWrite(g, LOW);
    para(1000);
    if ((analogRead(cord) <= limiarbd && analogRead(cord) > limiarpd) && analogRead(core) > 750) {
      para(100);
      frente(150, 150);
      delay(1000);
      direita(150, 150);
      delay(1000);
      while (digitalRead(sf) == 1) {
        direita(150, 150);
      }
    }
    digitalWrite(g, HIGH);
    }
  */
  // os 4 no preto e só o da frente no branco
  if (digitalRead(se) == 0 && digitalRead(sce) == 0 && digitalRead(sf) == 1 && digitalRead(scd) == 0 && digitalRead(sd) == 0)
  {
    para(1000);
    frente(130, 130);
    delay(1000);
    digitalWrite(g, LOW);
    para(1000);
    // VERDE ESQUERDO
    if ((analogRead(core) <= limiarbe && analogRead(core) > limiarpe) && analogRead(cord) > 710)
    {
      para(100);
      frente(150, 150);
      delay(1000);
      esquerda(150, 150);
      delay(1000);
      while (digitalRead(sf) == 1)
      {
        esquerda(150, 150);
      }
    }
    // VERDE DIREITO
    else if ((analogRead(cord) <= limiarbd && analogRead(cord) > limiarpd) && analogRead(core) > 750)
    {
      para(100);
      frente(150, 150);
      delay(1000);
      direita(150, 150);
      delay(1000);
      while (digitalRead(sf) == 1)
      {
        direita(150, 150);
      }
    }
    // OS DOIS VERDES NA FAIXA
    else if ((analogRead(cord) <= limiarbd && analogRead(cord) > limiarpd) && (analogRead(core) <= limiarbe && analogRead(core) > limiarpe))
    {
      para(100);
      re(150, 150);
      delay(800);
      direita(150, 150);
      delay(2000);
      while (digitalRead(sf) == 1)
      {
        direita(150, 150);
      }
    }
    digitalWrite(g, HIGH);
  }
  // todos na faixa e um no verde (encruzilhada)
  else if (digitalRead(se) == 0 && digitalRead(sce) == 0 && digitalRead(sf) == 0 && digitalRead(scd) == 0 && digitalRead(sd) == 0)
  {
    para(100);
    frente(130, 130);
    delay(3000);
    digitalWrite(g, LOW);
    para(1000);
    // esquerdo no verde e outro branco
    if ((analogRead(core) <= limiarbe && analogRead(core) > limiarpe) && analogRead(cord) > 700)
    {
      para(100);
      frente(150, 150);
      delay(800);
      esquerda(150, 150);
      delay(1000);
      while (digitalRead(sf) == 1)
      {
        esquerda(150, 150);
      }
    }
    // direito no verde e outro no branco
    else if ((analogRead(cord) <= limiarbd && analogRead(cord) > limiarpd) && analogRead(core) > 750)
    {
      para(100);
      frente(150, 150);
      delay(800);
      direita(150, 150);
      delay(1000);
      while (digitalRead(sf) == 1)
      {
        direita(150, 150);
      }
    }
    // os dois no verde
    else if ((analogRead(cord) <= limiarbd && analogRead(cord) > limiarpd) && (analogRead(core) <= limiarbe && analogRead(core) > limiarpe))
    {
      para(100);
      re(150, 150);
      delay(600);
      esquerda(150, 150);
      delay(1000);
      while (digitalRead(sf) == 1)
      {
        esquerda(150, 150);
      }
    }
    digitalWrite(g, HIGH);
  }
  /*
    //3 da frente na faixa e um no verde (encruzilhada)
    else if (digitalRead(se) == 0 && digitalRead(sf) == 0 && digitalRead(sd) == 0) {
      para(100);
      frente(130, 130);
      delay(100);
      digitalWrite(g, LOW);
      para(1000);
      if ((analogRead(core) <= limiarbe && analogRead(core) > limiarpe) && analogRead(cord) > 700) {
        para(100);
        frente(150, 150);
        delay(800);
        esquerda(150, 150);
        delay(1000);
        while (digitalRead(sf) == 1) {
          esquerda(150, 150);
        }
      }
      else if ((analogRead(cord) <= limiarbd && analogRead(cord) > limiarpd) && analogRead(core) > 750)  {
        para(100);
        frente(150, 150);
        delay(800);
        direita(150, 150);
        delay(1000);
        while (digitalRead(sf) == 1) {
          direita(150, 150);
        }
      }
      //os dois no verde
      else if ((analogRead(cord) <= limiarbd && analogRead(cord) > limiarpd) && (analogRead(core) <= limiarbe && analogRead(core) > limiarpe))  {
        para(100);
        re(150, 150);
        delay(700);
        esquerda(150, 150);
        delay(1000);
        while (digitalRead(sf) == 1) {
          esquerda(150, 150);
        }
      }

      digitalWrite(g, HIGH);
    }
    */
}
void testeomotores()
{
  for (int i = 0; i < 255; i++)
  {
    md.frente(i);
    delay(100);
  }
  for (int i = 0; i < 255; i++)
  {
    md.re(i);
    delay(100);
  }
  for (int i = 0; i < 255; i++)
  {
    me.frente(i);
    delay(100);
  }
  for (int i = 0; i < 255; i++)
  {
    me.re(i);
    delay(100);
  }
}
// void leitura()
// {
//   Serial.print("leitura do sensor");
//   //  Serial.println(digitalRead());
// }
void leituratodos()
{
  Serial.println("leitura do se: " + String(digitalRead(se)));
  Serial.println("leitura do sce: " + String(digitalRead(sce)));
  Serial.println("leitura do sf: " + String(digitalRead(sf)));
  Serial.println("leitura do scd: " + String(digitalRead(scd)));
  Serial.println("leitura do sd: " + String(digitalRead(sd)));

  Serial.println("============================================");

  Serial.println("leitura do cord: " + String(analogRead(cord)));
  Serial.println("leitura do core: " + String(analogRead(core)));
  Serial.println("");
  delay(300);

  Serial.println("============================================");
}
void calibra_cor()
{
  int cor_direito = map(analogRead(A0), 0, 1023, 0, 255);
  int cor_esquerdo = map(analogRead(A1), 0, 1023, 0, 255);
  cor_direito = constrain(analogRead(A0), 0, 255);
  cor_esquerdo = constrain(analogRead(A0), 0, 255);
}
void obstaculo()
{
}
void vv90d()
{
  para(200);
  frente(150, 150);
  delay(100);
  digitalWrite(g, LOW);
  para(500);
  if ((analogRead(cord) <= limiarbd && analogRead(cord) > limiarpd) && analogRead(core) > 750)
  {
    para(100);
    frente(150, 150);
    delay(1000);
    direita(150, 150);
    delay(800);
    while (digitalRead(sf) == 1)
    {
      direita(150, 150);
    }
  }
  digitalWrite(g, HIGH);
  if (analogRead(cord) >= 680 && analogRead(core) >= 750)
  {
    frente(150, 150);
    delay(200);
    while (digitalRead(sf) == 1)
    {
      direita(150, 150);
    }
  }
}

void vv90e()
{
  para(200);
  frente(150, 150);
  delay(200);
  digitalWrite(g, LOW);
  para(500);
  if ((analogRead(core) <= limiarbe && analogRead(core) > limiarpe) && analogRead(cord) > 700)
  {
    para(100);
    frente(150, 150);
    delay(800);
    esquerda(150, 150);
    delay(1000);
    while (digitalRead(sf) == 1)
    {
      esquerda(150, 150);
    }
  }
  if (analogRead(cord) >= 700 && analogRead(core) >= 750)
  {
    frente(150, 150);
    delay(200);
    while (digitalRead(sf) == 1)
    {
      esquerda(150, 150);
    }
  }
  digitalWrite(g, HIGH);
}
