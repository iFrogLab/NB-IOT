#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);

  char temp[3];
  char c;
  int index;
  int i;
String HexToString(String t1){
  char input[] = "486921206966726F676C6162";

 // char input[50];
//  stringOne.toCharArray(charBuf, 50) 


  for (i=0;i<sizeof(input);i+= 2) {
    temp[0]=input[i];
    temp[1]=input[i+1];
    temp[2]='\0';
    index=atoi(temp);
    Serial.print(index);
    c=toascii(index);
    //Serial.print(c);
  }
  return "OK";
}
/*
int StrToHex(char str1)
{
  return (int) strtol(str1, 0, 16);
}
*/

char HexStrToChar(String WorkingString){
  long A = strtol(WorkingString.c_str(),NULL,16);
  WorkingString= String(A);
  return char(int(A));
}

String HexStrToStr(String WorkingString){
  int t1=WorkingString.length();
  for(int i=0;i<t1;i=i+2){
     String t2=WorkingString.substring(i,i+2);
     Serial.print(HexStrToChar(t2));
  }
}



void setup() {

  Serial.begin(9600);
  while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Goodnight moon!");
 
/*
String WorkingString = "48";
long A = strtol(WorkingString.c_str(),NULL,16);
WorkingString= String(A);

Serial.println(WorkingString);
Serial.println(char(int(A)));
*/


   
/*

String tSting1="486921";
byte byteArr[] = {0x41, 0x42, 0x43};
char charArr[3];
for (int c=0;c<=2;c++)
{
    temp[0]=tSting1[(c*2)];
    temp[1]=tSting1[(c*2)+1];
    temp[2]='\0';
 byte t1=atoi(temp);
 charArr[c] = char(t1);
 Serial.print(char(charArr[c]));
}
Serial.println();


  Serial.println(HexToString("486921"));

*/




  

  
  
    // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  while (!mySerial) {}
 
  delay(1000);
  mySerial.print("AT+NSOCL=0");
  mySerial.print("\r");
  delay(100);
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }  
  delay(1000);
  mySerial.print("AT+NSOCL=1");
  mySerial.print("\r");
  delay(100);
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  delay(1000);
  mySerial.print("AT+NSOCL=2");
  mySerial.print("\r");
  delay(100);
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  
  delay(1000);
  mySerial.print("AT+CGDCONT=1,\"IP\",\"nbiot\"");
  mySerial.print("\r");
  delay(100);
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  delay(1000);
  mySerial.print("AT+CGDCONT?");
  mySerial.print("\r");
  delay(100);
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  delay(1000);
  mySerial.print("AT+NSOCR=DGRAM,17,56,1,\"AF_INET\"");
  mySerial.print("\r");
  delay(100);
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  delay(1000);
  mySerial.print("AT+NSOST=1,54.180.152.89,20001,8,6966726f676c6162");
  mySerial.print("\r");
  delay(100);
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  delay(1000);
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  delay(1000);
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  delay(1000);
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  delay(1000);
  mySerial.print("AT+NSORF=1,1024");
  mySerial.print("\r");
  delay(100);
  String Str1="";
  while (mySerial.available()) {
    char Str2=mySerial.read();
    Str1=Str1+Str2;
  }
  Serial.println(Str1);
  delay(1000);
  mySerial.print("AT+NSOCL=1");
  mySerial.print("\r");
  delay(100);
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  Serial.println("========================================================================");
  Serial.println(Str1);
  Serial.println("====================");
  Str1.replace("\r","");
  Str1.replace("\n","");
  Str1.replace("OK","");
  Serial.println(Str1);
  Serial.println("====================");
  int Str1Len=Str1.length();
  int index1 = Str1.indexOf(',');
  String socketNo=Str1.substring(0,index1);
  Serial.println(socketNo);
  int index2 = Str1.indexOf(',',index1+1);
  String TargetIPAddress=Str1.substring(index1+1,index2);
  Serial.println(TargetIPAddress);
  int index3 = Str1.indexOf(',',index2+1);
  String TargetIPAddressPort=Str1.substring(index2+1,index3);
  Serial.println(TargetIPAddressPort);
  int index4 = Str1.indexOf(',',index3+1);
  String StringLen=Str1.substring(index3+1,index4);
  Serial.println(StringLen);
  int index5 = Str1.indexOf(',',index4+1);
  String StringHex=Str1.substring(index4+1,index5);
  Serial.println(StringHex);
  String StringNextLen=Str1.substring(index5+1,Str1Len);
  Serial.println(StringNextLen);
  
  Serial.println("====================");
  Serial.print(HexStrToStr(StringHex));

 
}

void loop() { // run over and over
  
  
}
