int sensor_pin = A0;
int output_value ;

#include <ESP8266WiFi.h>

// Wi-Fi Settings
const char* ssid = "redmi"; // your wireless network name (SSID)
const char* password = "12345678"; // your Wi-Fi network password

WiFiClient client;

// ThingSpeak Settings
const int channelID = 408082;
String writeAPIKey = "49BK77B70E625CNK"; // write API key for your ThingSpeak Channel
const char* server = "api.thingspeak.com";
const int postingInterval = 20 * 1000; // post data every 20 seconds


void setup() {
  Serial.begin(9600);
 
  delay(500);//Delay to let system boot

  Serial.println("Reading From the Sensor ...");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  }
  
}

void loop() {

  output_value= analogRead(sensor_pin);
   output_value = map(output_value,1023,386,0,100);
   Serial.print("Mositure : ");
   Serial.print(output_value);
   Serial.println("%");

  if (client.connect(server, 80)) {
   
    long rssi = WiFi.RSSI();                // Measure Signal Strength (RSSI) of Wi-Fi connection

    Serial.print("RSSI = ");
    Serial.println(rssi); 

   Serial.print("Mositure : ");
   Serial.print(output_value);
   Serial.println("%");
      

    // Construct API request body
    String body = "field4=";
           body += String(output_value);       //soil moisture variable here
          
    delay(2000);

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + writeAPIKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(body.length());
    client.print("\n\n");
    client.print(body);
    client.print("\n\n");

  }
  client.stop();

  // wait and then post again
  delay(postingInterval);
}
