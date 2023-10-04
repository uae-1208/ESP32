#include <WiFi.h>
#include <ArduinoJson.h>
 
const char* host = "api.seniverse.com"; // 网络服务器地址
const int httpPort = 80;              // http端口80
 
// 设置wifi接入信息(请根据您的WiFi信息进行修改)
const char* ssid     = "CMCC-fKDy";         // 连接WiFi名
const char* password = "nbqd5g5k";          // 连接WiFi密码
 


void Deserializing(String Json)
{
    StaticJsonDocument<512> doc;

    DeserializationError error = deserializeJson(doc, Json);

    if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
    }

    JsonObject results_0 = doc["results"][0];

    JsonObject results_0_location = results_0["location"];
    const char* results_0_location_id = results_0_location["id"]; // "WTMKQ069CCJ7"
    const char* results_0_location_name = results_0_location["name"]; // "Hangzhou"
    const char* results_0_location_country = results_0_location["country"]; // "CN"
    const char* results_0_location_path = results_0_location["path"]; // "Hangzhou,Hangzhou,Zhejiang,China"
    const char* results_0_location_timezone = results_0_location["timezone"]; // "Asia/Shanghai"
    const char* results_0_location_timezone_offset = results_0_location["timezone_offset"]; // "+08:00"

    JsonObject results_0_now = results_0["now"];
    const char* results_0_now_text = results_0_now["text"]; // "Light rain"
    const char* results_0_now_code = results_0_now["code"]; // "13"
    int results_0_now_temperature = results_0_now["temperature"].as<int>(); // "24"

    const char* results_0_last_update = results_0["last_update"]; // "2022-09-04T17:40:11+08:00"

    Serial.print("location:  ");          Serial.println(results_0_location_name);
    Serial.print("weather:  ");           Serial.println(results_0_now_text);
    Serial.print("temperature:  ");       Serial.println(results_0_now_temperature);
}



// 向服务器发送HTTP请求
void wifiClientRequest()
{
    // 建立WiFi客户端对象，对象名称client
    WiFiClient client;    

    // 建立字符串，用于HTTP请求
    //String httpRequest = (String)("GET /v3/weather/now.json?key=SVd1OE4lhtZboSMUv&location=hangzhou&language=en&unit=c") 
    //String httpRequest = (String)("GET /v3/weather/daily.json?key=SVd1OE4lhtZboSMUv&location=hangzhou&language=en&unit=c&start=0&days=3") 
    String httpRequest = (String)("GET /v3/life/suggestion.json?key=SVd1OE4lhtZboSMUv&location=hangzhou&language=en") 
                       + " HTTP/1.1\r\n" 
                       + "Host: " + host + "\r\n" 
                       + "Connection: close\r\n" 
                       + "\r\n";
    // 通过串口输出连接服务器名称以便查阅连接服务器的网址                      
    Serial.print("Connecting to "); 
    Serial.print(host); 

    // 连接网络服务器，以下段落中的示例程序为本程序重点1
    if (client.connect(host, httpPort))
    { 
        Serial.println(" Success!");        // 连接成功后串口输出“Success”信息

        client.print(httpRequest);          // 向服务器发送HTTP请求
        Serial.println("Sending request: ");// 通过串口输出HTTP请求信息内容以便查阅
        Serial.println(httpRequest);     

        // 通过串口输出网络服务器响应信息， 以下段落中的示例程序为本程序重点2
        Serial.println("Web Server Response:");        


        while (client.connected() || client.available())
        { 
            if (client.available())
            {
                String line = client.readStringUntil('\n');
                Serial.println(line);
            }
        }

       if(client.find("\r\n\r\n"))
        {
            String Json = client.readString();
            Deserializing(Json);
            //Deserializing(client);      //也可以这样调用,不过这样的话Deserializing()入口参数类型就得由String改为WiFiClient了

        }

        client.stop();                      // 断开与服务器的连接
        Serial.print("Disconnected from "); // 并且通过串口输出断开连接信息
        Serial.print(host);
        Serial.print("\r\n\r\n\r\n");
    } 
    else
    {    
        // 如果连接不成功则通过串口输出“连接失败”信息
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
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi Connected!");

}
 
void loop()
{
    wifiClientRequest();  
    delay(400);
}
 
