#include <Arduino.h>

void setup()
{
    pinMode(22,OUTPUT);    //led pin
}

void loop()
{
    // put your main code here, to run repeatedly:
    digitalWrite(22,HIGH);
    delay(1000);    
    digitalWrite(22,LOW);
    delay(400);
}