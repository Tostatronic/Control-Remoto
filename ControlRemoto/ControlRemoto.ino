#include <SPI.h>
#include <RF24.h>
#define xAxis 14     // A0 for Arduino UNO
#define yAxis 15     // A1 for Arduino UNO

RF24 radio(9, 10); // CE, CSN

//Botones de la joystick Shield Game
int buttonUp    = 2;
int buttonRight = 3;
int buttonDown  = 4;
int buttonLeft  = 5;

//Declaramos la variable que contendra los estados de las 6 posibles acciones del joystick shield game
int joystick[6];



const byte identificacion[6] = "00001";

void setup()
{
  radio.begin();
  radio.openWritingPipe(identificacion);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  //Declaramos los botones en modo PULL_UP
  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonRight, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP);
  pinMode(buttonLeft, INPUT_PULLUP);

  //Inicializamos los estados de los botones
  digitalWrite(buttonUp, LOW);
  digitalWrite(buttonRight, LOW);
  digitalWrite(buttonDown, LOW);
  digitalWrite(buttonLeft, LOW);
  Serial.begin(9600);
}

void loop()
{
  GetLectura();
  radio.write(&joystick, sizeof(joystick));

  delay(100); // Un segundo (1000 milisegundos) de espera entre envío y envío
}

void GetLectura()
{
  joystick[0] = analogRead(xAxis);
  Serial.println(joystick[0]);
  joystick[1] = analogRead(yAxis);
  Serial.println(joystick[1]);
  joystick[2] = digitalRead(buttonUp);
  Serial.println(joystick[2]);
  joystick[3] = digitalRead(buttonRight);
  Serial.println(joystick[3]);
  joystick[4] = digitalRead(buttonDown);
  Serial.println(joystick[4]);
  joystick[5] = digitalRead(buttonLeft);
  Serial.println(joystick[5]);
}
