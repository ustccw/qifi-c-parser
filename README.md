# A lightweight QiFi parser in C
[QiFi](https://qifi.org/) can be used to carry WiFi information by QR code, the QR code image will be secure than plaintext transmission.  
QiFi parser will work for you QR scanner, convert the scan result into multipart, extract WiFi information for next easy connection.

# About QiFi parser
A QR scanner result, generally, is a Wi-Fi Network configuration format, described [here](https://github.com/zxing/zxing/wiki/Barcode-Contents#wi-fi-network-config-android-ios-11).  

For example:
```
WIFI:T:WPA;S:mynetwork;P:mypass;;
```

**QiFi parser will parse string and split into SSID, password, authentication type and hidden.**

# COMPILE & TEST
```
make test
```
