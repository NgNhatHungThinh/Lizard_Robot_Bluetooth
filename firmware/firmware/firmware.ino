#include <Servo.h>

Servo Front_Legs;
Servo Hind_Legs;
Servo Body;

void Move_Forward(void)
{
  Front_Legs.write(60);
}

void setup()
{
  Serial.begin(9600);
  Front_Legs.attach(9);
  Hind_Legs.attach(10);
  Body.attach(11);
}

void loop()
{
  Move_Forward();

}
