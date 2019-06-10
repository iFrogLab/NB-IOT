# coding=UTF-8
# *   iFrogLab_NBIOT.h - library for ifroglab NB-IOT - implementation
# *   Copyright (c) 2019 Powen Ko, iFroglab.com All right reserved.
# *   www.ifroglab.com
# *
# *
# * for PC:
# *   just connect to USB
# *
# *
# *
# * for Raspberry Pi:
# *   Function,  USB to TTL ,       IFROGLAB LORA
# *   GND,              GND ,       Pin 6
# *   UART,              RX ,       UART_RX  Pin 2
# *   UART,              TX ,       UART_TX  Pin 4
# *
# *
# * pip install pyserial
# * pip install pyserial=3.4
#
# List all ports
# $ python3 -m serial.tools.list_ports

import serial
from serial import Serial
import ifroglabNBIOT

port="/dev/ttyAMA0"                    # Open named port  RPI
port="COM1"                            # PC COM1 port
port="/dev/cu.usbserial"               # MAC port


NBIOT = ifroglabNBIOT.WNB301H("/dev/cu.usbserial", 9600, timeout=0.2)
t1=NBIOT.sendStringToTelcomUDP("abc","54.180.152.89",20001)
print("-------------")
print(t1)



