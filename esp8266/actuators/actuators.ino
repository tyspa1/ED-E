/*
ESP8266 Actuator Unit
copyright (c) 2015 Tyler Spadgenske

Change the DEVICE_ID to the name of your device assigned on ED-E
Change the HOST to the IP address of ED-E (run ifconfig or check the settings menu on the OLED)
*/
 
#include <ESP8266WiFi.h>

char ssid[] = "spadgenske"; //  your network SSID (name) 
char pass[] = "68mustang";    // your network password (use for WPA, or use as key for WEP)
#define HOST "192.168.0.105"
#define PORT 888

int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

boolean alreadyConnected = false; // whether or not the client was connected previously

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  
  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) { 
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  } 
  // you're connected now, so print out the status:
  printWifiStatus();
 }


void loop() {
  // wait for a new client:
  // Attempt a connection with base unit
   WiFiClient client;
   if (!client.connect(HOST, PORT)) {
     Serial.println("connection failed");
     return;
  }


  // when the client sends the first byte, say hello:
  if (client) {
    if (!alreadyConnected) {
      // clead out the input buffer:
      client.flush();    
      Serial.println("We have a new client");
      client.println("Hello, client!"); 
      alreadyConnected = true;
    } 

    if (client.available() > 0) {
      // read the bytes incoming from the client:
      char thisChar = client.read();
      // echo the bytes back to the client:
      // echo the bytes to the server as well:
      Serial.write(thisChar);
    }
  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
