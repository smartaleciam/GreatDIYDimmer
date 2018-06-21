/*
 *  This sketch demonstrates how to set up a simple HTTP-like server.
 *  The server will set a GPIO pin depending on the request
 *    http://server_ip/gpio/0 will set the GPIO2 low,
 *    http://server_ip/gpio/1 will set the GPIO2 high
 *  server_ip is the IP address of the ESP8266 module, will be 
 *  printed to Serial when the module is connected.
 */

#include <ESP8266WiFi.h>

const char* ssid = "FBI_Honeypot";
const char* password = "69meBitch";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  int tick=0;
  Serial.begin(115200);
  delay(10);

  // prepare GPIO2
  pinMode(2, OUTPUT);
  digitalWrite(2, 0);
  
  // Connect to WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.print(ssid);
  //Serial.println();
//WiFi.mode(WIFI_AP);
//WiFi.softAP("Light_Dimmer", "");  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) { tick=tick+1; delay(500); Serial.print("."); if(tick>=25){ Serial.println(" Failed"); Serial.println(); WiFi.mode(WIFI_AP); WiFi.softAP("Light_Dimmer", ""); Serial.println("Access Point Mode Started instead"); break; }; }
//  Serial.println("");
//  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
if(tick<=24) Serial.println(WiFi.localIP()); else Serial.println("192.168.4.1");
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();  if (!client) {    return;  }
  
  // Wait until the client sends some data
  //Serial.println("new client"); 
//  while(!client.available()){    delay(1);  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');  Serial.println(req); 
  client.flush();
  
  // Match the request
  int val, slider, sl_val;
  if (req.indexOf("/button=1") != -1)   {
//    sl_val=req.length();
      slider=req.substring(13-1).toInt();
      sl_val=req.substring(7+1).toInt(); 
    Serial.println(slider);
//    Serial.println(req.substring(13-1));
    Serial.println(" -= yes =- Button 1");
    }
  else
  if (req.indexOf("/button=2") != -1)    val = 1;
//else {      Serial.println("invalid request");    client.stop();    return;    }

  // Set GPIO2 according to the request
//  digitalWrite(8, val);
  
  client.flush();

  // Prepare the response
//String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
//  s += (val)?"high":"low";
//  s += "</html>\n";

  // Send the response to the client
//  client.print(s);
  client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
  delay(1);
//  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}

