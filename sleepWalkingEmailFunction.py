#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Feb 17 17:04:01 2018

@author: charleyxu
"""
import time
import serial
import smtplib
from email.mime.text import MIMEText
import requests
import json

send_url = 'http://freegeoip.net/json'
r = requests.get(send_url)
j = json.loads(r.text)
lat = j['latitude']
lon = j['longitude']

#THIS PORT CAN CHANGE!!!!
ser=serial.Serial('/dev/tty.usbmodem1421',9600);

gMapsLink="https://www.google.com/maps/search/?api=1&query="+str(lat)+","+str(lon);

email_content="STOP SLEEPWALKING pls! "+ "The location is at " + gMapsLink

#allows for email subject to be sent
msg=MIMEText(email_content)

msg['Subject']= "STOP SLEEPWALKING! "

#log into SMTP Server
try:
    gmail_username='ieeehwh@gmail.com'
    gmail_password='tomthecat123'
    print("Connecting to Gmail Server...)")
    server=smtplib.SMTP('smtp.gmail.com',587)
    print("Connected!")
    
    server.starttls() #makes secure connection
    #login
    print("Logging into account...")
    server.login(gmail_username,gmail_password)
    print("Logged in!")
    print("Detection system ready!")          

except:
    print("Cannot connect to Gmail Server")

#continually read bytes from serial
firstTime=time.time()
while True:
    readingBytes=(ser.readline());
    
    #convert bytes to integer
    readingConverted="".join(map(chr,readingBytes))
    readingConverted=int(readingConverted)
    
    #send email if force sensor is too high
    currentTime=time.time()
    #only run after 5 seconds after 5 second buffer
    if (readingConverted > 400 and currentTime - firstTime > 5):
    #sendEmail
        print(currentTime - firstTime)
        firstTime=time.time()    
        
        print("Force level > 400 detected: ")
        print("Sending warning email")
        msg['Subject']="SLEEP WALKING ALERT! PLEASE GO CHECK" 
        server.sendmail('ieeehwh@gmail.com','charleyxu2@gmail.com',msg.as_string())
        print("EMAIL SENT!!!")
