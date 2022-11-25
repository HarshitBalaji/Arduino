 //My first attempt at making a simple robot.
 //A quick-to-make and simple robot that waves at you when you get close enough to it.
 //Sensor: Sonar Sensor. Actuator: Servo Motor
 //By: Sai Harshit B  
 //email: sai.harshitbalaji.24@gmail.com
 //contact number: +91 8431003590
 //Date: 25/11/2022
 
 #include <Servo.h> //Robot arm uses a servo motor. I used the one which moves only between 0 and 180 degree positions.

//Global Variables:

Servo moto;  //moto is name of the servo motor. We can name it anything. It is a variable.
int pos = 0; //tracks position of the arm.

const int trig=11; //Initialize trigger pin. Trigger sends an ultrasound pulse.
const int echo=10; //Initialize echo pin. Echo detects reflected pulse.


//Functions:
//________________________________________________________________________________
void setup() 
{
  // The pins are initialized as input/output. The pulse for the servo motor is sent through pin 5 which has pwm capacity.
  moto.attach(5);
  
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}
//__________________________________________________________________________________
void wave()
//Decides on what way the arm should move to wave properly.
{
  moto.write(90);
  int i;
  if(pos==120) //The arm was at left end. Time to move right.
  {
    gotopose(60,120);
    return;
  }
  else if(pos==60)//The arm was at the right end. Time to move left.
  {
    gotopose(120,60);
    return;
  }
  else if (pos==90)  //The arm was resting. So it can move to left first.
  {gotopose(120,90);return;}
}
//_____________________________________________________________________
void gotopose(int pose,int curr) 
//This smoothens out the motion of the arm.
{
  if(pose>curr) //to move left
  {
    for(int i=curr;i<=pose;i+=2)
    {
      moto.write(i);pos=i;delay(10);
    }
  }
  
  else if(pose<curr) //to move right
  {
    for(int i=curr;i>=pose;i-=2)
    {
      moto.write(i);pos=i;delay(10);
    }
  }
  else //Stay at same place.
  {return;}
}
//__________________________________________________________________________
void loop() 
//runs on an infinite loop as long as the device has power and is turned ON.
//The block of code reads the data from sensor and acts on it.
{
  // A pulse is sent everytime the loop function iterates. The pulse lasts for 2 milliseconds.
  digitalWrite(trig, LOW);
  delay(2);
  digitalWrite(trig, HIGH);
  delay(2);
  digitalWrite(trig, LOW);

  //Distance calculated using the duration between pulse and echo, multiplying it with speed of sound. 
  //We divide by 2 because pulse travels twice the distance between the source and object.
  float distance=(pulseIn(echo, HIGH))*0.017;

  //Action taken on distance calculated:
  if(distance<=90)
  {
    wave(); //start waving if object is detected
  }
  else
  {
    gotopose(90,pos);pos=90; //No object within range. So the arm has to go back to resting position.
  }
  
}
//End of code
//_________________________________________________________________________________________________________
