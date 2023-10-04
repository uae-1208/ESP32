#include <Arduino.h>

hw_timer_t  *timer = NULL;  //定时器硬件地址
int interruptCounter = 0;

void IRAM_ATTR TimerEvent()
{
    Serial.println(interruptCounter++);
    if (interruptCounter > 5)
    {
        interruptCounter = 1;
    }
}

void setup() 
{
    Serial.begin(115200);
        
    timer = timerBegin(0, 80, true);                    //1.定时器编号0-3; 2.定时器分频(80M/num); 3.计数方向(true:上 false:下)
    timerAttachInterrupt(timer, &TimerEvent, true);     //3.表示中断触发类型是边沿（true）还是电平（false）的标志
    timerAlarmWrite(timer, 1000000, true);              //2.写入重装载值 3.是否重装载
    timerAlarmEnable(timer);                            //使能定时器


}

void loop() 
{

}