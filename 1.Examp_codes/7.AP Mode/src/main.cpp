#include <Arduino.h>
#include <WiFi.h>       
 
 
const char *ssid = "Uae' WiFi"; 
const char *password = "a1208172292"; 

 
void setup() {
  Serial.begin(115200);              // 启动串口通讯
 
  WiFi.softAP(ssid, password);      // 此语句是重点。WiFi.softAP用于启动NodeMCU的AP模式。
                                    // 括号中有两个参数，ssid是WiFi名。password是WiFi密码。

 
  Serial.print("Access Point: ");    // 通过串口监视器输出信息
  Serial.println(ssid);              // 告知用户NodeMCU所建立的WiFi名
  Serial.print("IP address: ");      // 以及NodeMCU的IP地址
  Serial.println(WiFi.softAPIP());   // 通过调用WiFi.softAPIP()可以得到NodeMCU的IP地址
}
 
void loop() { 
}