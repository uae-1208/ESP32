#include <Arduino.h>

bool i;

void setup()
{
    i = 1;
}


void loop()
{
    // put your main code here, to run repeatedly:
    /*digitalWrite(2,HIGH);
    delay(1000);    
    digitalWrite(2,LOW);
    delay(400);*/
    dacWrite(25,i*255);
    i =!i;
    delay(1);
}