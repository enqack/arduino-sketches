/*
 battery_alarm
 
 Fades LED and beeps buzzer on low voltage warning value.
 Strobes LED and alarm buzzer on low voltage cut-off value.
 
 */
 

 
float lvw = 3.9;  // low voltage warning value
float lvc = 3.0;  // low voltage cut-off value

int led_pin = 9;  // the pin that the LED is attached to
int buzzer_pin = 10; // the pin the buzzer is attached to




// the setup routine runs once when you press reset
void setup()  { 
  // declare pin 9 to be an output:
  pinMode(led_pin, OUTPUT);
  // set buzzer pin as output
  pinMode(buzzer_pin, OUTPUT);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  beep(0);
  delay(250);
  beep(0);
  delay(250);
  beep(0);
  delay(1000);
} 

// the loop routine runs over and over again forever
void loop()  {
  float c_volt = 0;
   
  // read the input on analog pin 1
  int sensorValue = analogRead(A1);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
  c_volt = sensorValue * (5.0 / 1023.0);
  
 // if voltage is equal to or less than cut-off level, alarm and strobe
 if( c_volt <= lvc) {
   lv_cutoff();
 } 
 // if voltage is equal to or less than warn level, beep and fade
 else if( c_volt <= lvw ) {
   lv_warn(5);
 }
 // ensure buzzer and led is off
 else {
   analogWrite(led_pin, 0);
   analogWrite(buzzer_pin, 0); 
 }
}

void lv_warn(int increment) {
  // beep every 3500 3.5
  beep(3500);
  
  // fade in from min to max in increment
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=increment) { 
    analogWrite(led_pin, fadeValue);         
    delay(30);                            
  } 

  // fade out from max to min in increment
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=increment) { 
    analogWrite(led_pin, fadeValue);         
    delay(30);                            
  } 
}

void lv_cutoff(){
  // fade out from max to min in increments of 20
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=20) { 
    analogWrite(buzzer_pin, fadeValue);     
    analogWrite(led_pin, fadeValue);     
    delay(30);                            
  } 
}

void beep(long interval){
  static long previousBeep = 0;
  
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousBeep > interval) {
    // save the last time you blinked the LED 
    previousBeep = currentMillis;   
    analogWrite(buzzer_pin, 100);
    delay(100);
    analogWrite(buzzer_pin, 0);
  }  
}  

