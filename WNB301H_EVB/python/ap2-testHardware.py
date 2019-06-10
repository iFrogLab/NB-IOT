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

try:
    port="/dev/ttyAMA0"                    # Open named port  RPI
    port="COM1"                            # PC COM1 port
    port="/dev/cu.usbserial"               # MAC port
    with serial.Serial(port, 9600, timeout=1) as ser:
        print(ser.name)
        ser.write(b"AT+CGPADDR"+b"\r\n")
        print(ser.readline())                # read up to ten bytes (timeout)
        print(str(ser.readline(), encoding="utf-8"))  # read up to ten bytes (timeout)
        print(str(ser.readline(), encoding="utf-8"))  # read up to ten bytes (timeout)
        ser.close()                                 # close port

except SerialException:
    print("SerialException")


