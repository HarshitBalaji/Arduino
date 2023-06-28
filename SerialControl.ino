int LEDpin = 12;
String status;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  pinMode(LEDpin, OUTPUT);
}

void loop() {
  
Serial.println("what to do? ON or OFF"); //print to serial monitor
while(Serial.available()==0){            //wait for input in serial monitor
  }
  
status=Serial.readString();             //read inout from serial monitor
if (status=="ON"){
  digitalWrite(LEDpin, HIGH);       //Turn the LED on if "ON" in serial monitor
  delay(1000);
  }
if (status=="OFF"){                    //Turn the LED off if "OFF" in serial monitor
    digitalWrite(LEDpin, LOW);      //turn the LED off by making the voltage LOW
    delay(1000); 
  }                   
}
