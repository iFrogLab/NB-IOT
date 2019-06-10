# www.ifroglab.com
# -*- coding: utf8 -*-
# coding=UTF-8
# * iFrogLab IL-LORA1272  www.ifroglab.com
# *
# * 功能,             USB to TTL , IFROGLAB LORA 
# * 電源VDD,          3.3V       ,Pin 3         
# * 接地GND,          GND        ,Pin 1        
# * 接收反應Host_IRQ,  null       , Pin 2        
# * UART,             RX         ,UART_RX  Pin 7 
# * UART,             TX         ,UART_TX  Pin 8 


# python ap12-SendReceive-data.py -u /dev/tty.usbserial-A700eGFx -r 115200 -a T  -s a1,2,3,4,5 -b /dev/tty.ttyAMA0 -m 9600
# python ap12-SendReceive-data.py -u /dev/tty.wchusbserial1410 -r 115200 -a R

import serial
import platform

from serial import SerialException
import time
import sys
import glob



#import sys, getopt
#import time
#import numpy
#import RPi.GPIO as GPIO ## Import GPIO library

class WNB301H:
    def sendToEVB(self,cmd, port, rate=9600, timeout=1,lines=1):
        try:
            with serial.Serial(port, rate, timeout=timeout) as ser:
                #print(ser.name)
                # str to bytes
                s1 = bytes(cmd, encoding="utf8")
                ser.write(s1 + b"\r\n")
                strall="";
                for x in range(lines):\
                    strall=strall+str(ser.readline(), encoding="utf-8")# read up to ten bytes (timeout)
                if(self.debug==1):
                    print(strall)                                      # read up to ten bytes (timeout)
                ser.close()  # close port
                return strall
        except SerialException:
            print("SerialException")

    def __init__(self,port, rate=9600, timeout=1):
        self.debug=0
        self.port=port
        self.rate=rate
        self.timeout=timeout
        self.sendToEVB("AT+NSOCL=0",self.port, self.rate, timeout=self.timeout,lines=2)
        self.sendToEVB("AT+NSOCL=1",self.port, self.rate, timeout=self.timeout,lines=2)
        self.sendToEVB("AT+CGPADDR",self.port, self.rate, timeout=self.timeout,lines=3)



    def sendStringToTelcomUDP(self,SendStr,PublicIPAddress,ServerPort):
        # sendStringToTelcom("hello","54.180.152.89",20001)
        self.sendToEVB("AT+CGDCONT=1,\"IP\",\"nbiot\"",self.port, self.rate, timeout=self.timeout,lines=2)
        self.sendToEVB("AT+CGDCONT?",self.port, self.rate, timeout=self.timeout,lines=2)
        t1=self.sendToEVB("AT+NSOCR=DGRAM,17,56,1,\"AF_INET\"",self.port, self.rate, timeout=self.timeout,lines=4)
        key1 = t1[2:4]
        SendStrLen=len(SendStr)
        tStrHex=''.join([hex(ord(x))[2:] for x in SendStr])
        #t1 = self.sendToEVB("AT+NSOST=1,54.180.152.89,20001,6,4C4954454F4E", self.port, self.rate, 2, lines=5)
        t1 = self.sendToEVB("AT+NSOST=1,54.180.152.89,20001,"+str(SendStrLen)+","+tStrHex, self.port, self.rate, 2, lines=5)
        key2 = t1[2:4]
        #print(key2)
        if(len(t1)>3):
            self.TargetStrNextInt=0
            self.TargetStrHex=""
            self.TargetStr=""
            self.TargetStrLen=0
            while(True):
                t2 = self.sendToEVB("AT+NSORF=1,1024", self.port, self.rate, timeout=self.timeout,
                                    lines=2)
                NSORForignalStr=t2
                # 回傳：　1,54.180.152.89,20001,29,48656C6C6F2055445020436C69656E7420323031393035323331323232,0
                #找,　找文字　和　剩下的長度
                i=0
                lastIndex=0
                if (len(t2) > 3):
                    while(True):
                        t3 = t2.find(',')
                        if(t3<0):
                            break;
                        returnValue = t2[t3+1:]
                        t2=returnValue
                        if(self.debug==1):
                            print(returnValue)
                        if(i==1):
                            self.TargetIP=NSORForignalStr[lastIndex:lastIndex+t3]
                        elif(i==2):
                            self.Targetport=NSORForignalStr[lastIndex:lastIndex+t3]
                        elif(i==3):
                            self.TargetStrLen=NSORForignalStr[lastIndex:lastIndex+t3]
                        elif(i==4):
                            self.TargetStrHex=NSORForignalStr[lastIndex:lastIndex+t3]
                            self.TargetStr=self.TargetStr+bytes.fromhex(self.TargetStrHex).decode('utf-8')
                            self.TargetStrNext=NSORForignalStr[lastIndex+t3+1:]
                            self.TargetStrNext=self.TargetStrNext.replace("\r\n","")
                            self.TargetStrNextInt=int(self.TargetStrNext)
                        lastIndex=lastIndex+t3+1
                        i=i+1
                if(self.TargetStrNextInt<=0):
                    break

        self.sendToEVB("AT+NSOCL="+key1, self.port, self.rate, timeout=self.timeout, lines=2)
        return self.TargetStr;




class LoRaNBIOT:
    def __init__(self):
        #self.name = name
        #self.number = number
        #self.balance = balance
        self.a1=1
    
    def deposit(self, amount):
        if amount <= 0:
            raise ValueError('amount must be positive')
        self.balance += amount
    
    def withdraw(self, amount):
        if amount > self.balance:
            raise RuntimeError('balance not enough')
        self.balance -= amount
    
    def __str__(self):
        return 'Account({0}, {1}, {2})'.format(self.name, self.number, self.balance)

    """  
    def WNB301H(self,port, rate=9600, timeout=1):
        self.port=port
        self.rate=rate
        self.timeout=timeout
        try:
            with serial.Serial(self.port, self.rate, timeout=self.timeout) as ser:
                print(ser.name)
                ser.write(b"AT+CGPADDR" + b"\r\n")
                print(ser.readline())  # read up to ten bytes (timeout)
                print(str(ser.readline(), encoding="utf-8"))  # read up to ten bytes (timeout)
                print(str(ser.readline(), encoding="utf-8"))  # read up to ten bytes (timeout)
                ser.close()  # close port
        except SerialException:
            print("SerialException")

    """
    # 計算CRC 檢查碼
    def Fun_CRC(self,data):
       crc=0
       for i in data:
         crc=crc^i
       return crc

    def serial_ports(self):
      """ Lists serial port names

        :raises EnvironmentError:
            On unsupported or unknown platforms
        :returns:
            A list of the serial ports available on the system
      """
      if sys.platform.startswith('win'):
        ports = ['COM%s' % (i + 1) for i in range(256)]
      elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
        # this excludes your current terminal "/dev/tty"
        ports = glob.glob('/dev/tty[A-Za-z]*')
      elif sys.platform.startswith('darwin'):
        ports = glob.glob('/dev/tty.*')
      else:
        raise EnvironmentError('Unsupported platform')
      result = []
      for port in ports:
        try:
            if port=="/dev/tty.Bluetooth-Incoming-Port":
              s=1
            else:
              s = serial.Serial(port)
              s.close()
              result.append(port)
        except (OSError, serial.SerialException):
            pass
      return result

    # open Serial Port   
    def FunLora_init(self):
      try:
        self.portPath=self.Fun_OS()
        print(self.portPath)
        self.ser = serial.Serial(self.portPath, 115200, timeout=3)    
        return self.ser
      except SerialException:
        print("port already open")

    # open Serial Port  by  name , like "/dev/xxx"
    def FunLora_initByName(self,i_portPath):
      try:
        #self.portPath=self.Fun_OS()
        print(i_portPath)
        self.ser = serial.Serial(i_portPath, 115200, timeout=3)    
        return self.ser
      except SerialException:
        print("port already open")

    #  get all USB Uart Port.
    def Fun_OS(self):
      OSVersion=platform.system()
      self.port_path="/dev/cu.usbserial"
      print(OSVersion)
      if OSVersion=="Darwin":              #MAC Port
         #self.port_path="/dev/cu.usbserial"
         #self.port_path="/dev/cu.usbmodem1421"
         self.port_path="/dev/cu.usbserial-A700eGFx"
      elif OSVersion=="Linux":            #Linux Port
         self.port_path="/dev/ttyUSB0"
      self.ports=self.serial_ports()
      print(self.ports)
      t1=len(self.ports)
      print("This device has %d Serial devices"%t1)
      for self.port_path in self.ports:
        #if t1>0:
        #self.port_path=self.ports[0]
        #self.ser=self.port_path
        # 判對是否是LoRa 接在上面
        print("1")
        self.ser=self.FunLora_initByName(self.port_path)
        print(self.ser)
        data=self.FunLora_0_GetChipID()
        print(data)
        if(len(data)>1):
          return self.port_path  
      return self.port_path

    # 送byte 到　Chip 上
    def FunLora_ChipSendByte(self,array1):    
      try:
        print(array1)
        self.ser.write(serial.to_bytes(array1))
        time.sleep(0.04)
        bytesToRead = self.ser.inWaiting()
        data = self.ser.read(bytesToRead)
        print(data.encode('hex'))
      except (OSError, serial.SerialException):
        pass
      return data

    def Fun_ser_Write(self,array1):
      try:
         self.ser.write(serial.to_bytes(array1))
      except SerialException:
        print("Fun_ser_Write error")


    # close Serial Port
    def FunLora_close(self):
      try:
        self.ser.close()
      except SerialException:
        print("port already open")
    




    def FunLora_0_GetChipID(self):
       array1=[0x80,0x00,0x00,0]
       array1[3]=self.Fun_CRC(array1)
       print(array1)
       self.Fun_ser_Write(array1)
       time.sleep(0.01)
       bytesToRead = self.ser.inWaiting()
       data = self.ser.read(bytesToRead)
       print(data.encode('hex'))
       return data

    # 重置 & 初始化
    def FunLora_1_Init(self):
       array1=[0xc1,0x01,0x00,0]
       array1[3]=self.Fun_CRC(array1)
       data=self.FunLora_ChipSendByte(array1)
       return data

    # 讀取設定狀態
    def FunLora_2_ReadSetup(self):
       array1=[0xc1,0x02,0x00,0]
       array1[3]=self.Fun_CRC(array1)
       data=self.FunLora_ChipSendByte(array1)
       return data

    # 設定讀取和頻段
    def FunLora_3_RX(self):
       array1=[0xC1,3,5,3,1,0x65,0x6C,0xf,0]
       array1[8]=self.Fun_CRC(array1)
       data=self.FunLora_ChipSendByte(array1)
       return data

    # 讀取LoRa 傳過來的資料
    def FunLora_6_read(self):
       array1=[0xC1,0x6,0x0,0]
       array1[3]=self.Fun_CRC(array1)
       data=self.FunLora_ChipSendByte(array1)
       return data

    # 設定寫入和頻段
    def FunLora_3_TX(self):
       array1=[0xC1,3,5,2,1,0x65,0x6C,0xf,0]
       array1[8]=self.Fun_CRC(array1)
       data=self.FunLora_ChipSendByte(array1)
       return data

    # 寫入測試
    def FunLora_5_write_test(self):
       array1=[0xC1,0x5,0x5,0x61,0x62,0x63,0x64,0x65,0]
       array1[8]=self.Fun_CRC(array1)
       data=self.FunLora_ChipSendByte(array1)
       return data

    def FunLora_5_write16bytesArray(self,data_array):
        #self.ser.write(serial.to_bytes([0xc1,0x03,0x05,0x02,0xe4,0xc0,0x00,0x03]))
        #data = ser.read(5)
        #print data.encode('hex')
        TX_Data=data_array
        ##[0x01,0x02,0x03]
        CMD_Data=[0xc1,0x05]
        CMD_Data.append(len(TX_Data))
        for i3 in data_array:
           #CMD_Data.append(int(i3, 16))
           CMD_Data.append(ord(i3))
        ##ser.write(serial.to_bytes([0xc1,0x05,0x03,0x01,0x02,0x03]))
        CRC=self.Fun_CRC(CMD_Data)
        CMD_Data.append(CRC)
        print(CMD_Data)
        data=self.FunLora_ChipSendByte(CMD_Data)
        return data

        ##ser.write(serial.to_bytes(TX_Data))
        #ser.write(CMD_Data)
        #
        #print ("Send:")
        ##print ','.join(format(x, '02x') for x in serial.to_bytes(TX_Data))
        #print ','.join([i2 for i2 in TX_Data])
        #data = ser.read(5)
        #print data.encode('hex')

    # 讀取LoRa 傳過來的資料
    def FunLora_7_readCounter(self):
       array1=[0xC1,0x7,0x0,0]
       array1[3]=self.Fun_CRC(array1)
       data=self.FunLora_ChipSendByte(array1)
       return data








