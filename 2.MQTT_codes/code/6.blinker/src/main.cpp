//例程  https://arduino.me/s/2?aid=711

#define BLINKER_WIFI

#include <Blinker.h>

char auth[] = "81f51910e9b2";   //双创APP
char ssid[] = "先贤显现";
char pswd[] = "a1208172292";


// 新建组件对象
BlinkerButton Button1("btn-led");
BlinkerButton Button2("btn-cnt");
BlinkerNumber Number1("num-abc");
BlinkerNumber Number2("num-temp");






/***********************************************例程3：历史数据*****************************************/
 int counter = 0;
float Temp = 10;
float Humi = 0;

// 按下按键即会执行该函数
void button1_callback(const String & state)
{
    BLINKER_LOG("get button state: ", state);
    if (state=="on") 
    {
        digitalWrite(LED_BUILTIN, HIGH);        // 反馈开关状态
        Button1.print("on");
    } 
    else if(state=="off")
    {
        digitalWrite(LED_BUILTIN, LOW);
        Button1.print("off");        // 反馈开关状态
    }
}

// 按下按键即会执行该函数
void button2_callback(const String & data)
{
    BLINKER_LOG("Blinker readString: ", data);
    counter++;
    Number1.print(counter);
}


//在blinker app上，点击设备图标进入设备控制页面时，app会向设备发送一个状态查询指令（心跳包）。此后，WiFi设备每59秒会发送一次心跳包；
// 心跳包函数
void heartbeat() 
{
    Number1.print(counter);   //连接时点击数显示为0
    Number2.print(Temp);      //连接时温度显示为10
}

void dataStorage()
{
    Blinker.dataStorage("temp", Temp);
    Blinker.dataStorage("humi", Humi);
}

void setup()
{
    Serial.begin(115200);     // 初始化串口
    BLINKER_DEBUG.stream(Serial);
    pinMode(LED_BUILTIN, OUTPUT);    // 初始化有LED的IO
    digitalWrite(LED_BUILTIN, HIGH);

    Blinker.begin(auth, ssid, pswd);    // 初始化blinker
    Button1.attach(button1_callback);
    Button2.attach(button2_callback);
    Blinker.attachHeartbeat(heartbeat);   //注册心跳包，用于初始化UI
    //Blinker.attachDataStorage(dataStorage);
}

void loop() 
{
  static int dir = 1;

  Blinker.run();
  Number2.print(Temp);      
  //频率不要太快，因为MQTT服务器不允许
  Blinker.delay(2500);   //需要注意的是：原本Arduino程序中的delay()，在blinker开发中，都需要使用Blinker.delay()替代，这样可以避免阻塞程序，造成设备WiFi断连。
  
  /* if(Temp > 45)
    dir = 0;
  if(Temp < 10)
    dir = 1;

  if(dir)
    Temp += 1.62;
  else
    Temp -= 1.62; */
}  



/***********************************************例程2：数据反馈*****************************************/
/* // 新建组件对象
BlinkerButton Button1("btn-led");
BlinkerButton Button2("btn-cnt");
BlinkerNumber Number1("num-abc");


int counter = 0;

// 按下按键即会执行该函数
void button1_callback(const String & state)
{
    BLINKER_LOG("get button state: ", state);
    if (state=="on") 
    {
        digitalWrite(LED_BUILTIN, HIGH);        // 反馈开关状态
        Button1.print("on");
    } 
    else if(state=="off")
    {
        digitalWrite(LED_BUILTIN, LOW);
        Button1.print("off");        // 反馈开关状态
    }
}

// 按下按键即会执行该函数
void button2_callback(const String & data)
{
    BLINKER_LOG("Blinker readString: ", data);
    counter++;
    Number1.print(counter);
}


//在blinker app上，点击设备图标进入设备控制页面时，app会向设备发送一个状态查询指令（心跳包）。此后，WiFi设备每59秒会发送一次心跳包；
// 心跳包函数
void heartbeat() 
{
    Number1.print(counter);   //连接时点击数显示为0
}


void setup()
{
    Serial.begin(115200);     // 初始化串口
    BLINKER_DEBUG.stream(Serial);
    pinMode(LED_BUILTIN, OUTPUT);    // 初始化有LED的IO
    digitalWrite(LED_BUILTIN, HIGH);

    Blinker.begin(auth, ssid, pswd);    // 初始化blinker
    Button1.attach(button1_callback);
    Button2.attach(button2_callback);
    Blinker.attachHeartbeat(heartbeat);   //注册心跳包，用于初始化UI
}

void loop() {
    Blinker.run();
    Blinker.delay(200);   //需要注意的是：原本Arduino程序中的delay()，在blinker开发中，都需要使用Blinker.delay()替代，这样可以避免阻塞程序，造成设备WiFi断连。
} */




/***********************************************例程1：基本控制*****************************************/
/*
 int counter = 0;
// 按下按键即会执行该函数
void button1_callback(const String & state)
{
    BLINKER_LOG("get button state: ", state);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

// 如果未绑定的组件被触发，则会执行其中内容
void dataRead(const String & data)
{
    BLINKER_LOG("Blinker readString: ", data);
    counter++;
    Number1.print(counter);
}

void setup()
{
    Serial.begin(115200);     // 初始化串口
    BLINKER_DEBUG.stream(Serial);
    pinMode(LED_BUILTIN, OUTPUT);    // 初始化有LED的IO
    digitalWrite(LED_BUILTIN, HIGH);

    Blinker.begin(auth, ssid, pswd);    // 初始化blinker
    Blinker.attachData(dataRead);
    Button1.attach(button1_callback);
}

void loop() {
    Blinker.run();
} */