/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com  
*********/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

MDNSResponder mdns;

// Replace with your network credentials
const char* ssid = "Yvens";
const char* password = "asd123456";

ESP8266WebServer server(80);

String webPage = "";

int gpio0_pin = 0;
int gpio2_pin = 2;
int gpio4_pin = 4;

void setup(void){
  //webPage += "<h1>ESP8266 Web Server</h1><p>Socket #1 <a href=\"socket1On\"><input type=\"button\" value=\"OK\" style=\"width: 200px; height: 200px\"><p>Socket #1 <a href=\"socket1On\"><button>ON</button></a>&nbsp;<a href=\"socket1Off\"><button>OFF</button></a></p>";
  //webPage += "<p>Socket #2 <a href=\"socket2On\"><button>ON</button></a>&nbsp;<a href=\"socket2Off\"><button>OFF</button></a></p>";
  webPage +=  "<h1 style=\"font-size:60px\">Quadro de Luz IoT</h1>";
  
  webPage +=  "<p style=\"font-size:40px\">Luz Sala</br> <a href=\"socket1On\">";
  webPage +=  "<input type=\"button\" value=\"ON\" style=\"width: 200px; height: 200px\">";
  webPage +=  "</a>&nbsp;<a href=\"socket1Off\">";
  webPage +=  "<input type=\"button\" value=\"OFF\" style=\"width: 200px; height: 200px\"></a>";

  webPage +=  "<p style=\"font-size:40px\">Luz Garagem</br> <a href=\"socket2On\">";
  webPage +=  "<input type=\"button\" value=\"ON\" style=\"width: 200px; height: 200px\">";
  webPage +=  "</a>&nbsp;<a href=\"socket2Off\">";
  webPage +=  "<input type=\"button\" value=\"OFF\" style=\"width: 200px; height: 200px\"></a></p>";

  webPage +=  "<p style=\"font-size:40px\">Luz Quarto</br> <a href=\"socket3On\">";
  webPage +=  "<input type=\"button\" value=\"ON\" style=\"width: 200px; height: 200px\">";
  webPage +=  "</a>&nbsp;<a href=\"socket3Off\">";
  webPage +=  "<input type=\"button\" value=\"OFF\" style=\"width: 200px; height: 200px\"></a>";

  webPage +=  "<p style=\"font-size:40px\">Desligar Tudo</br> <a href=\"socket4Off\">";
  webPage +=  "<input type=\"button\" value=\"\" style=\"width: 400px; height: 200px\">";
  webPage +=  "</a>";
  
  
  // preparing GPIOs
  pinMode(gpio0_pin, OUTPUT);
  digitalWrite(gpio0_pin, LOW);
  pinMode(gpio2_pin, OUTPUT);
  digitalWrite(gpio2_pin, LOW);
  pinMode(gpio4_pin, OUTPUT);
  digitalWrite(gpio4_pin, LOW);
  
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
  
  server.on("/", [](){
    server.send(200, "text/html", webPage);
  });
  server.on("/socket1On", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio0_pin, HIGH);
    delay(1000);
  });
  server.on("/socket1Off", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio0_pin, LOW);
    delay(1000); 
  });
  server.on("/socket2On", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio2_pin, HIGH);
    delay(1000);
  });
  server.on("/socket2Off", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio2_pin, LOW);
    delay(1000); 
  });
  server.on("/socket3On", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio4_pin, HIGH);
    delay(1000);
  });
  server.on("/socket3Off", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio4_pin, LOW);
    delay(1000);
  });
  server.on("/socket4Off", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio4_pin, LOW);
    digitalWrite(gpio2_pin, LOW);
    digitalWrite(gpio0_pin, LOW);
    delay(1000);
  });
  
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void){
  server.handleClient();
} 
