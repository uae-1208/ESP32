/**********************************************************************
项目名称/Project          : 零基础入门学用物联网
程序名称/Program name     : publish_retained_msg
团队/Team                : 太极创客团队 / Taichi-Maker (www.taichi-maker.com)
作者/Author              : CYNO朔
日期/Date（YYYYMMDD）     : 20201014
程序目的/Purpose          : 
本程序旨在演示如何使用PubSubClient库使用ESP8266向MQTT服务器发布保留信息。
此程序在a_publish_ranye_url程序基础上修改。重点修改内容是publish函数添加了
第三个参数，用于设置发布信息是否是保留信息(retained msg)
-----------------------------------------------------------------------
本示例程序为太极创客团队制作的《零基础入门学用物联网》中示例程序。
该教程为对物联网开发感兴趣的朋友所设计和制作。如需了解更多该教程的信息，请参考以下网页：
http://www.taichi-maker.com/homepage/esp8266-nodemcu-iot/iot-c/esp8266-nodemcu-web-client/http-request/
***********************************************************************/
#include <WiFi.h>
#include <PubSubClient.h>
 
#define KeyGpio 0

// 设置wifi接入信息(请根据您的WiFi信息进行修改)
const char* ssid = "先贤显现";
const char* password = "a1208172292";
const char* mqttServer = "test.ranye-iot.net";
bool RetStatus = 0;
 
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
 
void connectMQTTServer()
{
  String clientId = "ESP21-Uae";
 
  // 连接MQTT服务器
  if (mqttClient.connect(clientId.c_str())) { 
    Serial.println("MQTT Server Connected.");
    Serial.println("Server Address: ");
    Serial.println(mqttServer);
    Serial.println("ClientId:");
    Serial.println(clientId);
  } else {
    Serial.print("MQTT Server Connect Failed. Client State:");
    Serial.println(mqttClient.state());
    delay(3000);
  }   
}
 
// 发布保留信息
void pubRetMQTTmsg()
{
  // 建立发布主题。
  String topicString = "ESP32-Uae-Ret";
  char publishTopic[topicString.length() + 1];  
  strcpy(publishTopic, topicString.c_str());
 
  // 建立即将发布的保留消息。消息内容为"Retained Msg"。
  String messageString = "Retained Msg"; 
  char publishMsg[messageString.length() + 1];   
  strcpy(publishMsg, messageString.c_str());
  
  // 实现ESP8266向主题发布retained信息
  // 以下publish函数第三个参数用于设置保留信息（retained message)
  if(mqttClient.publish(publishTopic, publishMsg, true)){
    Serial.println("Publish Topic:");Serial.println(publishTopic);
    Serial.println("Publish Retained message:");Serial.println(publishMsg);    
  } else {
    Serial.println("Message Publish Failed."); 
  }
}

// 删除保留信息
void delRetMQTTmsg()
{
  // 建立发布主题。
  String topicString = "ESP32-Uae-Ret";
  char publishTopic[topicString.length() + 1];  
  strcpy(publishTopic, topicString.c_str());
 
  // 建立即将发布的保留消息。消息内容为"Retained Msg"。
  String messageString = ""; 
  char publishMsg[messageString.length() + 1];   
  strcpy(publishMsg, messageString.c_str());
  
  // 实现ESP8266向主题发布retained信息
  // 以下publish函数第三个参数用于设置保留信息（retained message)
  if(mqttClient.publish(publishTopic, publishMsg, true)){
    Serial.println("Publish Topic:");Serial.println(publishTopic);
    Serial.println("Publish Retained message:");Serial.println(publishMsg);    
  } else {
    Serial.println("Message Publish Failed."); 
  }
}

 
// ESP8266连接wifi
void connectWifi()
{
 
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
  pinMode(KeyGpio, INPUT);  
  Serial.begin(115200);
 
  //设置ESP8266工作模式为无线终端模式
  WiFi.mode(WIFI_STA);
  
  // 连接WiFi
  connectWifi();
  // 设置MQTT服务器和端口号
  mqttClient.setServer(mqttServer, 1883);
  // 连接MQTT服务器
  connectMQTTServer();
  
  if (mqttClient.connected()) { // 如果开发板成功连接服务器
    pubRetMQTTmsg();               // 发布信息   
  }
}
 
void loop() 
{ 
  static byte a = 1;
  mqttClient.loop();          // 保持心跳

  if(!digitalRead(KeyGpio))
  {
    RetStatus = !RetStatus;
    a = 1;
  }

  if(a)
  {
    a = 0;
    if(RetStatus)
      delRetMQTTmsg();
    else
      pubRetMQTTmsg();
  }
 
  delay(1000);
}

