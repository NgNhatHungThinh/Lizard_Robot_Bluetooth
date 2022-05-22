////////////////////////////////////////////////////////////////
// Arduino    <-->    Bluetooth
//  Pin 4                Tx
//  Pin 5                Rx 
////////////////////////////////////////////////////////////////
#include <SoftwareSerial.h>
#include <Servo.h>

#define DEBUG

#define BLUETOOTH_TX 4 
#define BLUETOOTH_RX 5 
SoftwareSerial bluetooth(BLUETOOTH_TX, BLUETOOTH_RX); // RX, TX

Servo FrontLegs; 
Servo Body; 
Servo HindLegs; 

int delay_us = 1500; 

////////////////////////////////////////////////////////////
//                     FRONT LEGS 
////////////////////////////////////////////////////////////
void FrontLeg_Left_MoveForward(uint8_t ang)
{
  for(uint8_t i = 0; i < ang; i++)
  {
    FrontLegs.write(ang); 
    delayMicroseconds(delay_us); 
  }
}

void FrontLegs_Balance(uint8_t ang)
{
  for(uint8_t i = 0; i < ang; i++)
  {
    FrontLegs.write(ang); 
    delayMicroseconds(delay_us); 
  }
}

void FrontLeg_Right_MoveForward(uint8_t ang)
{
  for(uint8_t i = 0; i < ang; i++)
  {
    FrontLegs.write(ang); 
    delayMicroseconds(delay_us); 
  }
}

////////////////////////////////////////////////////////////
//                     THE BODY 
////////////////////////////////////////////////////////////
void Body_TiltToLeft(uint8_t ang)
{
  for(uint8_t i = 90; i > ang; i--)
  {
    Body.write(i); 
    delayMicroseconds(delay_us); 
  }
}

void Body_Balance(uint8_t ang)
{
  for(uint8_t i = ang; i > 0; i--)
  {
    Body.write(i); 
    delayMicroseconds(delay_us); 
  }
}

void Body_TiltToRight(uint8_t ang)
{
  for(uint8_t i = 90; i < ang; i++)
  {
    Body.write(i); 
    delayMicroseconds(delay_us); 
  }
}

////////////////////////////////////////////////////////////
//                     HIND LEGS 
////////////////////////////////////////////////////////////
void HindLeg_Left_MoveForward(uint8_t ang)
{
  for(uint8_t i = 100; i < ang; i++)
  {
    HindLegs.write(i); 
    delayMicroseconds(delay_us); 
  }
}

void HindLeg_Balance(void)
{
  HindLegs.write(100); 
  delay(500);
}

void HindLeg_Right_MoveForward(uint8_t ang)
{
  for(uint8_t i = 100; i > ang; i--)
  {
    HindLegs.write(i); 
    delayMicroseconds(delay_us); 
  }
}

void setup() 
{
  bluetooth.begin(9600);  
  
  FrontLegs.attach(11); 
  Body.attach(10); 
  HindLegs.attach(9); 

  //...Default
  FrontLegs.write(40);
  Body.write(90); 
  HindLegs.write(100);
}

void loop() 
{
  uint8_t T = 0;

  //...Default
  FrontLegs.write(40);
  Body.write(90); 
  HindLegs.write(100);
   
  if(bluetooth.available() > 0)
  {
    char chr = bluetooth.read(); 

    if(chr == '1') //...Move Forward 
    {
      do
      {
        HindLeg_Left_MoveForward(140); 
        FrontLeg_Right_MoveForward(10); 
        Body_TiltToRight(130); 
          
        HindLeg_Right_MoveForward(70);
        FrontLeg_Left_MoveForward(80);
        Body_TiltToLeft(40);
  
        T += 1;
      }while(T < 4); 
      
      T = 0; 
    }
    else if(chr == '2') //...Move Backforward 
    {
      do
      {
        HindLeg_Right_MoveForward(70);
        FrontLeg_Left_MoveForward(80);
        Body_TiltToRight(120); 
        
        HindLeg_Left_MoveForward(140); 
        FrontLeg_Right_MoveForward(10); 
        Body_TiltToLeft(60);
  
        T += 1; 
      }while(T < 4); 

      T = 0; 
    }
    else if(chr == '3') //...Move Turn Left 
    {
      do
      {
        HindLeg_Left_MoveForward(140); 

        FrontLeg_Right_MoveForward(10); 
        Body_TiltToRight(130); 
      
        FrontLeg_Left_MoveForward(80); 
        Body_TiltToLeft(40);
  
        T += 1; 
      }while(T < 4); 

      T = 0; 
    }
    else if(chr == '4') //...Move Turn Right
    {
      do
      {
        HindLeg_Right_MoveForward(70);

        FrontLeg_Left_MoveForward(80); 
        Body_TiltToLeft(60);
        
        FrontLeg_Right_MoveForward(10); 
        Body_TiltToRight(120);
  
        T += 1; 
      }while(T < 4); 

      T = 0; 
    }
  }
}
