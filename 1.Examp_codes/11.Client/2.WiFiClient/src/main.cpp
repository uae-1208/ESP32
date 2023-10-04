#include <WiFi.h>
 
const char* host = "www.taichi-maker.com"; // 网络服务器地址
const int httpPort = 80;              // http端口80
 
// 设置wifi接入信息(请根据您的WiFi信息进行修改)
const char* ssid     = "CMCC-fKDy";         // 连接WiFi名
const char* password = "nbqd5g5k";          // 连接WiFi密码
 

// 向服务器发送HTTP请求
void wifiClientRequest()
{
  // 建立WiFi客户端对象，对象名称client
  WiFiClient client;    
 
  // 建立字符串，用于HTTP请求
//String httpRequest =  String("GET /") + " HTTP/1.1\r\n" +
  String httpRequest =  (String)("GET /homepage/esp8266-nodemcu-iot/iot-c/esp8266-nodemcu-web-client/") + " HTTP/1.1\r\n" +
                        "Host: " + host + "\r\n" +
                        "Connection: close\r\n" +
                        "\r\n";
  
  // 通过串口输出连接服务器名称以便查阅连接服务器的网址                      
  Serial.print("Connecting to "); 
  Serial.print(host); 
 
  // 连接网络服务器，以下段落中的示例程序为本程序重点1
  if (client.connect(host, httpPort)){ 
    Serial.println(" Success!");        // 连接成功后串口输出“Success”信息
    
    client.print(httpRequest);          // 向服务器发送HTTP请求
    Serial.println("Sending request: ");// 通过串口输出HTTP请求信息内容以便查阅
    Serial.println(httpRequest);     
    
  // 通过串口输出网络服务器响应信息， 以下段落中的示例程序为本程序重点2
    Serial.println("Web Server Response:");        
    while (client.connected() || client.available()){ 
      if (client.available()){
        String line = client.readStringUntil('\n');
        Serial.println(line);
      }
    }
    
    client.stop();                      // 断开与服务器的连接
    Serial.print("Disconnected from "); // 并且通过串口输出断开连接信息
    Serial.print(host);
    
  } else{    // 如果连接不成功则通过串口输出“连接失败”信息
    Serial.println(" connection failed!");
    client.stop();
  }  
}

void setup()
  {
  //初始化串口设置
  Serial.begin(115200);
  Serial.println("");

  //设置ESP8266工作模式为无线终端模式
  WiFi.mode(WIFI_STA);

  //开始连接wifi
  WiFi.begin(ssid, password);

  //等待WiFi连接,连接成功打印IP
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected!");

  wifiClientRequest();  
}
 
void loop()
{}
 
