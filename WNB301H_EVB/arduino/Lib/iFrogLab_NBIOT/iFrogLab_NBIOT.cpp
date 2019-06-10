/*
  iFrogLab_NBIOT.h - Test library for ifroglab NB-IOT - implementation
  Copyright (c) 2019 Powen Ko, iFroglab.com All right reserved.
*/

// For Arduino 1.0 and earlier
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
// include this library's description file
#include "iFrogLab_NBIOT.h"
#include <SoftwareSerial.h>


// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

iFrogLab_NBIOT::iFrogLab_NBIOT(int RX, int TX)
{

  m_Debug=1;
  m_RX=RX;
  m_TX=TX;
  m_port=0;

  static SoftwareSerial mySerial2(m_RX,m_TX);    //setup RX, TX Pin
    mySerial=&mySerial2;
    mySerial->begin(9600); 


    if(m_Debug==1){
      Serial.begin(9600);
      while (!Serial) {
            ; // wait for serial port to connect. Needed for native USB port only
      }
    }
}

// Public Methods //////////////////////////////////////////////////////////////
// Check the bands by using “AT+NBAND?”. WNB301H supports 5,8,28,3,20,1. You
// can set curtain band by yourself by AT+NBAND=#. 
// # = 5 as China Telecom, 
// * = 8 as China Mobile。
// After re-config band, you need to reboot module, by
// software reset “AT+NRB” or hardware reset(”Reset button”
/*
------------------

+NBAND:8,28,5,20,3,1

OK

------------------
*/
String iFrogLab_NBIOT::SendCmd(String cmd)
{
//#String cmd="AT+NBAND?";
  String dataStr="";
  mySerial->print(cmd);
  mySerial->print("\r");
  delay(10);
  if (mySerial->available()) {
    dataStr=dataStr+mySerial->readString();// read the incoming data as string
    dataStr=dataStr+mySerial->readString();// read the incoming data as string
    dataStr=dataStr+mySerial->readString();// read the incoming data as string
    if(m_Debug==1) Serial.println(dataStr);
  }
  return dataStr;
} 
String iFrogLab_NBIOT::CheckTheBands(void)
{
  String cmd="AT+NBAND?";
  String dataStr="";
  mySerial->println(cmd);
  delay(10);
  if (mySerial->available()) {
    dataStr=mySerial->readString();// read the incoming data as string
    if(m_Debug==1) Serial.println(dataStr);
  }
  // close sockets
  for(int i=0;i<3;i++){
    CloseSocket(i);
  }
  return dataStr;

} 
String iFrogLab_NBIOT::SetCheckTheBands(String i_value)
{

  String cmd="AT+NBAND="+i_value;
  String dataStr="";
  mySerial->println(cmd);
  delay(10);
  if (mySerial->available()) {
    dataStr=mySerial->readString();// read the incoming data as string
    if(m_Debug==1) Serial.println(dataStr);
  }
  return dataStr;

} 
/*
Check SIM
You are able to check SIM card is ready or not by “AT+CIMI” and “AT +NCCID”.
If SIM card is ready, what you can get is: IMSI number, ICCID number and CFUN
is 1. While using “AT +NCCID”, if no SIM card is present, or the SIM card is
unreadable, no data is returned. “AT+CIMI” causes the TA to return <IMSI>,
which is intended to permit the TE to identify the individual SIM card.
“AT+CFUNC?” returned value 1 means RF full functionality
*/
/*
------------------

+NBAND:8,28,5,20,3,1

OK

------------------
*/

int *iFrogLab_NBIOT::CheckSIM_IMSI(void)
{
  static int val[10];
  String cmd; 
  //cmd="AT+NCCID";
  cmd="AT+CFUN?";
  String dataStr="";
  mySerial->println(cmd);
  delay(10);
  int byteCount = mySerial->available();
  if (byteCount > 5) // don't do anything until you get 3 characters (header plus the two data bytes
  {
    //Serial.print("byteCount = ");
    //Serial.println(byteCount);
    for(int b=0; b<byteCount; b++)
    {
      //Serial.print(b);
      //Serial.print(") ");
      val[b] = mySerial->read();
      if(m_Debug==1) Serial.println(val[b]);
      //Serial.print("val = ");
      //Serial.println(val, HEX);
    }
  }

 

  return val;
 

} 

int *iFrogLab_NBIOT::CheckSIM_NCCID(void)
{

  static int val[10];
  String cmd; 
  cmd="AT+NCCID";
  //cmd="AT+CFUN?";
  String dataStr="";
  mySerial->println(cmd);
  delay(10);
  int byteCount = mySerial->available();
  if (byteCount > 5) // don't do anything until you get 3 characters (header plus the two data bytes
  {
    //Serial.print("byteCount = ");
    //Serial.println(byteCount);
    for(int b=0; b<byteCount; b++)
    {
      //Serial.print(b);
      //Serial.print(") ");
      val[b] = mySerial->read();
      if(m_Debug==1) Serial.println(val[b]);
      //Serial.print("val = ");
      //Serial.println(val2, HEX);
    }
  }

  return val;
}
String iFrogLab_NBIOT::CheckSignal()
{

  String cmd="AT+CSQ";
  String dataStr="";
  mySerial->print(cmd);
  mySerial->print("\r");
  delay(10);
  if (mySerial->available()) {
    dataStr=mySerial->readString();// read the incoming data as string
    //if(m_Debug==1) Serial.println(dataStr);
  }
  return dataStr;

} 
String iFrogLab_NBIOT::CheckIP()
{

  String cmd="AT+CGPADDR";
  String dataStr="";
  mySerial->print(cmd);
  mySerial->print("\r");
  delay(10);
  if (mySerial->available()) {
    dataStr=mySerial->readString();// read the incoming data as string
    if(m_Debug==1) Serial.println(dataStr);
  }
  return dataStr;

} 


String iFrogLab_NBIOT::SendString(String ipaddress1,int i_port,String str1,String Telcom)
{
 
  String alldataStr="";
  String dataStr="";
  if(Telcom=="EasTone"){
     mySerial->println("AT+CGDCONT=1,\"IP\",\"nbiot\"");  //EasTone(遠傳)
  }else if(Telcom=="Taiwan Mobile"){
     mySerial->println("AT+CGDCONT=1,\"IP\",\"test.nbiot\"");  //EasTone(遠傳)
  }else{

  }
  delay(10);
  if (mySerial->available()) {
    dataStr=mySerial->readString(); 
    if(m_Debug==1) Serial.println(dataStr);
  }
  alldataStr=alldataStr+dataStr;



  mySerial->println("AT+CGDCONT?");
  delay(10);
  if (mySerial->available()) {
    dataStr=mySerial->readString();
    if(m_Debug==1) Serial.println(dataStr);
  }
  alldataStr=alldataStr+dataStr;


  m_port=i_port;
  String port=String(m_port, DEC); 
  //m_port++;
  mySerial->println("AT+NSOCR=DGRAM,17,"+port+",1,\"AF_INET\"");
  String key1="1";
  delay(10);
  if (mySerial->available()) {
    dataStr=mySerial->readString();
    if(m_Debug==1) Serial.println("Send==> AT+NSOCR=DGRAM,17,"+port+",1,\"AF_INET\"");
    if(m_Debug==1) Serial.println(dataStr);
    if(dataStr.length()<=1) return "error 001: AT+NSOCR does not return socked number ";
    key1=dataStr.substring(2,3);
    Serial.println("--------");
    Serial.println(key1);
    Serial.println("--------");
  }
  alldataStr=alldataStr+dataStr;





  String key2="1,6";
  String key3="1,29";
  //mySerial->println("AT+NSOST=1,54.180.152.89,20001,8,6966726f676c6162");
  String t1="AT+NSOST="+key1+","+ipaddress1+","+port+",8,6966726f676c6162";
         //t1="AT+NSOST=1,54.180.152.89,20001,8,6966726f676c6162";
  Serial.println(t1);
  mySerial->print(t1);
  mySerial->print("\r");
  delay(2000);
  if (mySerial->available()) {
    dataStr=mySerial->readString();
    if(m_Debug==1) Serial.println(dataStr);
    if(dataStr.length()<=1) return "error";
    key2=dataStr.substring(2,5);
    key3=dataStr.substring(23,28);
    Serial.println("----dataStr----");
    Serial.println(dataStr);
    Serial.println("----key2----");
    Serial.println(key2);
    Serial.println("----key3----");
    Serial.println(key3);
    Serial.println("--------");
  }
  alldataStr=alldataStr+dataStr;


  t1="AT+NSORF="+key2;
  t1="AT+NSORF=1,1024";
  Serial.println(t1);
  mySerial->print(t1);
  mySerial->print("\r");


  delay(3000);
  String datareturn="No data";
  for(int i=0;i<3000;i++){
    if (mySerial->available()) {
      //delay(3000);
        datareturn=mySerial->readString();
      // if(m_Debug==1) 
      Serial.println("----NSORF----");
      Serial.println(datareturn);
      Serial.println("--------");
      break;
    }
    delay(1);
  }
  alldataStr=dataStr;alldataStr+dataStr;
  CloseSocket(key1.toInt());
  return datareturn;
} 


String iFrogLab_NBIOT::CloseSocket(int portNumer)
{
  String dataStr="";
  //Close socket,  關閉socket
  mySerial->print("AT+NSOCL="+String(portNumer, DEC));
  mySerial->print("\r");
  delay(10);
  if (mySerial->available()) {
    dataStr=mySerial->readString();
    if(m_Debug==1) Serial.println(dataStr);
  }
  return dataStr;


}