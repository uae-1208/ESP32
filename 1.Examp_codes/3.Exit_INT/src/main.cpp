#include <Arduino.h>

void PinIntEvent()
{
    Serial.printf("Hello world\r\n");
}



void setup()
{
    Serial.begin(115200);
    pinMode(0,INPUT_PULLUP);
    attachInterrupt(0,PinIntEvent,FALLING);
}

void loop() 
{
}