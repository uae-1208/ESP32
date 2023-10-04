#include "SPIFFS.h"
#include <FS.h>  
 
String file_name = "/uae/notes.txt"; //被读取的文件位置和名称
String file_name1 = "/uae/text.txt"; //被读取的文件位置和名称
 
void setup() {
  Serial.begin(115200);
  Serial.println("");
  
/**********************************************************************************************************/ 
  Serial.print("System Informatin:   ");
  Serial.println("SPIFFS format start");
  SPIFFS.format();    // 格式化SPIFFS
  Serial.print("System Informatin:   ");
  Serial.println("SPIFFS format finish");
/**********************************************************************************************************/ 


/**********************************************************************************************************/ 
  Serial.print("System Informatin:   ");
  if(SPIFFS.begin()){ // 启动SPIFFS
    Serial.println("SPIFFS Started.");
  } else {
    Serial.println("SPIFFS Failed to Start.");
  }

  File dataFile = SPIFFS.open(file_name, "w");// 建立File对象用于向SPIFFS中的file对象（即/notes.txt）写入信息
  dataFile.println("Hello IOT World.");       // 向dataFile写入字符串信息
  dataFile.close();                           // 完成文件写入后关闭文件
  Serial.print("System Informatin:   ");
  Serial.println("Finished Writing data to SPIFFS");
/**********************************************************************************************************/ 


/**********************************************************************************************************/ 
//确认闪存中是否有file_name文件
  Serial.print("System Informatin:   ");
  Serial.print(file_name);
  if (SPIFFS.exists(file_name))
    Serial.println(" FOUND.");
  else 
    Serial.print(" NOT FOUND.");
  

//建立File对象用于从SPIFFS中读取文件
  dataFile = SPIFFS.open(file_name, "r"); 

  Serial.print("Get Informatin:      ");
//读取文件内容并且通过串口监视器输出文件信息
  for(int i=0; i<dataFile.size(); i++){
    Serial.print((char)dataFile.read());       
  }

//完成文件读取后关闭文件
  dataFile.close();                          
/**********************************************************************************************************/ 


/**********************************************************************************************************/ 
  dataFile = SPIFFS.open(file_name, "a"); 
  dataFile.println("Something Added. You know what I mean!");       // 向dataFile写入字符串信息
  dataFile.close();                           // 完成文件写入后关闭文件
/**********************************************************************************************************/ 

/**********************************************************************************************************/ 
  Serial.print("System Informatin:   ");
  Serial.print("Read the ");
  Serial.print(file_name);
  Serial.println("  again.");

//建立File对象用于从SPIFFS中读取文件
  dataFile = SPIFFS.open(file_name, "r"); 
//读取文件内容并且通过串口监视器输出文件信息
  Serial.print("Get Informatin:      ");
  for(int i=0; i<dataFile.size(); i++){
    Serial.print((char)dataFile.read());       
  }

//完成文件读取后关闭文件
  dataFile.close();
/**********************************************************************************************************/ 



}
 
void loop() {
}

