#include "String.h"
#include <Math.h>

//////////////////////
// global variables //
//////////////////////
String inputString = "";    // a string to hold incoming data

int LY              = 0;    // Left Stick Foward/Backward
int RY              = 0;    // Right Stick Foward/Backward
int DIR             = 0;    // Direction
int StickRatio      = 2; // multiplier for stick input

int deadSpace       = 5;    // used to make the stick a little less sensative for moving //

int minSpeed        = 75;   // the smallest value we want to set as a motor speed //
int maxSpeed        = 255;  // the largest value we want to set as a motor speed //
int leftMotorSpeed  = 0;    // adjust later in code
int rightMotorSpeed = 0;    // adjust later in code

// used to determine the motor pins on the Arduino board
int pin_in1         = 9;     
int pin_in2         = 8;     
int pin_in3         = 7;     
int pin_in4         = 6;     

int pin_ENA         = 10;    // controls left motor speeds on the motor controller //
int pin_ENB         = 5;     // controls right motor speeds on the motor controller //

// used to determine a specific direction //
int dir_stop        = 0;
int dir_forward     = 1;
int dir_left        = 2;
int dir_right       = 3;
int dir_back        = 4;

// used as a safty in case communication with the car is lost //
int intSafty        = 0;

// used to set motor speeds //
float tempSpeed     = 0.0;

void setup()
{
  // initialize motors
  pinMode(pin_in1, OUTPUT); // send motor direction to motor controller //
  pinMode(pin_in2, OUTPUT); // send motor direction to motor controller //
  pinMode(pin_in3, OUTPUT); // send motor direction to motor controller //
  pinMode(pin_in4, OUTPUT); // send motor direction to motor controller //
  pinMode(pin_ENA, OUTPUT); // send left motor speed to motor controller //
  pinMode(pin_ENB, OUTPUT); // send right motor speed to motor controller //

  setMotors_Stop();  // make sure that the car is in park

  inputString.reserve(255);  // make inputString large enough to hold 255 chars

  Serial.begin(9600);  // Turn on bluetooth and initialize to 9600 bod
}

void loop()
{
  // the movement commands are captured in serialEvent //

  if (intSafty < 1200)
  {
    intSafty ++;
    determineAction();
    setMotorSpeeds();
    moveCar();
  }
  else
  {
    zeroVariables();
    setMotors_Stop();
  }
}

///////////////////////////////////////////////////////////////////////
void serialEvent()
{
  intSafty = 0;
  while (Serial.available())
  {
    char c = Serial.read();  // Read character
    inputString += c;

    if (c == ';')
      // If end-of-line, parse and reset inputStringfer and send back the data
    {
      parseInputString();  // Parse received data
    }
  }
}
void parseInputString()
{
  if (inputString.length() > 3)
  {
    int i = inputString.indexOf(' ');
    inputString.remove(0, i + 1);

    i = inputString.indexOf(' ');
    LY = inputString.substring(0, i).toInt();
    inputString.remove(0, i + 1);

    i = inputString.indexOf(' ');
    inputString.remove(0, i + 1);

    i = inputString.indexOf(' ');
    inputString.remove(0, i + 1);

    i = inputString.indexOf(' ');
    inputString.remove(0, i + 1);

    i = inputString.indexOf(' ');
    RY = inputString.substring(0, i).toInt();
    inputString.remove(0, i + 1);

    i = inputString.indexOf(';');
    inputString.remove(0, inputString.length());
  }
  else
  {
    inputString.remove(0, inputString.length());

    zeroVariables();
  }
}

///////////////////////////////////////////////////////////////////////
void determineAction()
{
  setDirection();
  setMotorSpeeds();
}
void setDirection()
{
  DIR = dir_stop;

  if (abs(LY) > deadSpace && abs(RY) > deadSpace)  // make sure that there is enough to move motors //
  {
    if (LY > 0 && RY > 0)
    {
      DIR = dir_forward;
    }
    if (LY < 0 && RY < 0)
    {
      DIR = dir_back;
    }
    if (LY > 0 && RY < 0)
    {
      DIR = dir_right;
    }
    if (LY < 0 && RY > 0)
    {
      DIR = dir_left;
    }
  } else
  {
    if (abs(LY) > deadSpace)  // is there enough from the left stick to move motors //
    {
      if (LY > 0)
      {
        DIR = dir_right;
      }
      else
      {
        DIR = dir_left;
      }
    }
    if (abs(RY) > deadSpace)  // is there enough from the right stick to move motors //
    {
      if (RY > 0)
      {
        DIR = dir_left;
      }
      else
      {
        DIR = dir_right;
      }
    }
  }
}
void setMotorSpeeds()
{
  tempSpeed = (float)abs(LY) * StickRatio;  // this way a max stick value of 100 results in 255 //
  leftMotorSpeed = (int)tempSpeed;  // motor speed in as integer but using a float in calculation so need to convert back to an integer //
  tempSpeed = (float)abs(RY) * StickRatio;  // this way a max stick value of 100 results in 255 //
  rightMotorSpeed = (int)tempSpeed;  // motor speed in as integer but using a float in calculation so need to convert back to an integer //

  // make sure that motor speed is not under min or over max speeds //
  verifyMotorSpeeds();
}

void verifyMotorSpeeds()
{
  // make sure that leftMotorSpeed is not under min or over max to protect the motors //
  if (leftMotorSpeed > 0 && leftMotorSpeed < minSpeed)
  {
    leftMotorSpeed = minSpeed;
  }
  if (leftMotorSpeed > maxSpeed)
  {
    leftMotorSpeed = maxSpeed;
  }
  // make sure that rightMotorSpeed is not under min or over max to protect the motors //
  if (rightMotorSpeed > 0 && rightMotorSpeed < minSpeed)
  {
    rightMotorSpeed = minSpeed;
  }
  if (rightMotorSpeed > maxSpeed)
  {
    rightMotorSpeed = maxSpeed;
  }
}

////////////////////////////////////////////////////////////////
void moveCar()
{
  if (DIR == dir_stop)
  {
    setMotors_Stop();
  }
  if (DIR == dir_forward)
  {
    setMotors_Forward();
  }
  if (DIR == dir_back)
  {
    setMotors_Backward();
  }
  if (DIR == dir_right)
  {
    setMotors_Right();
  }
  if (DIR == dir_left)
  {
    setMotors_Left();
  }
}
////////////////////////////////////////////////////////////////
void setMotors_Forward()
{
  analogWrite(pin_ENA, rightMotorSpeed);
  analogWrite(pin_ENB, leftMotorSpeed);
  digitalWrite(pin_in1, LOW);
  digitalWrite(pin_in2, HIGH);
  digitalWrite(pin_in3, LOW);
  digitalWrite(pin_in4, HIGH);
}
void setMotors_Backward()
{
  analogWrite(pin_ENA, rightMotorSpeed);
  analogWrite(pin_ENB, leftMotorSpeed);
  digitalWrite(pin_in1, HIGH);
  digitalWrite(pin_in2, LOW);
  digitalWrite(pin_in3, HIGH);
  digitalWrite(pin_in4, LOW);
}
void setMotors_Left()
{
  analogWrite(pin_ENA, rightMotorSpeed);
  analogWrite(pin_ENB, leftMotorSpeed);
  digitalWrite(pin_in1, LOW);
  digitalWrite(pin_in2, HIGH);
  digitalWrite(pin_in3, HIGH);
  digitalWrite(pin_in4, LOW);
}
void setMotors_Right()
{
  analogWrite(pin_ENA, rightMotorSpeed);
  analogWrite(pin_ENB, leftMotorSpeed);
  digitalWrite(pin_in1, HIGH);
  digitalWrite(pin_in2, LOW);
  digitalWrite(pin_in3, LOW);
  digitalWrite(pin_in4, HIGH);
}
void setMotors_Stop()
{
  digitalWrite(pin_ENA, LOW);
  digitalWrite(pin_ENB, LOW);
}

///////////////////////////////////////////////////////
void zeroVariables()
{
  LY = 0;
  RY = 0;
  DIR = 0;
}
