int fsrAnalogPin = 0; // FSR is connected to analog 0
int LEDpin = 13;      // connect Red LED to pin 11 (PWM pin)
int fsrReading;      // the analog reading from the FSR resistor divider
int LEDbrightness;
 
void setup(void) {
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor
  pinMode(LEDpin, OUTPUT);
  
}
 
void loop(void) {
  fsrReading = analogRead(fsrAnalogPin);
  Serial.print("Analog reading = ");
  Serial.println(fsrReading);


  //
  if (fsrReading>300){
    tone(LEDpin,100,100);
  }
  
  
 
  delay(100);
}
