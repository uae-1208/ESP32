/**********************************************************************
项目名称/Project          : 零基础入门学用物联网
程序名称/Program name     : publish_ranye_url
团队/Team                : 太极创客团队 / Taichi-Maker (www.taichi-maker.com)
作者/Author              : CYNO朔
日期/Date（YYYYMMDD）     : 20200813
程序目的/Purpose          : 
本程序旨在演示如何使用PubSubClient库使用ESP8266向MQTT服务器发布信息。
-----------------------------------------------------------------------
本示例程序为太极创客团队制作的《零基础入门学用物联网》中示例程序。
该教程为对物联网开发感兴趣的朋友所设计和制作。如需了解更多该教程的信息，请参考以下网页：
http://www.taichi-maker.com/homepage/esp8266-nodemcu-iot/iot-c/esp8266-nodemcu-web-client/http-request/
***********************************************************************/
#include <WiFi.h>
#include <PubSubClient.h>
#include <Ticker.h>
 
#define BUILTIN_LED 2

// 设置wifi接入信息(请根据您的WiFi信息进行修改)
const char* ssid = "先贤显现";
const char* password = "a1208172292";
const char* mqttServer = "test.ranye-iot.net";
 
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
 
bool LED_STatus; 



// 订阅指定主题
void subscribeTopic(){
 
  // 建立订阅主题。
  String topicString = "Uae-Sub";
  char subTopic[topicString.length() + 1];  
  strcpy(subTopic, topicString.c_str());
  
  // 通过串口监视器输出是否成功订阅主题以及订阅的主题名称
  if(mqttClient.subscribe(subTopic)){
    Serial.print("Subscrib Topic:");
    Serial.println(subTopic);
  } else {
    Serial.print("Subscribe Fail...");
  }  
}


// 发布信息
void pubMQTTmsg()
{ 
  String LEDStatusString[2]={"OFF","ON"};
  // 建立发布主题。
  String topicString = "Uae-Pub";
  char publishTopic[topicString.length() + 1];  
  strcpy(publishTopic, topicString.c_str());
 
  // 建立发布信息。
  String messageString = "LED Status: " + LEDStatusString[LED_STatus]; 
  char publishMsg[messageString.length() + 1];   
  strcpy(publishMsg, messageString.c_str());
  
  // 实现ESP8266向主题发布信息            //publish只能传入字符数组参数而不是string变量
  if(mqttClient.publish(publishTopic, publishMsg)){
    Serial.print("Publish Topic:  ");Serial.println(publishTopic);
    Serial.print("Publish message:  ");Serial.println(publishMsg);    
    Serial.print("\r\n");  
  } else {
    Serial.println("Message Publish Failed."); 
  }
}

// 收到信息后的回调函数
void receiveCallback(char* topic, byte* payload, unsigned int length) 
{
  String PrintMsg[2] = {"LED OFF","LED ON"};
  
  Serial.print("Message Received [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }

  Serial.println("");
  Serial.print("Message Length(Bytes) ");
  Serial.println(length);
 

  if ((char)payload[0] == '1') // 如果收到的信息以“1”为开始
    LED_STatus = 1;            // 则点亮LED。
  else 
    LED_STatus = 0;            // 否则熄灭LED。      


  Serial.println(PrintMsg[LED_STatus]);
  pubMQTTmsg();   //订阅信息
  digitalWrite(BUILTIN_LED, LED_STatus); 
}

void connectMQTTServer(){
  // 根据ESP8266的MAC地址生成客户端ID（避免与其它ESP8266的客户端ID重名）
  String clientId = "ESP32-UAE";
 
  // 设置MQTT服务器和端口号
  mqttClient.setServer(mqttServer, 1883);
   // 设置MQTT订阅回调函数
  mqttClient.setCallback(receiveCallback);

  // 连接MQTT服务器
  if (mqttClient.connect(clientId.c_str())) 
  { 
    Serial.println("MQTT Server Connected.");
    Serial.print("Server Address: ");
    Serial.println(mqttServer);
    Serial.print("ClientId:  ");
    Serial.println(clientId);
    subscribeTopic(); // 订阅指定主题

  } else {
    Serial.print("MQTT Server Connect Failed. Client State:");
    Serial.println(mqttClient.state());
    delay(3000);
  }   
}
 


// ESP8266连接wifi
void connectWifi(){
 
  WiFi.begin(ssid, password);
 
  //等待WiFi连接,成功连接后输出成功信息
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected!");  
  Serial.println(""); 
}






 
void setup() 
{
  pinMode(BUILTIN_LED, OUTPUT);     // 设置板上LED引脚为输出模式
  digitalWrite(BUILTIN_LED, HIGH);  // 启动后开启板上LED
  Serial.begin(115200);
  
  //设置ESP8266工作模式为无线终端模式
  WiFi.mode(WIFI_STA);
  // 连接WiFi
  connectWifi();
  
  // 连接MQTT服务器
  connectMQTTServer();
}
 
void loop() { 
  if (mqttClient.connected())  // 如果开发板成功连接服务器
    // 保持心跳 
    mqttClient.loop();
  else                   // 如果开发板未能成功连接服务器
    connectMQTTServer();    // 则尝试连接服务器
  
}
 

 
