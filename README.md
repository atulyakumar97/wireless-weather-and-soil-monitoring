# Wireless Weather and Soil Monitoring Station

Thingspeak Channel - https://thingspeak.com/channels/408082/ (Offline now)

Our main project objective is to integrate Temperature & Humidity Sensor (DHT11), Carbon Monoxide Sensor (MQ-7) and Soil Moisture Sensor with the Arduino Microcontroller.<br>
The final device is a low voltage system i.e. all sensors and components can work with a 6V battery or external power supply and is completely wireless with minimum internal connections making it ideal to be placed outside in the field.<br>
The system is completely wireless that senses and uploads data to a third-party website thingspeak.com, using the nodeMCU. All information sensed by the sensors will be uploaded at fixed intervals and stored online in a graphical manner with proper date and time-stamps to allow ease of access.<br>
Once the data acquisition system is successfully working and has collected data over certain time period, we begin analysing the data obtained.<br>
We developed a python app to scrape data from our IoT server https://thingspeak.com/channels/408082. The app displays real-time value as well averages of sensor values over a time period.<br>
Furthermore, by using Twilio API and Python we were able to send SMS to a mobile number in case of a high ppm value reported by the MQ-7 sensor along with a physical buzzer that is powered up if MQ-7 senses values above 250 ppm.<br>


# Circuit Diagram

![circuit diagram](https://github.com/atulyakumar97/wireless-weather-and-soil-monitoring/blob/master/circuit%20diagram.png?raw=true)


# Details about Technical Paper


ISBN : 978-93-5300-801-7<br>

Book Title: D J Strike 2018<br>
Name of Publisher: Anuja Arun Odhekar	<br>

It contains papers written by undergraduate engineering students based on their original technical project ideas performed under DJ Strike 2018. <br>This is mentorship programme held under Student Chapter of Electronics and Telecommunication Engineering Department, IETE-SF.	<br>

Publish Volume : 1	<br>
Publish Year : 2018	<br>
Publish Edition : first	<br>
Pages : 90	<br>
Language: English	<br>
ISSUE Date: 13-04-2018

# License and Copyright

Licensed under the [MIT License](LICENSE)
