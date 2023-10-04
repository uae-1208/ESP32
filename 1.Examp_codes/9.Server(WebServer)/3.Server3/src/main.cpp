#include <Arduino.h>
#include <WiFi.h>       
#include <WiFiMulti.h>   
#include <WebServer.h>  
 
 
WiFiMulti wifiMulti;     // 建立ESP32WiFiMulti对象,对象名称是'wifiMulti'
WebServer ESP32_server(80);// 建立网络服务器对象，该对象用于响应HTTP请求。监听端口（80）
 
const char* ssid     = "CMCC-fKDy";         // 连接WiFi名
const char* password = "nbqd5g5k";          // 连接WiFi密码
short touch_value; 
 

String sendHTML(short touch_value){
  
  String htmlCode = "<!DOCTYPE html> <html>\n";
  htmlCode +="<head><meta http-equiv='refresh' content='0.05'/>\n";    //0.05s自动刷新
  htmlCode +="<title>ESP32 Butoon State</title>\n";
  htmlCode +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  htmlCode +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  htmlCode +="</style>\n";
  htmlCode +="</head>\n";
  htmlCode +="<body>\n";
  htmlCode +="<h1>The Uae Server</h1>\n";
  
  
  htmlCode +="<p>Touch Value: ";
  htmlCode += (char)('0'+(touch_value/100));
  htmlCode += (char)('0'+((touch_value%100)/10));
  htmlCode += (char)('0'+(touch_value%10));

  htmlCode += "</p>\n";
    
  htmlCode +="</body>\n";
  htmlCode +="</html>\n";
 
  return htmlCode;
}


void handleRoot() {   
  ESP32_server.send(200, "text/html", sendHTML(touch_value)); 
}
 
// 设置处理404情况的函数'handleNotFound'
void handleNotFound(){                                        // 当浏览器请求的网络资源无法在服务器找到时，
  ESP32_server.send(404, "text/plain", "404: Not found");   // NodeMCU将调用此函数。
}



void setup(){
  Serial.begin(115200);   // 启动串口通讯
  
  WiFi.begin(ssid, password);                  // 启动网络连接

  Serial.println("Connecting ...");                       
  
  int i = 0;                                 
  while (WiFi.status() != WL_CONNECTED) {      // WiFi.status()函数的返回值是由NodeMCU的WiFi连接状态所决定的。 
      delay(1000);                               // 如果WiFi连接成功则返回值为WL_CONNECTED                       
      Serial.print(i++); Serial.print(' ');      // 此处通过While循环让NodeMCU每隔一秒钟检查一次WiFi.status()函数返回值
    }                                            // 同时NodeMCU将通过串口监视器输出连接时长读秒。


  Serial.println('\n');                     // WiFi连接成功后
  Serial.print("Connected to ");            // NodeMCU将通过串口监视器输出。
  Serial.println(WiFi.SSID());              // 连接的WiFI名称
  Serial.print("IP address:\t");            // 以及
  Serial.println(WiFi.localIP());           // NodeMCU的IP地址
  
  ESP32_server.begin();                   // 启动网站服务                
  ESP32_server.on("/", handleRoot);       // 设置服务器根目录即'/'的函数'handleRoot'
  ESP32_server.onNotFound(handleNotFound);// 设置处理404情况的函数'handleNotFound'        
 
  Serial.println("HTTP ESP32_server started");
}
 
void loop(){
  ESP32_server.handleClient();     //处理http服务器访问
  touch_value = touchRead(T0);     //GPIO4 D4
}
 
                                                                      



