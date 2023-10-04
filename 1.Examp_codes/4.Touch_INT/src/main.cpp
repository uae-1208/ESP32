#include <Arduino.h>

void  TouchEvent()
{
    Serial.println("Hello world!");
}


void setup()
{
    Serial.begin(115200);
    touchAttachInterrupt(T0,TouchEvent,50);
}

void loop() 
{
    Serial.printf("Touch value:%d\r\n",touchRead(T0));
    delay(400);
}