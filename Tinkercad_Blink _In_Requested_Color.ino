/*This code is to operate an arduino connected to an RGB LED and a servo motor.
The input is from the serial monitor or the UART serial communication ports, i.e. Digital pins 0 & 1 also labelled as Tx and Rx.
THe valid inputs are 'red','blue','green' and 'wave'
This was just to demostrate the working of accepting direct user input using Serial Monitor / UART serial communication.
*/
#include<Servo.h> 
//Initializing the GPIO pins.
int red=7;
int green=6;
int blue=5;
String command; //The String that will store the incoming message
Servo mm; //Initializing the servo motor object

void setup() // Runs once when the Arduino starts up
{
  mm.attach(9); //Specifying the pin the servo is attached to.
  Serial.begin(9600); //Starting communication with serial monitor
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
}

void wave() // to make servo motor do a wave motion
{
	int i;
  	for(i=0;i<90;i++)
    {mm.write(i);delay(10);}
  	for(i=90;i>0;i--)
    {mm.write(i);delay(10);}
}

void loop() //After execution of setup(), this function runs in a loop.
{
   //Reads String input from Serial Monitor
   command=Serial.readStringUntil('\n');
  
  //The following if else cases take appropriate action
  
   if(command=="red") //Blink in red color
   {
     digitalWrite(red,HIGH);
     delay(2000);
     digitalWrite(red,LOW);
   }
   if(command=="green") //Blink in green color
   {
     digitalWrite(green,HIGH);
     delay(2000);
     digitalWrite(green,LOW);
   }
  if(command=="blue") //Blink in blue color
   {
     digitalWrite(blue,HIGH);
     delay(2000);
     digitalWrite(blue,LOW);
   }
//___________________________________________________________________________
  if(command=="wave") //For the Servo Action: This makes the servo motor do a wave like motion.
   {
     wave();
   }
  
}
