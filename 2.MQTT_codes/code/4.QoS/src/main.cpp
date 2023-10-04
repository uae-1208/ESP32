/**********************************************************************
项目名称/Project          : 零基础入门学用物联网
程序名称/Program name     : subscribe_qos1
团队/Team                : 太极创客团队 / Taichi-Maker (www.taichi-maker.com)
作者/Author              : CYNO朔
日期/Date（YYYYMMDD）     : 20200813
程序目的/Purpose          : 
本程序旨在演示如何使用PubSubClient库使用ESP8266向MQTT服务器订阅信息。
订阅QoS级别为1。
 
- 在此程序控制下，ESP8266启动后将会尝试连接MQTT服务端。
  连接时cleanSession=false。
- 接下来ESP8266在订阅主题时，将QoS设置为1。
- 保持ESP8266在线，使用MQTTfx向ESP8266所订阅的主题发布QoS=1的信息。
- ESP8266将会收到信息（至此还没有体现QoS=1的优势）
- 将ESP8266断电，然后再次使用MQTTfx向ESP8266订阅主题发布QoS=1的信息。
  此时由于ESP8266未通电，所以无法接收到MQTTfx发送的信息。因此MQTT服务端
  将会保存此信息。
- 将ESP8266再次通电，ESP8266连接到MQTT服务端后，将会马上收到了MQTTfx在ESP8266断电时所发送的信息。（这就是QoS=1的优势，即客户端断电再通电后依然可以收到QoS=1信息。）
 
要使用QoS=1订阅MQTT消息，需要满足以下要求：
1 接收端要有确定的clientID 
2 接收端连接服务器时 cleanSession=False
3 发送端发布消息时 QoS=1或QoS=2
4 接收端订阅消息时 QoS=1
-----------------------------------------------------------------------
本示例程序为太极创客团队制作的《零基础入门学用物联网》中示例程序。
该教程为对物联网开发感兴趣的朋友所设计和制作。如需了解更多该教程的信息，请参考以下网页：
http://www.taichi-maker.com/homepage/esp8266-nodemcu-iot/iot-c/esp8266-nodemcu-web-client/http-request/
***********************************************************************/
#include <WiFi.h>
#include <PubSubClient.h>
 
#define BUILTIN_LED 2

// 设置wifi接入信息(请根据您的WiFi信息进行修改)
const char* ssid = "先贤显现";
const char* password = "a1208172292";
const char* mqttServer = "test.ranye-iot.net";
 
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
 
const int subQoS = 1;     // 客户端订阅主题时使用的QoS级别（截止2020-10-07，仅支持QoS = 1，不支持QoS = 2）
const bool cleanSession = false; // 清除会话（如QoS>0必须要设为false）
 
const char* willTopic = "willTopic"; // 遗嘱主题名称
const char* willMsg = "willMsg";     // 遗嘱主题信息
const int willQos = 0;               // 遗嘱QoS
const int willRetain = false;        // 遗嘱保留
 
 

 
// 收到信息后的回调函数
void receiveCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message Received [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println("");
  Serial.print("Message Length(Bytes) ");
  Serial.println(length);
 
  if ((char)payload[0] == '1') {     // 如果收到的信息以“1”为开始
    digitalWrite(BUILTIN_LED, HIGH);  // 则点亮LED。
  } else {                           
    digitalWrite(BUILTIN_LED, LOW); // 否则熄灭LED。
  }
}
 
// 订阅指定主题
void subscribeTopic()
{
  // 建立订阅主题。
  String topicString = "EPS32-Uae-Sub";
  char subTopic[topicString.length() + 1];  
  strcpy(subTopic, topicString.c_str());
  
  // 通过串口监视器输出是否成功订阅主题以及订阅的主题名称
  // 请注意subscribe函数第二个参数数字为QoS级别。这里为QoS = 1
  if(mqttClient.subscribe(subTopic, subQoS)){
    Serial.print("Subscribed Topic: ");
    Serial.println(subTopic);
  } else {
    Serial.print("Subscribe Fail...");
  }  
}
 
// 连接MQTT服务器并订阅信息
void connectMQTTserver()
{
  String clientId = "EPS32-Uae";
 
  /* 连接MQTT服务器
  boolean connect(const char* id, const char* user, 
                  const char* pass, const char* willTopic, 
                  uint8_t willQos, boolean willRetain, 
                  const char* willMessage, boolean cleanSession); 
  若让设备在离线时仍然能够让qos1工作，则connect时的cleanSession需要设置为false   */

  if (mqttClient.connect(clientId.c_str(), NULL, NULL, willTopic, willQos, willRetain, willMsg, cleanSession)) { 
    Serial.print("MQTT Server Connected. ClientId: ");
    Serial.println(clientId);
    subscribeTopic(); // 订阅指定主题
  } else {
    Serial.print("MQTT Server Connect Failed. Client State:");
    Serial.println(mqttClient.state());
    delay(5000);
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
  pinMode(BUILTIN_LED, OUTPUT);     // 设置板上LED引脚为输出模式
  digitalWrite(BUILTIN_LED, HIGH);  // 启动后开启板上LED
  Serial.begin(115200);               // 启动串口通讯
  
  //设置ESP8266工作模式为无线终端模式
  WiFi.mode(WIFI_STA);
  
  // 连接WiFi
  connectWifi();
  
  // 设置MQTT服务器和端口号
  mqttClient.setServer(mqttServer, 1883);
  mqttClient.setCallback(receiveCallback);
 
  // 连接MQTT服务器
  connectMQTTserver();
}
 
void loop() {
  // 如果开发板未能成功连接服务器，则尝试连接服务器
  if (!mqttClient.connected()) {
    connectMQTTserver();
  }
 
   // 处理信息以及心跳
   mqttClient.loop();
   
}