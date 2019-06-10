/*
  Test.h - Test library for Wiring - description
  Copyright (c) 2006 John Doe.  All right reserved.
*/

// ensure this library description is only included once
#ifndef iFrogLab_NBIOT_h
#define iFrogLab_NBIOT_h



#include <inttypes.h>
#include <SoftwareSerial.h>


// library interface description
class iFrogLab_NBIOT
{
  // user-accessible "public" interface
  public:
    iFrogLab_NBIOT(int RX, int TX);
    String CheckTheBands(void);              // Check Bands
    String SetCheckTheBands(String i_value); // Set Check Bands
    int *CheckSIM_IMSI(void);              // Check SIM IMSI
    int *CheckSIM_NCCID(void);              // Check SIM CCID
    String CheckSignal(void);              // Check Signal
    String CheckIP();              // Check IP
    String SendString(String ipaddress1,int i_port,String str1,String Telcom);              // Send String
    //String SendHexArray(int* t1,int len);              // CheckSignal

    String CloseSocket(int portNumer);
    String SendCmd(String cmd);

    SoftwareSerial *mySerial;
    
  private:
    int m_port;

    byte m_TXRX;
    byte m_Freq1;
    byte m_Freq2;
    byte m_Freq3;
    byte m_Power;

    uint8_t m_FW_Ver=6;
    uint32_t m_UniqueNumber=0;

/*
    byte  Fun_CRC(byte t1[], int len);   //計算出CRC 
    void  Fun_PrintArray(byte t1[], byte len);
    void  Fun_AddArray(byte source[],byte target[],int sourceLen,int targetStart);
*/
    //void iFrogLabLoRaLibrary::Message_error();

    unsigned long m_lastTime;
    uint8_t m_pin;
    int m_brightness;
    int m_fadeAmount;
    unsigned long m_delayDuration;

    byte data[30];
    byte data2[20];
    int i=0;
    uint8_t m_RX;
    uint8_t m_TX;
    int m_Debug;
};

#endif

