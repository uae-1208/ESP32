#include <Arduino.h>
#include <WiFi.h>       
 
 
const char* ssid     = "CMCC-fKDy";         // 连接WiFi名
const char* password = "nbqd5g5k";          // 连接WiFi密码
                                            
void setup() {
    Serial.begin(115200);        
  
    WiFi.begin(ssid, password);                  // 启动网络连接
    Serial.print("Connecting to ");              // 串口监视器输出网络连接信息
    Serial.print(ssid); 
    Serial.println(" ..."); 
  
    int i = 0;                                   // 这一段程序语句用于检查WiFi是否连接成功
    while (WiFi.status() != WL_CONNECTED) {      // WiFi.status()函数的返回值是由NodeMCU的WiFi连接状态所决定的。 
      delay(1000);                               // 如果WiFi连接成功则返回值为WL_CONNECTED                       
      Serial.print(i++); Serial.print(' ');      // 此处通过While循环让NodeMCU每隔一秒钟检查一次WiFi.status()函数返回值
    }                                            // 同时NodeMCU将通过串口监视器输出连接时长读秒。


    Serial.println("");                          // WiFi连接成功后
    Serial.println("Connection established!");   // NodeMCU将通过串口监视器输出"连接成功"信息。
    Serial.print("IP address:    ");             // 同时还将输出NodeMCU的IP地址。这一功能是通过调用
    Serial.println(WiFi.localIP());              // WiFi.localIP()函数来实现的。该函数的返回值即NodeMCU的IP地址。
}
 
void loop() {                                   
}