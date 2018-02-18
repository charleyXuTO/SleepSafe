#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Feb 17 17:04:01 2018

@author: charleyxu
"""

import serial
import smtplib

from email.mime.text import MIMEText



#THIS PORT CAN CHANGE!!!!
ser=serial.Serial('/dev/tty.usbmodem1421',9600);


from_email='ieehw@gmail.com'
to_email='sharon.lin89@hotmail.com'

email_content="STOP SLEEPWALKING"

#allows for email subject to be sent
msg=MIMEText(email_content)



msg['Subject']="STOP SLEEPWALKING"








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
while True:
    readingBytes=(ser.readline());
    
    #convert bytes to integer
    readingConverted="".join(map(chr,readingBytes))
    readingConverted=int(readingConverted)
    
    #send email if force sensor is too high
    if (readingConverted > 400):
    #sendEmail
        print("Force level > 400 detected: ")
        print("Sending warning email")
        msg['Subject']="SLEEP WALKING ALERT! PLEASE GO CHECK" 
        server.sendmail('ieeehwh@gmail.com','sharon.lin89@hotmail.com',msg.as_string())
        print("EMAIL SENT!!!")
        
        print(readingConverted)




