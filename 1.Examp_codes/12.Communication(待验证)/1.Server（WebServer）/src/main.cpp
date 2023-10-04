#include <WiFi.h>
#include <WiFiMulti.h>   // 使用WiFiMulti库 
#include <WebServer.h>   // 使用WebServer库
  
WebServer server(80);    // 建立网络服务器对象，该对象用于响应HTTP请求。监听端口（80）

IPAddress local_IP(192, 168, 1, 123); // 设置ESP8266-NodeMCU联网后的IP
IPAddress gateway(192, 168, 1, 1);    // 设置网关IP（通常网关IP是WiFI路由IP）
IPAddress subnet(255, 255, 255, 0);   // 设置子网掩码
IPAddress dns(192,168,1,1);           // 设置局域网DNS的IP（通常局域网DNS的IP是WiFI路由IP） 与网关相同

// 设置wifi接入信息(请根据您的WiFi信息进行修改)
const char* ssid     = "CMCC-fKDy";         // 连接WiFi名
const char* password = "nbqd5g5k";          // 连接WiFi密码

void handleUpdate()
{
    float floatValue = server.arg("float").toFloat();  // 获取客户端发送HTTP信息中的浮点数值
    int intValue = server.arg("int").toInt();        // 获取客户端发送HTTP信息中的整数数值
    int buttonValue = server.arg("button").toInt();  // 获取客户端发送HTTP信息中的按键控制量

    server.send(200, "text/plain", "Received");                 // 发送http响应


    // 通过串口监视器输出获取到的变量数值
    Serial.print("floatValue = ");  Serial.println(floatValue);  
    Serial.print("intValue = ");  Serial.println(intValue); 
    Serial.print("buttonValue = ");  Serial.println(buttonValue);   
    Serial.println("=================");    
}



void setup(void)
{
    Serial.begin(115200);          // 启动串口通讯
    Serial.println("");


    // 设置开发板网络环境
    if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("Failed to Config ESP8266 IP"); 
    } 

    //开始连接wifi
    WiFi.begin(ssid, password);

    //等待WiFi连接,连接成功打印IP
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }

    // WiFi连接成功后将通过串口监视器输出连接成功信息 
    Serial.println('\n');
    Serial.print("Connected to ");
    Serial.println(WiFi.SSID());              // 通过串口监视器输出连接的WiFi名称
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());           // 通过串口监视器输出ESP8266-NodeMCU的IP

    server.on("/update", handleUpdate);        // 处理服务器更新函数

    server.begin();                            // 启动网站服务
    Serial.println("HTTP server started");
}
 
void loop(void)
{
    server.handleClient();                    // 检查http服务器访问
}
 

