#include <Arduino.h>

HardwareSerial zhp_serial(0);
char string[100];

void setup() 
{
    Serial.begin(115200);
    //zhp_serial.begin(115200);       //要用zhp_serial必须初始化,哪怕以及初始化过Serial了
}

void loop() 
{
    if(Serial.find('d'))
    {   
        while(Serial.available())
            Serial.printf("%c",Serial.read());        
    }

    /*Serial.print("Hello world!\r\n");
    Serial.println("Hello world!");
    zhp_serial.println("nb?");
    delay(500);*/
}