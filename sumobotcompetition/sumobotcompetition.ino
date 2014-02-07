#include <Servo.h>
Servo servo;



int motorPin1F = 5;
int motorPin1R = 6;
int motorPin2F = 9;
int motorPin2R = 10;
int photoCellPin1 = A0;
int photoCellPin2 = A1;
int irSensorPin = A2; 
int sonarSensorPin = 13;
int minLight1 = 0;
int minLight2 = 0;



void setup()
{
//Serial.begin(9600);
delay(5000);
//servo.attach(3); //check which pin it is connected on
pinMode(motorPin1F, OUTPUT);
pinMode(motorPin1R,OUTPUT);
pinMode(motorPin2F, OUTPUT);
pinMode(motorPin2R, OUTPUT);
pinMode(photoCellPin1,INPUT);
pinMode(photoCellPin2,INPUT);
pinMode(irSensorPin, INPUT);
digitalWrite(motorPin1F, LOW);
digitalWrite(motorPin2F, LOW);
digitalWrite(motorPin2R, LOW);
digitalWrite(motorPin2R, LOW);
minLight1 = analogRead(photoCellPin1) - 200;
minLight2 = analogRead(photoCellPin2) - 100;

//servo.write(45); //Confirm this lifts up spike, and lowers ramp

}


//-----------------------The main algorithm for the sumobot-----------------------//
void loop()
{

  while(noLineFront() && noLineBack())
  {
    boolean sT = somethingThere();
    if(sT)
    {
      goForward();
    }
    else
    {
    turn30CCW();
    }
  }
 boolean x = noLineFront();
 boolean y = noLineBack();
  if (x == false && y == false)
  {
    turn30CCW();
  } else if (y == false)
  {
    foreward();
    turn180CCW();
  } else if (x == false)
  {
    reverse();
    turn180CCW();
  }
}
//----------------------Finds other Sumobot---------------------------------------//

boolean somethingThere()
{
 float x = irBot();
 long y = sonarBot();
  if (((x > 1.40 && x < 1.32) || (y <= 77 && y >= 3)))
  {
    return true;
  }
  return false;
}

//-------------------------Constant Move Functions------------------------------//

void goForward()
{
boolean sT = somethingThere();
if (sT)
{
  digitalWrite(motorPin1F, HIGH);
  digitalWrite(motorPin2F, HIGH);
}
while(noLineFront()){noLineFront();}
digitalWrite(motorPin1F, LOW);
digitalWrite(motorPin2F, LOW); 
}

//---------------------Discrete Move Functions---------------------------------//** CALLIBRATE SERVO**
void turn30CCW()
{
//servo.write(0);
//digitalWrite(motorPin1R,HIGH);
digitalWrite(motorPin2F,HIGH);
delay(1000);
//digitalWrite(motorPin1R,LOW);
digitalWrite(motorPin2F,LOW);
//servo.write(45);
}

void turn30CW()
{
 // servo.write(0);
digitalWrite(motorPin2R,HIGH);
delay(750);
digitalWrite(motorPin2R,LOW);
//servo.write(45);
}


void turn180CCW()
{
//servo.write(0);
digitalWrite(motorPin1R,HIGH);
delay(7000);
digitalWrite(motorPin1R,LOW);
//servo.write(45);
}

void turn180CW()
{
  servo.write(0);
digitalWrite(motorPin2R,HIGH);
delay(2000);
digitalWrite(motorPin2R,LOW);
servo.write(45);
}


void reverse()
{
  if(noLineBack()){
 // servo.write(0);
  digitalWrite(motorPin1R,HIGH);
  digitalWrite(motorPin2R,HIGH);
  delay(2000);
  digitalWrite(motorPin1R,LOW);
  digitalWrite(motorPin2R,LOW);
 // servo.write(45);
  }
}

void foreward()
{
  digitalWrite(motorPin1F,HIGH);
  digitalWrite(motorPin2F,HIGH);
  delay(1000);
  digitalWrite(motorPin1F,LOW);
  digitalWrite(motorPin2F,LOW);
}
//----------------------Looks for the line and other sumobot------------------------------------------// **CALLIBRATE IR AND SONAR SENSORS**
boolean noLineFront()
{
int lightLevel1=analogRead(photoCellPin1);
if( minLight1>lightLevel1){
  return false;
}else{
return true;
}
}

boolean noLineBack()
{
int lightLevel2=analogRead(photoCellPin2);
if(minLight2 > lightLevel2){
  return false;
}else{
return true;
}
}

long sonarBot()
{
  long duration, cm;
  pinMode(sonarSensorPin,OUTPUT);
  digitalWrite(sonarSensorPin, LOW);
  delayMicroseconds(2);
  digitalWrite(sonarSensorPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(sonarSensorPin, LOW); 
  pinMode(sonarSensorPin,INPUT);
  duration = pulseIn(sonarSensorPin, HIGH);
  return microsecondsToCm(duration);
}

float irBot()
{
  return analogRead(irSensorPin)*(5.0/1023.0); //Need to callibrate
}
//--------------------To convert the echo to distance measurements------------------------------------//

float microsecondsToCm(float microseconds)
{
  return microseconds / 29.0 / 2.0;
}
