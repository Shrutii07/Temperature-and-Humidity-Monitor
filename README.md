# Temperature and Humidity Monitor

To monitor real time temperature & humidity values on a webserver using DHT11 sensor & ESP32.

## DHT 11
The DHT11 is a basic, ultra low-cost digital temperature and humidity sensor. It uses a capacitive humidity sensor and a thermistor to measure the surrounding air, and spits out a digital signal on the data pin. The only real downside of this sensor is you can only get new data from it once every 2 seconds, so when using our library, sensor readings can be up to 2 seconds old. Compared to the DHT22, this sensor is less precise, less accurate and works in a smaller range of temperature/humidity, but its smaller and less expensive.

## Connections
Install "DHT Sensor" Library for DHT Sensor. 

Arduino IDE > Sketch > Include Library > Manage Libraries > DHT SENSOR.

DHT11 sensor normally comes with only three pins: VCC, GND and the Data line. Data Line is connected to GPIO4 (D4).

## [Basic Webpage]()
