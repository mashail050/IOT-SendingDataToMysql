/*We're using Ethernet shield*/
#include "DHT.h"
#include <SPI.h>
#include <Ethernet.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //Setting MAC Address of ethernet shield

#define DHTPIN 2

#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);


float humidityValue;
float temperatureValue;


char server[] = "192.168.68.111";/*This is my local ip address */
IPAddress ip(192,168,68,177); 
EthernetClient client; 

/* Setup for Ethernet and RFID */

void setup() {
  Serial.begin(9600);
  dht.begin();
  if (Ethernet.begin(mac) == 0) {
  Serial.println("Failed to configure Ethernet using DHCP");
  Ethernet.begin(mac, ip);
  }
  delay(1000);
}

/* Infinite Loop */
void loop(){
  humidityValue = dht.readHumidity();
  temperatureValue = dht.readTemperature(); 
  Sending_To_phpmyadmindatabase(); 
  delay(30000); // interval
}


  void Sending_To_phpmyadmindatabase()  
 {
   if (client.connect(server, 80)) {
    Serial.println("connected");
    /* Make a HTTP request:*/
    Serial.print("GET /Task4IoT/index.php?humidity=");
    client.print("GET /Task4IoT/index.php?humidity=");    
    Serial.println(humidityValue);
    client.print(humidityValue);
    client.print("&temperature=");
    Serial.println("&temperature=");
    client.print(temperatureValue);
    Serial.println(temperatureValue);
    client.print(" ");      
    client.print("HTTP/1.1");
    client.println();
    client.println("Host: 192.168.68.111");
    client.println("Connection: close");
    client.println();
  } else {
    /*if you didn't get a connection to the server: */
    Serial.println("connection failed");
  }
 }
