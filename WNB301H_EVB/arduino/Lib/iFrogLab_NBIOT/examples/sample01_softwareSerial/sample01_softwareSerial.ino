#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);


void setup() {

  Serial.begin(9600);
  while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Goodnight moon! AA");
  
    // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  while (!mySerial) {}
  

}
void loop() { // run over and over
   
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
  
}
