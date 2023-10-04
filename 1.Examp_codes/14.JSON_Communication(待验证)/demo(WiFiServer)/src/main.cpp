#include <Arduino.h>
#include <WiFi.h>

const char* host = "www.taichi-maker.com"; // 网络服务器地址
const int httpPort = 80;              // http端口80
 
// 设置wifi接入信息(请根据您的WiFi信息进行修改)
const char* ssid     = "CMCC-fKDy";         // 连接WiFi名
const char* password = "nbqd5g5k";          // 连接WiFi密码

WiFiServer server(80);


void runserver()
{
    // 重点1：建立WiFiClient对象用于处理客户端请求信息
    WiFiClient incomingClient = server.available();

    // 如果没有客户端连接服务器，则“跳过”本函数中后续程序内容
    if (!incomingClient) 
        return;
     
     Serial.println("====Client  Connected===");
  
    // 通过串口监视器输出客户端请求信息
    /*String clientRequest = incomingClient.readString();
    Serial.print(clientRequest);*/
    
    //192.168.1.4/uae?button=1&falsh=100
    /*if(incomingClient.find("button"))
        digitalWrite(2,incomingClient.parseInt());*/

 
    // 建立服务器响应信息
    String httpResponse =
        "HTTP/1.0 200 OK\r\n"
        "Connection: close\r\n"
        "Content-Type: text/plain;\r\n"
        "\r\n"
        "client_request_received";

    // 向客户端发送以上服务器响应信息
    incomingClient.print(httpResponse); 

    incomingClient.stop();  
    Serial.println("incomingClient stop");   
}



void setup()
{
    pinMode(2,OUTPUT);

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
    // WiFi连接成功后将通过串口监视器输出连接成功信息 
    Serial.println('\n');                     // WiFi连接成功后
    Serial.print("Connected to ");            // NodeMCU将通过串口监视器输出。
    Serial.println(WiFi.SSID());              // 连接的WiFI名称
    Serial.print("IP address:\t");            // 以及
    Serial.println(WiFi.localIP());           // NodeMCU的IP地址

    //启动服务器
    server.begin();
}

void loop()
{
    runserver();
}