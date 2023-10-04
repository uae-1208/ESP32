#include <Arduino.h>



void setup() 
{
    ledcSetup(14, 10000, 10);                //设置通道  将光标放到函数名上看需要的参数
    ledcAttachPin(26, 14);                    //将 LEDC 通道绑定到指定 IO 口上以实现输出

    ledcWrite(14, 750);
}

void loop() 
{

}