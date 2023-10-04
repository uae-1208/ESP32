#include <WiFi.h>
#include <WiFiMulti.h>   // 使用WiFiMulti库 
 
 
bool buttonState;       //存储客户端按键控制数据
float clientFloatValue; //存储客户端发送的浮点型测试数据
int clientIntValue;     //存储客户端发送的整数型测试数据
 
const char* host = "192.168.1.123";    // 即将连接服务器网址/IP
const int httpPort = 80;               // 即将连接服务器端口
 
// 设置wifi接入信息(请根据您的WiFi信息进行修改)
const char* ssid     = "CMCC-fKDy";         // 连接WiFi名
const char* password = "nbqd5g5k";          // 连接WiFi密码


void wifiClientRequest()
{
    WiFiClient client;  

    // 将需要发送的数据信息放入客户端请求
    String url = "/update?float=" + String(clientFloatValue) + 
                "&int=" + String(clientIntValue) +
                "&button=" + String(buttonState);
                            
    // 建立字符串，用于HTTP请求
    String httpRequest =  String("GET ") + url + " HTTP/1.1\r\n" +
                        "Host: " + host + "\r\n" +
                        "Connection: close\r\n" +
                        "\r\n";
                        
    Serial.print("Connecting to "); 
    Serial.print(host); 

    if (client.connect(host, httpPort)) 
    {  //如果连接失败则串口输出信息告知用户然后返回loop
        Serial.println(" Sucess");

        client.print(httpRequest);          // 向服务器发送HTTP请求
        Serial.println("Sending request: ");// 通过串口输出HTTP请求信息内容以便查阅
        Serial.println(httpRequest);        
    } 
    else
        Serial.println(" failed");

    client.stop();                         
}


void setup(void)
{
    Serial.begin(115200);                  // 启动串口通讯
    Serial.println("");


    //设置ESP8266工作模式为无线终端模式
    WiFi.mode(WIFI_STA);
    
    //开始连接wifi
    WiFi.begin(ssid, password);
    
    //等待WiFi连接,连接成功打印IP
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi Connected!");
    Serial.println(WiFi.SSID());              // 通过串口监视器输出连接的WiFi名称
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());           // 通过串口监视器输出ESP8266-NodeMCU的IP
}
 
void loop(void)
{

    // 改变测试用变量数值用于服务器端接收数据检测
    clientFloatValue += 1.5;
    clientIntValue += 2;

    // 发送请求
    wifiClientRequest();
    delay(1000);
}
 
