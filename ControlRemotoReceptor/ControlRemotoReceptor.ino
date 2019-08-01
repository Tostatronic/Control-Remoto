#include <SPI.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

int joystick[6];

char instruction = 'x';
char lastInstruction = 'x';

const byte identificacion[6] = "00001";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();

  radio.openReadingPipe(0, identificacion);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (radio.available())
  {
    radio.read(&joystick, sizeof(joystick));
    instruction = GetInstruction();
    if (instruction != lastInstruction) {//instruction=x,a,a,b, lastInstruction=x,x,a,a
      lastInstruction = instruction;//i=a,b li=a,b
      switch(instruction)
      {
        case 'a':
        Serial.println("Adelante");
        break;
        case 'b':
        Serial.println("Derecha");
        break;
        case 'c':
        Serial.println("Atras");
        break;
        case 'd':
        Serial.println("Izquierda");
        break;
        case 'x':
        Serial.println("Alto");
        break;
      }
      Serial.println(lastInstruction);
    }

  }
}

char GetInstruction()
{
  if (joystick[2] == LOW)
  {
    return 'a';
  }
  else if (joystick[3] == LOW)
  {
    return 'b';
  }
  else if (joystick[4] == LOW)
  {
    return 'c';
  }
  else if (joystick[5] == LOW)
  {
    return 'd';
  }
  else if(joystick[1] > 550)
  {
    return 'a';
  }
  else if(joystick[0] > 550)
  {
    return 'b';
  }
  else if(joystick[1] < 300)
  {
    return 'c';
  }
  else if(joystick[0] < 300)
  {
    return 'd';
  }
  return 'x';
}
