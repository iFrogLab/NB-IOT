
/*
 * iFrogLab IL-LORA1272 
 * Function功能,     ARDUINO , IFROGLAB LORA IL-LORA1272
 * GND接地,          GND     ,Pin 1, 
 * Host_IRQ接收反應, Pin 9   ,Pin 2, 
 * VDD電源,          3.3V    ,Pin 3, 
 * UART TX,         Pin 10  ,Pin 7 
 * UART RX,         Pin 11  ,Pin 8 
 * 
 * tutorial: please see http://www.ifroglab.com/?p=7641
 */
#include <iFrogLab_NBIOT.h>

int counter=0;
iFrogLab_NBIOT NBIOT(10,11);  // RX, TX

void setup()  {
  Serial.begin(9600);
  ///////////////////////////
  // Check Bands
  String data=NBIOT.CheckTheBands();
  Serial.println("CheckTheBands");
  Serial.println(data);
  Serial.println("------------------");
  
  ///////////////////////////
  // Check SIM card IMSI
  /*
  int* data2=NBIOT.CheckSIM_IMSI();
  Serial.println("CheckSIM_IMSI");
  Serial.print("val = ");
  for(int b=0; b<10; b++)
  {
      int val = data2[b];
      Serial.print(val, HEX);
  }
  Serial.println("");
  Serial.println("------------------");
  */
 
  ///////////////////////////
  // Check SIM card
  /*
  int* data3=NBIOT.CheckSIM_NCCID();  
  Serial.println("CheckSIM_NCCID");
  Serial.print("val = ");
  for(int b=0; b<10; b++)
  {
      int val = data3[b];
      Serial.print(val, HEX);
  }
  Serial.println("");
  Serial.println("------------------");
  */
  ///////////////////////////
  //CheckSignal
  // 訊號強度
  
  String strCheckSignal=NBIOT.CheckSignal();
  Serial.println("CheckSignal");
  Serial.println(strCheckSignal);
  Serial.println("------------------");


  ///////////////////////////
  //　get IP Address
  // 取得IP位置
  String str3=NBIOT.CheckIP();
  Serial.println("CheckIP");
  Serial.println(str3);
  Serial.println("------------------");


  ///////////////////////////
  // SendString
  // Send information to the telecommunications provider
  // 送資料到電信商
  String IPAddress1="211.77.241.100";
  IPAddress1="54.180.152.89";
  String str1="hello";
  String str2=NBIOT.SendString(IPAddress1,20001,str1,"EasTone");  //EasTone(遠傳)
  //String str2=NBIOT.SendString(IPAddress1,str1,"Taiwan Mobile");  //Taiwan Mobile(台灣大哥大)
  Serial.println("SendString");
  Serial.println(str2);
  Serial.println("------------------");

  

  delay(5000);
  
}

String dataStr="";
void loop() { // run over and over
  if (NBIOT.mySerial->available()) {
    Serial.write(NBIOT.mySerial->read());
  }
  if (Serial.available()) {
    NBIOT.mySerial->write(Serial.read());
  }

}
