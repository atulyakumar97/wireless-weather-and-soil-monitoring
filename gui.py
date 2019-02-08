import tkinter as tk
from tkinter import *
root=tk.Tk()
root.title("Wireless Weather and Soil Monitorings Station : Group 138")

import pandas
df=pandas.read_csv("https://thingspeak.com/channels/408082/feed.csv")
df=df.drop(["field4","entry_id","created_at"],1)
df=df.rename(columns={'field1': 'wifi', 'field2': 'humidity', 'field3': 'temp','field5': 'aqi','field6': 'moisture'})
avgwifi=df['wifi'].mean()
avgtemp=df['temp'].mean()
avghumidity=df['humidity'].mean()
wifi=df['wifi'][df['wifi'].last_valid_index()]
humidity=df['humidity'][df['humidity'].last_valid_index()]
temp=df['temp'][df['temp'].last_valid_index()]
aqi=df['aqi'][df['aqi'].last_valid_index()]
moisture=df['moisture'][df['moisture'].last_valid_index()]
avgmoisture=df['moisture'].mean()

avgwifi1=StringVar()
avgtemp1=StringVar()
avghumidity1=StringVar()
wifi1=StringVar()
temp1=StringVar()
humidity1=StringVar()
str=StringVar()
soilmoistureentry=StringVar()

def btn_Click():
    avgwifi1.set(avgwifi)
    avgtemp1.set(avgtemp)
    avghumidity1.set(avghumidity)
    wifi1.set(wifi)
    temp1.set(temp)
    humidity1.set(humidity)
    soilmoistureentry.set(avgmoisture)


labelTitle = tk.Label(root, text="Current and Average Sensor Values").grid(row=0, column=1)
labelNum1 = tk.Label(root, text="Current  Temperature").grid(row=1, column=0)

labelNum2 = tk.Label(root, text="Average Temperature").grid(row=2, column=0)

labelNum3 = tk.Label(root, text="Current  Humidity").grid(row=3, column=0)

labelNum4 = tk.Label(root, text="Average Humidity").grid(row=4, column=0)

labelNum5 = tk.Label(root, text="Current  RSSI").grid(row=5, column=0)

labelNum6 = tk.Label(root, text="Average RSSI").grid(row=6, column=0)

entryNum1 = tk.Entry(root,textvariable=temp1).grid(row=1, column=2)

entryNum2 = tk.Entry(root, textvariable=avgtemp1).grid(row=2, column=2)

entryNum3 = tk.Entry(root,textvariable=humidity1).grid(row=3, column=2)

entryNum4 = tk.Entry(root, textvariable=avghumidity1).grid(row=4, column=2)

entryNum5 = tk.Entry(root,textvariable=wifi1).grid(row=5, column=2)

entryNum6 = tk.Entry(root, textvariable=avgwifi1).grid(row=6, column=2)


buttonCal = tk.Button(root, text="Calculate", command=btn_Click).grid(row=8, column=2)

def var_states():
   print("male: %d,\nfemale: %d" % (var1.get(), var2.get()))

def click():
    if var1.get()==1 and var2.get()==0:
        if avgmoisture<=2:
            str.set("Exteme Stress")    
        elif avgmoisture>2 and avgmoisture<=5:
            str.set("Stress")
        elif avgmoisture>5 and avgmoisture<=10:
            str.set("Optimal Moisture")
        elif avgmoisture>10:
            str.set("Excess Moisture")    
        
    elif var1.get()==0 and var2.get()==1:
        if avgmoisture<=30:
            str.set("Exteme Stress")    
        elif avgmoisture>30 and avgmoisture<=40:
            str.set("Stress")
        elif avgmoisture>40 and avgmoisture<=50:
            str.set("Optimal Moisture")
        elif avgmoisture>50:
            str.set("Excess Moisture")    
    elif var1.get()==0 and var2.get()==0:
        str.set("select any one type")
    else:
        str.set("select only one type")
        

Label(root, text="Soil Type :").grid(row=9,column=0, sticky=W)
var1 = IntVar()
Checkbutton(root, text="Sand", variable=var1).grid(row=9,column=1, sticky=W)
var2 = IntVar()
Checkbutton(root, text="Clay", variable=var2).grid(row=9,column=2, sticky=W)

Label(root,text="Average Soil Moisture").grid(row=10,column=0)
Entry(root,textvariable=soilmoistureentry).grid(row=10,column=1)
Button(root,text="Check Soil Status", command=click).grid(row=11)
Entry(root, textvariable=str).grid(row=11,columnspan=5)

text1 = Text(root, height=100, width=50)
photo=PhotoImage(file='./moisture.png')
text1.insert(END,'\n')
text1.image_create(END, image=photo)
text1.grid(row=12,columnspan=3)
root.mainloop()
