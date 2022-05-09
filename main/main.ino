#include <SoftwareSerial.h>

#define LED1 6
#define LED2 7
#define LED3 8

////////////////////////////////////////////////////////////////
// Arduino    <-->    Bluetooth
//  Pin 4                Tx
//  Pin 5                Rx 
////////////////////////////////////////////////////////////////

#define BLUETOOTH_TX 4 
#define BLUETOOTH_RX 5 

SoftwareSerial bluetooth(BLUETOOTH_TX, BLUETOOTH_RX); // RX, TX

void setup() 
{
 bluetooth.begin(9600);  
 pinMode(LED1, OUTPUT);
 pinMode(LED2, OUTPUT);
 pinMode(LED3, OUTPUT); 
 pinMode(13, OUTPUT); 

 digitalWrite(LED1, LOW);
 digitalWrite(LED2, LOW);
 digitalWrite(LED3, LOW); 
 digitalWrite(13, LOW); 
}

void loop() 
{
  if(bluetooth.available() > 0)
  {
    char chr = bluetooth.read(); 

    if(chr == '1')
    {
      digitalWrite(LED1, HIGH); 
      digitalWrite(LED2, HIGH); 
      digitalWrite(LED3, HIGH); 
      digitalWrite(13, HIGH); 
    }
    else if(chr == '2')
    {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW); 
      digitalWrite(13, LOW);
    }
  }

}
