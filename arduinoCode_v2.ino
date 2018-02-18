#include <Time.h>
#include <TimeLib.h>

int fsrAnalogPin = 0; // FSR is connected to analog 0
int speaker = 13;      // connect Red LED to pin 11 (PWM pin)
int fsrReading;      // the analog reading from the FSR resistor divider
int pitch=50;
int currentTime;
bool pressed;

// Pin 2-8 is connected to the 7 segments of the display.
const int DELAY_TIME=2;
int pinA = 2;
int pinB = 3;
int pinC = 4;
int pinD = 5;
int pinE = 6;
int pinF = 7;
int pinG = 8;
int D1 = 9;
int D2 = 10;
int D3 = 11;
int D4 = 12;
int timeNow;
int timeElapsed = 0;

void setup(void) {
  Serial.begin(9600); // We'll send debugging information via the Serial monitor
  pinMode(speaker, OUTPUT);

  // initialize the digital pins as outputs.
  pinMode(pinA, OUTPUT);     
  pinMode(pinB, OUTPUT);     
  pinMode(pinC, OUTPUT);     
  pinMode(pinD, OUTPUT);     
  pinMode(pinE, OUTPUT);     
  pinMode(pinF, OUTPUT);     
  pinMode(pinG, OUTPUT);   
  pinMode(D1, OUTPUT);  
  pinMode(D2, OUTPUT);  
  pinMode(D3, OUTPUT);  
  pinMode(D4, OUTPUT);  
  timeNow=now();
  currentTime=millis();
  pressed=false;
}

void printNumber(int digit, int digitPlace){
  if (digitPlace==1){
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
    digitalWrite(D3, LOW);
    digitalWrite(D4, HIGH); 
  }else if (digitPlace==2){
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
    digitalWrite(D3, HIGH);
    digitalWrite(D4, LOW); 
  }else if (digitPlace==3){
    digitalWrite(D1, LOW);
    digitalWrite(D2, HIGH);
    digitalWrite(D3, LOW);
    digitalWrite(D4, LOW); 
  }else if (digitPlace==4){
    digitalWrite(D1, HIGH);
    digitalWrite(D2, LOW);
    digitalWrite(D3, LOW);
    digitalWrite(D4, LOW); 
  }

  if (digit==0){
    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, LOW);   
    digitalWrite(pinF, LOW);   
    digitalWrite(pinG, HIGH); 
  }else if (digit==1){
    digitalWrite(pinA, HIGH);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, HIGH);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, HIGH);   
    digitalWrite(pinG, HIGH);
  }else if (digit==2){
    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, HIGH);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, LOW);   
    digitalWrite(pinF, HIGH);   
    digitalWrite(pinG, LOW);
  }else if (digit==3){
    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, HIGH);   
    digitalWrite(pinG, LOW);
  }else if (digit==4){
    digitalWrite(pinA, HIGH);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, HIGH);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, LOW);   
    digitalWrite(pinG, LOW);
  }else if (digit==5){
    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, HIGH);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, LOW);   
    digitalWrite(pinG, LOW);
  }else if (digit==6){
    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, HIGH);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, LOW);   
    digitalWrite(pinF, LOW);   
    digitalWrite(pinG, LOW);
  }else if (digit==7){
    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, HIGH);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, LOW);   
    digitalWrite(pinG, HIGH);
  }else if (digit==8){
    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, LOW);   
    digitalWrite(pinF, LOW);   
    digitalWrite(pinG, LOW);
  }else if (digit==9){
    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, LOW);   
    digitalWrite(pinG, LOW);
  }    
}
 
void loop(void) {
  fsrReading = analogRead(fsrAnalogPin);
  //output force reading to python program
  Serial.println(fsrReading);

  if (pressed){
    if((now()-timeNow)>=1){
      timeNow=now();
      timeElapsed++;
    }

    if (timeElapsed<10){
      printNumber(0,3);
      delay(DELAY_TIME);
      printNumber(0,4);
      delay(DELAY_TIME);
      printNumber(0,2);
      delay(DELAY_TIME);
      printNumber(timeElapsed,1);  
      delay(DELAY_TIME);
    }else if (timeElapsed>=10 && timeElapsed<100){
      printNumber(0,3);
      delay(DELAY_TIME);
      printNumber(0,4);
      delay(DELAY_TIME);
      printNumber(timeElapsed/10,2);
      delay(DELAY_TIME);
      printNumber(timeElapsed%10,1);  
      delay(DELAY_TIME);
    }else if (timeElapsed>=100 && timeElapsed<1000){
      printNumber(0,4);
      delay(DELAY_TIME);
      printNumber(timeElapsed/100,3);
      delay(DELAY_TIME);
      printNumber((timeElapsed%100)/10,2);
      delay(DELAY_TIME);
      printNumber((timeElapsed%10),1);
      delay(DELAY_TIME);
    }else{
      printNumber(timeElapsed/1000,4);
      delay(DELAY_TIME);
      printNumber((timeElapsed%1000)/100,3);
      delay(DELAY_TIME);
      printNumber((timeElapsed%100)/10,2);
      delay(DELAY_TIME);
      printNumber((timeElapsed%10),1);
      delay(DELAY_TIME); 
    }
  }

  if (fsrReading>300){
    currentTime=millis();
    pressed = true;
    if (pitch <1000){
      pitch+=10;
    }
    tone(speaker,pitch,100);
  }
}


