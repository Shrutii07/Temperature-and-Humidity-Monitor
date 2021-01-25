#include "WiFi.h"
#include "DHT.h"

#define DHTPIN 4     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

const char* ssid = "Shruti_ESP";
const char* pass = "Shubh@123";

WiFiServer server(80);
String output = "";
String output1 ="";

DHT dht(DHTPIN, DHTTYPE);

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
  WiFiClient client = server.available();
  if(client)
  {
    Serial.println("Web Client connected ");
    String request = client.readStringUntil('\r'); 
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println("Connection: close");
    client.println();
    client.println("<!DOCTYPE html><html>");
    client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
    client.println("<link rel=\"icon\" href=\"data:,\">");

    //Adding styles to a web page to look more professional
    client.println("<style>body { text-align: center; font-family: \"Arial\", Arial;}");
    client.println("table { border-collapse: collapse; width:40%; margin-left:auto; margin-right:auto;border-spacing: 2px;background-color: white;border: 4px solid green; }");
    client.println("th { padding: 20px; background-color: #008000; color: white; }");
    client.println("tr { border: 5px solid green; padding: 2px; }");
    client.println("tr:hover { background-color:yellow; }");
    client.println("td { border:4px; padding: 12px; }");
    client.println(".sensor { color:white; font-weight: bold; background-color: #bcbcbc; padding: 1px; }");

    client.println("</style></head><body><h1>ESP32 Web Server </h1>");
    client.println("<h2>DHT11/DHT22</h2>");
    client.println("<table><tr><th>MEASUREMENT</th><th>VALUE</th></tr>");
    client.println("<tr><td>Temp. Celsius</td><td><span class=\"sensor\">");
    client.println(dht.readTemperature());
    client.println(" *C</span></td></tr>"); 
    client.println("<tr><td>Temp. Fahrenheit</td><td><span class=\"sensor\">");
    client.println(1.8 * dht.readTemperature() + 32);
    client.println(" *F</span></td></tr>"); 
    client.println("<tr><td>Humidity</td><td><span class=\"sensor\">");
    client.println(dht.readHumidity());
    client.println(" %</span></td></tr>"); 
    client.println("</body></html>"); 
    client.stop();
    client.println();
    Serial.println("Client disconnected.");
    Serial.println("");
}
delay(1500);
}
