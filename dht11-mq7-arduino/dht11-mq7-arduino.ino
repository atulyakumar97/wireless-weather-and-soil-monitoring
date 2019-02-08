#include <dht.h> 
#define dht_apin 16 
dht DHT;

#define RELAY 15
#define MQ7_ANALOG_IN_PIN 1
//#define MQ7_DIGITAL_IN_PIN 10
#define MQ7_HEATER_5_V_TIME_MILLIS 60000
#define MQ7_HEATER_1_4_V_TIME_MILLIS 90000
#define GAS_LEVEL_READING_PERIOD_MILLIS 1000
#define BUZZER 14
//int mq135sensorValue;   //MQ135
#define HEATING_LED 2
#define READING_LED 12


int globalgasLevel;

unsigned long startMillis;
unsigned long switchTimeMillis;
boolean heaterInHighPhase;


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

  pinMode(RELAY, OUTPUT);
  startMillis = millis();
  turnHeaterHigh();
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  }
  
}

void loop() {

  if (heaterInHighPhase) {
    // 5v phase of cycle. see if need to switch low yet
    if (millis() > switchTimeMillis) {
      Serial.println("Reading from sensors....");
      turnHeaterLow();
    }
    blinkHeating();
  }
  else {
    // 1.4v phase of cycle. see if need to switch high yet
    if(millis() > switchTimeMillis) {
      Serial.println("Heating the gas sensor....");
      turnHeaterHigh();
    }
  }
    blinkReading();
    if (globalgasLevel >= 100) {
      tone(BUZZER, 10000); // Send 1KHz sound signal...
    }
    else {
      noTone(BUZZER);     // Stop sound...
    }

  if (client.connect(server, 80)) {
   
    long rssi = WiFi.RSSI();                // Measure Signal Strength (RSSI) of Wi-Fi connection

    Serial.print("RSSI = ");
    Serial.println(rssi); 
    
    DHT.read11(dht_apin);
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    Serial.print("AQI =  ");
    Serial.println(globalgasLevel, DEC);    

    // Construct API request body
    String body = "field1=";
           body += String(rssi);                   //wifi signal strength
           body += "&field2=";
           body += String(DHT.humidity);           //humidity variable here
           body += "&field3=";
           body += String(DHT.temperature);         //temperature variable here
           body += "&field5=";
           body += String(globalgasLevel);        //MQ135 variable here
          
 
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


void turnHeaterHigh(){
  // 5v phase
  digitalWrite(RELAY, LOW);
  heaterInHighPhase = true;
  switchTimeMillis = millis() + MQ7_HEATER_5_V_TIME_MILLIS;
}

void turnHeaterLow(){
  // 1.4v phase
  digitalWrite(RELAY, HIGH);
  heaterInHighPhase = false;
  switchTimeMillis = millis() + MQ7_HEATER_1_4_V_TIME_MILLIS;
}

void readGasLevel(){

 
  unsigned int gasLevel = analogRead(MQ7_ANALOG_IN_PIN);
  unsigned int time = (millis() - startMillis) / 1000;

  if(!heaterInHighPhase)
  {
    gasLevel=0;
  }
  
  Serial.print(time);
  Serial.print(",");
  Serial.println(gasLevel);

 globalgasLevel=gasLevel;
}

void blinkHeating() {
  digitalWrite(HEATING_LED, HIGH);
  delay(100);
  digitalWrite(HEATING_LED, LOW);
  delay(100);
}

void blinkReading() {
  digitalWrite(READING_LED, HIGH);
  delay(GAS_LEVEL_READING_PERIOD_MILLIS / 2);
  digitalWrite(READING_LED, LOW);
  delay(GAS_LEVEL_READING_PERIOD_MILLIS / 2);
}


