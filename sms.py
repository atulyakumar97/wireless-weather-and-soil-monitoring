import pandas
import time
from twilio.rest import Client

while True:
    df=pandas.read_csv("https://thingspeak.com/channels/408082/feed.csv")
    df=df.drop(["field4","entry_id","created_at"],1)
    df=df.rename(columns={'field1': 'wifi', 'field2': 'humidity', 'field3': 'temp','field5': 'aqi','field6': 'moisture'})

    avgwifi=df['wifi'].mean()
    avghumidity=df['humidity'].mean()
    avgtemp=df['temp'].mean()
    avgaqi=df['aqi'].mean()
    avgmoisture=df['moisture'].mean()

    print(df,'\n')

    #Average Values
    
    print("Average Values : ")
    print("Average Wifi Strength = ",avgwifi,"dB")
    print("Average Humidity = ",avghumidity,"%")
    print("Average Temperature = ",avgtemp," Celcius")
    print("Average AQI = ",avgaqi)
    print("Average Soil Moisture = ",avgmoisture)
    print()

    #Last Known Values / Current Values (Ignoring invalid indexes

    wifi=df['wifi'][df['wifi'].last_valid_index()]
    humidity=df['humidity'][df['humidity'].last_valid_index()]
    temp=df['temp'][df['temp'].last_valid_index()]
    aqi=df['aqi'][df['aqi'].last_valid_index()]
    moisture=df['moisture'][df['moisture'].last_valid_index()]

    print("Current Values : ")
    print("Current Wifi Strength : ", wifi,"dB")
    print("Current Humidity : ", humidity,"%")
    print("Current Temperature : ",temp,"Celcius")
    print("Current AQI : ",aqi)
    print("Current Soil Moisture % : ",moisture,"%")
    print()

    if aqi>100:
        account_sid = "ACb2b621362ce2b435ba55c4577fe1ed6d"
        auth_token  = "fea7e9970181ad490daeba47508e8db0"
        client = Client(account_sid, auth_token)

        message = client.messages.create(
            to="+917738437356", 
            from_="+17206198978",
            body="SMS Testing - Warning! Carbon Monoxide level is above 100 ppm !")

        print(message.sid)
    elif aqi==0:
        print("Heating switched off, sensor is temporarily switched off")
    else:
        print("Carbon Monoxide level is normal!")

    print("Refreshing data in 15 seconds")
    time.sleep(15)

    
    
