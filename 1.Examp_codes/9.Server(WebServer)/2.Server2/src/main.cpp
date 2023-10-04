#include <Arduino.h>
#include <WiFi.h>       
#include <WiFiMulti.h>   
#include <WebServer.h>  
 
WiFiMulti wifiMulti;                // 建立WiFiMulti对象,对象名称是'wifiMulti'
 
WebServer ESP32_server(80);       // 建立WebServer对象，对象名称为ESP32_server
                                    // 括号中的数字是网路服务器响应http请求的端口号
                                    // 网络服务器标准http端口号为80，因此这里使用80为端口号
                                                                         
/*void handleRoot() {       
  ESP32_server.send(200, "text/html", "<form action=\"/uae\" method=\"POST\"><input type=\"submit\" value=\"Iverson Guo: LED\"></form>");
}*/
 
//处理LED控制请求的函数'handleLED'
/*void handle() {                          
  digitalWrite(2,!digitalRead(2));// 改变LED的点亮或者熄灭状态
  ESP32_server.sendHeader("Location","/");          // 跳转回页面根目录
  ESP32_server.send(303);                           // 发送Http相应代码303 跳转  
}*/

void handleRoot() {       
  ESP32_server.send(200, "text/html", "<form action=\"/uae1\" method=\"POST\"><input type=\"submit\" value=\"CountDown:3!\"></form>");
}

void handle1() {                          
   ESP32_server.send(200, "text/html", "<form action=\"/uae2\" method=\"POST\"><input type=\"submit\" value=\"CountDown:2!\"></form>");
}
 
void handle2() {                          
   ESP32_server.send(200, "text/html", "<form action=\"/uae3\" method=\"POST\"><input type=\"submit\" value=\"CountDown:1!\"></form>");
}

void handle3() {      
   ESP32_server.sendHeader("Location","/");                   
   ESP32_server.send(303);
}

// 设置处理404情况的函数'handleNotFound'
void handleNotFound(){
  ESP32_server.send(404, "text/plain", "404: Not found"); // 发送 HTTP 状态 404 (未找到页面) 并向浏览器发送文字 "404: Not found"
}

void setup(void){
  Serial.begin(115200);          // 启动串口通讯
  pinMode(2,OUTPUT);

  //通过addAp函数存储  WiFi名称       WiFi密码
  wifiMulti.addAP("taichi-maker", "12345678");  // 这三条语句通过调用函数addAP来记录3个不同的WiFi网络信息。
  wifiMulti.addAP("taichi-maker2", "87654321"); // 这3个WiFi网络名称分别是taichi-maker, taichi-maker2, taichi-maker3。
  wifiMulti.addAP("CMCC-fKDy", "nbqd5g5k"); // 这3个网络的密码分别是123456789，87654321，13572468。

 
  int i = 0;                                 
  while (wifiMulti.run() != WL_CONNECTED) {  // 此处的wifiMulti.run()是重点。通过wifiMulti.run()，NodeMCU将会在当前
    delay(1000);                             // 环境中搜索addAP函数所存储的WiFi。如果搜到多个存储的WiFi那么NodeMCU
    Serial.print(i++); Serial.print(' ');    // 将会连接信号最强的那一个WiFi信号。
  }                                          // 一旦连接WiFI成功，wifiMulti.run()将会返回“WL_CONNECTED”。这也是
                                             // 此处while循环判断是否跳出循环的条件。
 
  // WiFi连接成功后将通过串口监视器输出连接成功信息 
  Serial.println('\n');                     // WiFi连接成功后
  Serial.print("Connected to ");            // NodeMCU将通过串口监视器输出。
  Serial.println(WiFi.SSID());              // 连接的WiFI名称
  Serial.print("IP address:\t");            // 以及
  Serial.println(WiFi.localIP());           // NodeMCU的IP地址
  
//--------"启动网络服务功能"程序部分开始-------- //  此部分为程序为本示例程序重点1
  ESP32_server.begin();                   //  详细讲解请参见太极创客网站《零基础入门学用物联网》
  ESP32_server.on("/", HTTP_GET, handleRoot);     // 设置服务器根目录即'/'的函数'handleRoot'
  ESP32_server.on("/uae1", HTTP_POST, handle1); 
  ESP32_server.on("/uae2", HTTP_POST, handle2); 
  ESP32_server.on("/uae3", HTTP_POST, handle3); 
  ESP32_server.onNotFound(handleNotFound);        // 设置处理404情况的函数'handleNotFound'
//--------"启动网络服务功能"程序部分结束--------
  Serial.println("HTTP ESP32_server started");//  告知用户ESP32网络服务功能已经启动
}
 
/* 以下函数语句为本示例程序重点3
详细讲解请参见太极创客网站《零基础入门学用物联网》
第3章-第2节 3_2_1_First_Web_Server 的说明讲解*/  
void loop(void){
  ESP32_server.handleClient();     // 处理http服务器访问
}
 
