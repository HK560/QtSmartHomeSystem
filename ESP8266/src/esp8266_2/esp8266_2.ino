#include <ESP8266WiFi.h> //ESP8266基本网络功能
#include <U8g2lib.h>
#include <WiFiUdp.h> //提供UDP相关功能
#include <Wire.h>
// #include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Servo.h>
// #include <DNSServer.h>
#include "DHT.h"
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <string>
#define DHTTYPE DHT11
#define MAX_SRV_CLIENTS 3
// #include"u8g2_wqy.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

String devId = "D0002"; // idname
const char *apName = "ESP8266_AP_D0002";
const char *ssid = "elbadaernU";   // 网络名称 修改为你的wifi名字
const char *password = "12345678"; // 网络密码 修改为你的wifi密码
Servo myservo;
byte revByte;
WiFiUDP Udp;
WiFiClient client;                  // 创建一个tcp client连接
unsigned int localUdpPort = 5600;   // 本地端口号
unsigned int TcpPort = 5656;        // 监听端口号
unsigned int remoteUdpPort = 56700; // 本地端口号

// const char *tcpSendMsg;
int getRemoteHost = 0;

char incomingPacket[10000]; // 接收缓冲区
IPAddress remoteHost;
String ipStr;
WiFiServer server(TcpPort);
WiFiClient serverClients[MAX_SRV_CLIENTS];

// func list
#define FUNC_NUM 3
#define FUNC_NUM_USE 2
String funcName[FUNC_NUM] = {"电灯", "亮度值", "显示内容"};
String funcDesc[FUNC_NUM] = {"控制电灯的开关", "控制电灯的亮度",
                             "设置设备显示的文本"};
String funcType[FUNC_NUM] = {"F_LIGHT", "F_VOLUME", "F_NULL"};
String funcValueType[FUNC_NUM] = {"0", "1", "2"};
String funcValue[FUNC_NUM] = {"0", "1", "NULL"};

#define RV_NUM 2
#define RV_NUM_USE 0
String rvName[RV_NUM] = {"温度", "湿度"};
String rvDesc[RV_NUM] = {"当前检测到温度", "当前检测到湿度"};
String rvType[RV_NUM] = {"RV_TEMP", "RV_VALUE"};
String rvValueType[FUNC_NUM] = {"2", "2"};
String rvValue[FUNC_NUM] = {"0", "0"};
bool lightValue = false;
int volumeValue = 0;
String textValue = "NULL";

String TcpSendData = "";

String title = "elbadaernU";            // 可自定义，限制长度为15
String subtitle = "Waiting for signal"; // 可自定义，限制长度为15

// DHT Sensor
uint8_t DHTPin = 2;

// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);

float Temperature;
float Humidity;

void welcomeTextShow() {

  char titleChar[30], subtitleChar[30];
  String ssidname =WiFi.SSID();
  ssidname.toCharArray(titleChar, 30);
  subtitle.toCharArray(subtitleChar, 30);
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_wqy13_t_gb2312a);
  char nowip[20];
  ipStr = WiFi.localIP().toString();
  ipStr.toCharArray(nowip, 20);
  u8g2.drawStr((128 - (u8g2.getUTF8Width(titleChar))) / 2, 20,titleChar);
  u8g2.drawStr((128 - (u8g2.getUTF8Width(subtitleChar))) / 2, 40, subtitleChar);
  u8g2.drawStr((128 - (u8g2.getUTF8Width(nowip))) / 2, 55, nowip);
  u8g2.sendBuffer();
}

void showStr(String str) {
  char strChar[30];
  funcValue[2].toCharArray(strChar, 30);
  char volume[5];
  funcValue[1].toCharArray(volume, 5);
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_missingplanet_tr);
  u8g2.drawStr((128 - (u8g2.getUTF8Width(strChar))) / 2, 40, strChar);
  u8g2.drawStr((128 - (u8g2.getUTF8Width(volume))) / 2, 55, volume);
  u8g2.sendBuffer();
}

void showStr2(String str) {
  char strChar[30];
  str.toCharArray(strChar, 30);
  // char volume[5];
  // funcValue[1].toCharArray(volume, 5);
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_missingplanet_tr);
  u8g2.drawStr((128 - (u8g2.getUTF8Width(strChar))) / 2, 40, strChar);
  // u8g2.drawStr((128 - (u8g2.getUTF8Width(volume))) / 2, 55, volume);
  u8g2.sendBuffer();
}


void boot() { // 没有收到数据时候执行的函数

  char nowip[20];
  ipStr = WiFi.localIP().toString();
  ipStr.toCharArray(nowip, 20);
  Serial.println(ipStr);

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_missingplanet_tr);

  // 设置字体库可以查询u8g2库wiki：https://github.com/olikraus/u8g2/wiki/fntlistall

  welcomeTextShow();

  Udp.begin(localUdpPort);
  Serial.printf("UDP: Now listening at IP %s, UDP port %d\n",
                WiFi.localIP().toString().c_str(), localUdpPort);

  // 启动TCP server服务器
  server.begin();
  server.setNoDelay(true);
  Serial.printf("TCP: Server started, Port: %d\n", TcpPort);
}

void Tcplisten() {
  uint8_t i;
  if (server.hasClient()) {
    Serial.println("hasClient"); // 判断是否有新的client请求进来
    for (i = 0; i < MAX_SRV_CLIENTS; i++) {

      // 释放旧无效或者断开的client
      if (!serverClients[i] || !serverClients[i].connected()) {
        if (!serverClients[i]) {
          // serverClients[i]    判断指定序号的客户端是否有效
          serverClients[i].stop(); // 停止指定客户端的连接
        }

        serverClients[i] = server.available(); // 分配最新的client
        Serial.print("1个新的客户端: ");
        Serial.println(i);
        break; // 跳出一层for循环
      }
    }

    // 当达到最大连接数 无法释放无效的client，需要拒绝连接
    if (i == MAX_SRV_CLIENTS) {
      WiFiClient client = server.available();
      client.stop();
      Serial.println("连接被拒绝 ");
    }
  }

  for (i = 0; i < MAX_SRV_CLIENTS; i++) {
    if (serverClients[i] && serverClients[i].connected()) {
      if (serverClients[i].available()) {
        Serial.printf("Going to read");
        String req = serverClients[i].readStringUntil('\r');
        Serial.printf("GET data from TCP client:%s\n", req.c_str());
        while (serverClients[i].available()) {
          serverClients[i].read();
        }

        HandleClientMsg(i, req);
        TcpSend(i, TcpSendData);
        TcpSendData = "";
      }
    }
  }
}

//
void funcHandle(int tcpid, String type, String func, String value) {

  if (type.equals(String("FN")) || type.equals(String("GET"))) {

    for (int i = 0; i < FUNC_NUM_USE; ++i) {
      TcpSendData += '#';
      TcpSendData += funcType[i];
      TcpSendData += '*';
      TcpSendData += funcName[i];
      TcpSendData += '<';
      TcpSendData += funcDesc[i];
      TcpSendData += '/';
      TcpSendData += funcValueType[i];
      TcpSendData += '/';
      TcpSendData += funcValue[i];
    }
    goto END;
  }

  if (type.equals(String("SET"))) {
    int length = value.length();
    String nname = "";
    String ttype = "";
    String vvalue = "";
    int c = 0;
    while (value[c] != '/' && c < length) {
      nname += value[c++];
    }
    while (value[++c] != '/' && c < length) {
      ttype += value[c];
    }
    while (value[++c] != '/' && c < length) {
      vvalue += value[c];
    }
    Serial.printf("funcName : %s, valueType : %s, value : %s\n", nname.c_str(),
                  ttype.c_str(), vvalue.c_str());

    for (int i = 0; i < FUNC_NUM_USE; ++i) {
      if (nname.equals(String(funcName[i])) &&
          ttype.equals(String(funcValueType[i]))) {
        funcValue[i] = vvalue;
        Serial.printf("Already set value : %s\n", funcName[i].c_str());
        break;
      }
    }

    TcpSendData += "#OK*0";
    goto END;
  }

END:
  return;
}
void HandleClientMsg(int tcpId, String req) {
  int strSize = req.length();
  int i = 0;
  String type = "";
  const char *data = req.c_str();
  Serial.printf("Start handle client msg (%s), size is %d\n", data, strSize);
  if (data[i++] == '!') {
    // 读类型
    while (data[i] != '#' && i < strSize) {
      type += (char)data[i++];
    }
    Serial.printf("type is %s\n", type.c_str());

    TcpSendData = "!";
    TcpSendData += type;
    TcpSendData += 'A';

    // 单独读一个func
    while (data[i++] != '?' && i < strSize) {
      String func = "";
      String value = "";
      while (data[i] != '*' && i < strSize) {
        func += (char)data[i++];
      }
      Serial.printf("func is %s\n", func.c_str());
      i++;
      while (req[i] != '#' && req[i] != '?' && req[i] != 0 && i < strSize) {
        value += (char)req[i++];
      }
      Serial.printf("value is %s\n", value.c_str());

      funcHandle(tcpId, type, func, value);
    }
    TcpSendData += '?';
    updateFunc();
    Serial.printf("msg handle end");
  }
}

void updateFunc() {
  switchLight();
  showStr(funcValue[2]);
}

// for func void
void switchLight() {
  String enable = "1";
  // String disable = "0";
  if (enable.equals(String(funcValue[0]))) {
    Serial.printf("open light\n");
    digitalWrite(LED_BUILTIN, LOW);

    myservo.write(180);
    delay(1000);
  } else {
    Serial.printf("disable light\n");
    digitalWrite(LED_BUILTIN, HIGH);

    myservo.write(0);
    delay(1000);
  }
}

void TcpSend(int i, String req) {
  Serial.printf("Going to send TCP:%s\n", req.c_str());
  serverClients[i].print(req.c_str());
}

/////////////////////////////////////////////////////
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  myservo.attach(14);
  myservo.write(0);   // 电机转动到0度
  delay(1000);        // 等待1秒钟
  myservo.write(180); // 电机转动到90度
  delay(1000);        // 等待1秒钟
  myservo.write(0);   // 电机转动到0度
  delay(1000);        // 等待1秒钟
  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.clearBuffer();
  Serial.begin(115200);
  Serial.println("Ready");

  pinMode(DHTPin, INPUT);
  dht.begin();

  Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity();       // Gets the values of the humidity
  Serial.println((float)Temperature, 2);
  Serial.println((float)Humidity, 2);
  WiFiManager wifiManager;
  showStr2("Waiting for AP Config");
  // wifiManager.resetSettings();
  wifiManager.autoConnect(apName);

  Serial.println("");
  Serial.print("ESP8266 Connected to ");
  Serial.println(WiFi.SSID()); // WiFi名称
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP()); // IP
  boot();
}

void loop() {
  if (1) {
    getUdp();
  }
  Tcplisten();
}
//////////////////////////////////////////////////////////////////////
void getUdp() {
  int packetSize = Udp.parsePacket(); // 获取当前队首数据包长度
  char firstChar[2];
  firstChar[1] = 0;
  String type = "";

  if (packetSize) // 有数据可用
  {
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize,
                  Udp.remoteIP().toString().c_str(), Udp.remotePort());

    revByte = Udp.read(); // 读取数据到incomingPacket
    packetSize--;
    firstChar[0] = revByte;

    Serial.printf("UDP header contents: %s\n", firstChar);
    if (revByte == '!') {
      while (packetSize > 0 && revByte != '#') {
        revByte = Udp.read();
        packetSize--;
        if (revByte != '#') {
          type += (char)revByte;
        }
      }
      Serial.println(type); // 如果需要显示其他的信息，去上位机输出里查名称

      if (type.compareTo(String("DC")) == 0) {
        Serial.println("UDP:IS DC");
        remoteHost = Udp.remoteIP();
        getRemoteHost = 1;
        Temperature =
            dht.readTemperature(); // Gets the values of the temperature
        Humidity = dht.readHumidity();
        char tempbuffer1[10];
        char tempbuffer2[10];
        dtostrf(Temperature, 6, 2, tempbuffer1);
        dtostrf(Humidity, 6, 2, tempbuffer2);
        rvValue[0] = String(tempbuffer1);
        rvValue[1] = String(tempbuffer2);
        Udp.beginPacket(Udp.remoteIP(), remoteUdpPort); // 配置远端ip地址和端口
        String data = "!DCA";
        data += "#IP";
        data += '*';
        data += ipStr;
        data += "#ID";
        data += '*';
        data += devId;
        //
        for (int i = 0; i < RV_NUM_USE; ++i) {
          data += '#';
          data += rvType[i];
          data += '*';
          data += rvName[i];
          data += '<';
          data += rvDesc[i];
          data += '/';
          data += rvValueType[i];
          data += '/';
          data += rvValue[i];
        }

        data += '?';
        Serial.printf("UDP going to send: %s\t%s:%d\n", data.c_str(),
                      Udp.remoteIP().toString().c_str(), remoteUdpPort);
        Udp.write(data.c_str()); // 把数据写入发送缓冲区
        Udp.endPacket();         // 发送数据
      }
    }
  }
}
