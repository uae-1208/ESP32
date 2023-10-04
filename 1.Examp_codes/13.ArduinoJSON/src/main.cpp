#include <Arduino.h>
#include <ArduinoJson.h>

/*{
  "results": [
    {
      "location": {
        "name": "Beijing",
        "country": "CN"
      },
      "now": {
        "text": "Clear",
        "code": "1",
        "temperature": "3"
      },
      "last_update": "2020-03-01T20:10:00+08:00"
    }
  ]
}*/


void Deserialization(String stream)
{
    StaticJsonDocument<384> doc;
    
    DeserializationError error = deserializeJson(doc, stream);    //此时stream的位置也可以是别的流

    if (error) 
    {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
    }

    JsonObject results_0 = doc["results"][0];

    const char* results_0_location_name = results_0["location"]["name"]; // "Beijing"
    const char* results_0_location_country = results_0["location"]["country"]; // "CN"

    JsonObject results_0_now = results_0["now"];
    const char* results_0_now_text = results_0_now["text"]; // "Clear"
    int results_0_now_code = results_0_now["code"].as<int>(); // "1"
    int results_0_now_temperature = results_0_now["temperature"].as<int>(); // "3"

    const char* results_0_last_update = results_0["last_update"]; // "2020-03-01T20:10:00+08:00"

    Serial.print("name:");          Serial.println(results_0_location_name);
    Serial.print("country:");       Serial.println(results_0_location_country);
    Serial.print("text:");          Serial.println(results_0_now_text);
    Serial.print("code:");          Serial.println(results_0_now_code);
    Serial.print("temperature:");   Serial.println(results_0_now_temperature);
    Serial.print("last_update:");   Serial.println(results_0_last_update);
}


String Serialization(void)
{
    String stream;
    StaticJsonDocument<256> doc;

    JsonObject results_0 = doc["results"].createNestedObject();

    JsonObject results_0_location = results_0.createNestedObject("location");
    results_0_location["name"] = "Beijing";
    results_0_location["country"] = "CN";

    JsonObject results_0_now = results_0.createNestedObject("now");
    results_0_now["text"] = "Clear";
    results_0_now["code"] = "1";
    results_0_now["temperature"] = "3";
    results_0["last_update"] = "2020-03-01T20:10:00+08:00";

    serializeJson(doc, stream);

    return stream;
}


void setup()
{
    String stream ;

    Serial.begin(115200);
    pinMode(2,OUTPUT);
    
    stream = Serialization();
    Deserialization(stream);

}

void loop()
{
    // put your main code here, to run repeatedly:
    digitalWrite(2,HIGH);
    delay(1000);    
    digitalWrite(2,LOW);
    delay(400);
}