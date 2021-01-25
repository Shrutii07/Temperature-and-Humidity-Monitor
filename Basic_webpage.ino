#include "WiFi.h"
#include "DHT.h"

#define DHTPIN 4     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

const char* ssid = "Shruti_ESP";
const char* pass = "Shubh@123";

WiFiServer server(80);

DHT dht(DHTPIN, DHTTYPE);
String output = "";
String output1 = "";
String html = "<!DOCTYPE html> \
<html> \
<head> <meta http-equiv=\"refresh\" content=\"1\"> \
</head> \
<body> \
Temperature(in Celsius): ";

String html2 = "</body> \
</html> ";

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, pass);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  server.begin();
  dht.begin();
}

void loop() {

  float h = dht.readHumidity();     //Read Humidity
  float t = dht.readTemperature();  // Read temperature as Celsius
  float f = dht.readTemperature(true);   // Read temperature as Fahrenheit (isFahrenheit = true)
  
  WiFiClient client = server.available();
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;}
  float hif = dht.computeHeatIndex(f, h);   // Compute heat index in Fahrenheit 
  float hic = dht.computeHeatIndex(t, h, false);  // Compute heat index in Celsius (isFahreheit = false)
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("C "));
  Serial.print(f);
  Serial.print(F("F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("C "));
  Serial.print(hif);
  Serial.println(F("F"));
  output = String(t) + "<br>";
  output1 = String(h) + "<br>";
  client.print(html + output + html2);  
  client.print("Humidity(in %): " + output1 + html2);
  delay(1500);
  }
