#include <ESP8266WiFi.h>

IPAddress ip(192, 168, 0, 80);            // IP address of the server
IPAddress gateway(192,168,0,1);           // gateway of your network
IPAddress subnet(255,255,255,0);          // subnet mask of your network

//wifi credentials 
const char *ssid = "ESP8266";       // ssid of wifi you want 
const char *password = "ESP8266Test"; // password if reqd 
WiFiServer server(80);               // initialising your server      

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  //set-up the custom IP address
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(ip, ip, subnet);   // subnet FF FF FF 00  
  
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);  // generating hotspot connnection 

  IPAddress myIP = WiFi.softAPIP(); 
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();                         // starts the server

}

void loop() {
  // put your main code here, to run repeatedly:
WiFiClient client = server.available();     // checks if any client is available
  if (client) {
    if (client.connected()) {
      Serial.println(".");
      String request = client.readStringUntil('\r');    // receives the message from the client
      /*
      code here for your future preference 
      */
      Serial.print("From client: "); Serial.println(request);
      client.flush();
      client.println("Hi client! No, I am listening.\r"); // sends the answer to the client
    }
    client.stop();                // terminates the connection with the client
  }
}
