
#include "String.h"
#include <Math.h>

#define BUTTON_UP_MASK      1
#define BUTTON_DOWN_MASK    2
#define BUTTON_LEFT_MASK    4
#define BUTTON_RIGHT_MASK   8
#define BUTTON_START_MASK   16
#define BUTTON_SELECT_MASK  32
#define BUTTON_L3_MASK      64
#define BUTTON_R3_MASK      128
#define BUTTON_L1_MASK      256
#define BUTTON_R1_MASK      512
#define BUTTON_A_MASK       4096
#define BUTTON_B_MASK       8192
#define BUTTON_X_MASK       16384
#define BUTTON_Y_MASK       32768

#define isButtonPressed(reg, mask)  ((reg & mask) == mask)

//////////////////////
// global variables //
//////////////////////
int gpio = 12;
String inputString = "";    // a string to hold incoming data
String outputString = "";    // a string to hold incoming data

int LY              = 0;    // Left Stick Foward/Back
int RY              = 0;    // Right Stick Foward/Back
int DIR             = 0;    // Direction
int StickRatio      = 2; // multiplier for stick input
int buttons         = 0;    // 

//int maxStick;  // max abs value of Y and X

int deadSpace       = 5;    // used to make the stick a little less sensative for moving //

int minSpeed        = 75;   // the smallest value we want to set as a motor speed //
int maxSpeed        = 255;  // the largest value we want to set as a motor speed //
int leftMotorSpeed  = 0;    // adjust later in code
int rightMotorSpeed = 0;    // adjust later in code

int in1         = 9;     // right
int in2         = 8;     // right
int in3         = 7;     // left
int in4         = 6;     // left

int ENA         = 10;    // controls left motor speeds on the motor controller //
int ENB         = 5;   // controls right motor speeds on the motor controller //

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


//Ultrasonic Variable Definition
#include <Servo.h>  //servo library
Servo myservo;
// create servo object to control servo
int Echo = A4;
int Trig = A5;

int StopDistance = 25;

//Line Tracker Variable Definition
#define LT_R !digitalRead(2)
#define LT_M !digitalRead(4)
#define LT_L !digitalRead(11)


void setup() {
  // put your setup code here, to run once:
 // initialize motors
  pinMode(in1, OUTPUT); // send motor direction to motor controller //
  pinMode(in2, OUTPUT); // send motor direction to motor controller //
  pinMode(in3, OUTPUT); // send motor direction to motor controller //
  pinMode(in4, OUTPUT); // send motor direction to motor controller //
  pinMode(ENA, OUTPUT); // send left motor speed to motor controller //
  pinMode(ENB, OUTPUT); // send right motor speed to motor controller //

  Stop();  // make sure that the car is in park

  inputString.reserve(255);  // make inputString large enough to hold 255 chars

  Serial.begin(9600);  // Turn on bluetooth and initialize to 9600 bod
  pinMode(gpio, OUTPUT);
  
  /* You have a number of funcitons to choose from that are defined below. Arrange them in order as you wish
      1000 milliseconds = 1 second
      List of Functions:
        Stop()                - will Stop the car until next command
        Stop(input)           - will Stop the car for 'input' number of milliseconds
        Forward()             - will move forward until next command
        Forward(input)        - will move forward for 'input' number of milliseconds
        Back()                - will move backward until next command
        Back(input)           - will move backward for 'input' number of milliseconds
        Right()               - will turn right until next command
        Right(input)          - will turn right for 'input' number of milliseconds
        Left()                - will turn left until next command
        Left(input)           - will turn left for 'input' number of milliseconds

        Check_Front()         - Uses the Ultrasonic Sensor to check the front of the car and returns a distance value
        Check_Left()          - Uses the Ultrasonic Sensor to check the left of the car and returns a distance value
        Check_Right()         - Uses the Ultrasonic Sensor to check the right of the car and returns a distance value

        Forward_CheckFront()  - will move forward until detects an object then Stop
        Right_CheckRight()    - will turn Right until detects an object then Stop
        Left_CheckLeft()      - will turn left until detects an object then Stop
        Forward_Sweep()       - will move forward until detects an object using a 15 degree sweep

        Ultrasonic_FLRCheck() - will move forward until object is detected, check left, check right, then towards to the side that is clear or move back if all sides are blocked
        Distance_test()       -returns a distance value from the ultrasonic sensor
        
        Forward_TrackLine()   - will move forward and track a line if present
        TrackLine_CheckFront()- will track line until something there is an obsacle detected
        TrackLine_Stop()      - will track a line if present and Stop if no line is present
        TrackLine_Stop(input) - will track a line if present and Stop if no line is present for input number of seconds

        FindLine_Right()      - will turn right until a line is sensed
        FindLine_Left()       - will turn right until a line is sensed
        FindLine_Forward()    - will move forward until a line is sensed
        FindLine_Back()       - will move backward until a line is sensed

        delay(input)          - car will not do anything for input number of milliseconds
        BoxTrap()             - will not cross a line, can trap by putting a box around the car
        
  */

}

void loop() {
  // 1 Teleop1
  // 2 Autonomous1
   int DriveMode = 1;

  if(isButtonPressed(buttons, BUTTON_A_MASK)){
    DriveMode = 2;
  }

   switch (DriveMode) {
   case 1: //Tank Control
     /********************************* START TELEOP1 *****************************************************/
     Serial.println("Teleop");
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
      Stop();
    }
     /********************************* END TELEOP1 *******************************************************/
   break;
   
   case 2:
     /********************************* START AUTONOMOUS1 *************************************************/
     Serial.println("Autonomous1");
     leftMotorSpeed  = 255;  
     rightMotorSpeed = 200;

    TrackLine_Stop();
    delay(250);
    FindLine_Right();
    delay(250);
    TrackLine_Stop(2500);
    Forward(2500);
    Stop();

     /********************************* END AUTONOMOUS1 ***************************************************/
     DriveMode = 1;
   break;
   }
}

/*********************************END Tank Control Teleop ************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************** FUNCTIONs Tank Control ************************************************/

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
    buttons = inputString.substring(0, i).toInt();
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
    Stop();
  }
  if (DIR == dir_forward)
  {
    Forward();
  }
  if (DIR == dir_back)
  {
    Back();
  }
  if (DIR == dir_right)
  {
    Right();
  }
  if (DIR == dir_left)
  {
    Left();
  }
}

///////////////////////////////////////////////////////
void zeroVariables()
{
  LY = 0;
  RY = 0;
  DIR = 0;
}
/**************************************************END TANK CONTROL FUNCTIONS **************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////////
/*define stop function*/
void Stop(int duration)
{
  analogWrite(ENA, rightMotorSpeed);
  analogWrite(ENB, leftMotorSpeed);

  //RIGHT Motor Spin Forward
  digitalWrite(in4, LOW); //digital output
  digitalWrite(in3, LOW);

  //Left Motor Spin Forward
  digitalWrite(in2, LOW);
  digitalWrite(in1, LOW);

  //continue spinning for specified amount of time
  delay(duration);
  Stop();

  Serial.println("Stop");
  Serial.println(duration);
}

/*define forward function*/
void Forward(int duration)
{
  analogWrite(ENA, rightMotorSpeed);
  analogWrite(ENB, leftMotorSpeed);

  //RIGHT Motor Spin Forward
  digitalWrite(in4, HIGH); //digital output
  digitalWrite(in3, LOW);

  //Left Motor Spin Forward
  digitalWrite(in2, HIGH);
  digitalWrite(in1, LOW);

  //continue spinning for specified amount of time
  delay(duration);
  Stop();

  Serial.println("Forward");
  Serial.println(duration);
}

/*define back function*/
void Back(int duration)
{
  analogWrite(ENA, rightMotorSpeed);
  analogWrite(ENB, leftMotorSpeed);

  //RIGHT Motor Spin Back
  digitalWrite(in4, LOW); //digital output
  digitalWrite(in3, HIGH);

  //Left Motor Spin Back
  digitalWrite(in2, LOW);
  digitalWrite(in1, HIGH);

  //continue spinning for specified amount of time
  delay(duration);
  Stop();

  Serial.println("Back");
  Serial.println(duration);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
void Left(int duration)
{
  analogWrite(ENA, rightMotorSpeed);
  analogWrite(ENB, leftMotorSpeed);

  //RIGHT Motor Spin Back
  digitalWrite(in4, LOW); //digital output
  digitalWrite(in3, HIGH);

  //Left Motor Spin Forward
  digitalWrite(in2, HIGH);
  digitalWrite(in1, LOW);

  //continue spinning for specified amount of time
  delay(duration);
  Stop();

  Serial.println("Left");
  Serial.println(duration);
}

//////////////////////////////////////////////////////////////////////////////////////////////
void Right(int duration) //car will turn right for the specified duration in milliseconds
{
  analogWrite(ENA, rightMotorSpeed);
  analogWrite(ENB, leftMotorSpeed);

  //RIGHT Motor Spin Forward
  digitalWrite(in4, HIGH); //digital output
  digitalWrite(in3, LOW);

  //Left Motor Spin Back
  digitalWrite(in2, LOW);
  digitalWrite(in1, HIGH);

  //continue spinning for specified amount of time
  delay(duration);
  Stop();

  Serial.println("Right");
  Serial.println(duration);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
void Stop()
{
  analogWrite(ENA, rightMotorSpeed);
  analogWrite(ENB, leftMotorSpeed);

  //RIGHT Motor Spin Forward
  digitalWrite(in4, LOW); //digital output
  digitalWrite(in3, LOW);

  //Left Motor Spin Forward
  digitalWrite(in2, LOW);
  digitalWrite(in1, LOW);

  Serial.println("Stop");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Forward()
{
  analogWrite(ENA, rightMotorSpeed);
  analogWrite(ENB, leftMotorSpeed);

  //RIGHT Motor Spin Forward
  digitalWrite(in4, HIGH); //digital output
  digitalWrite(in3, LOW);

  //Left Motor Spin Forward
  digitalWrite(in2, HIGH);
  digitalWrite(in1, LOW);

  Serial.println("Forward");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Back()
{
  analogWrite(ENA, rightMotorSpeed);
  analogWrite(ENB, leftMotorSpeed);

  //RIGHT Motor Spin Back
  digitalWrite(in4, LOW); //digital output
  digitalWrite(in3, HIGH);

  //Left Motor Spin Back
  digitalWrite(in2, LOW);
  digitalWrite(in1, HIGH);

  Serial.println("Back");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Left()
{
  analogWrite(ENA, rightMotorSpeed);
  analogWrite(ENB, leftMotorSpeed);

  //RIGHT Motor Spin Back
  digitalWrite(in4, LOW); //digital output
  digitalWrite(in3, HIGH);

  //Left Motor Spin Forward
  digitalWrite(in2, HIGH);
  digitalWrite(in1, LOW);

  Serial.println("Left");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Right() //car will turn right until Stopped
{  
  analogWrite(ENA, rightMotorSpeed);
  analogWrite(ENB, leftMotorSpeed);

  //RIGHT Motor Spin Forward
  digitalWrite(in4, HIGH); //digital output
  digitalWrite(in3, LOW);

  //Left Motor Spin Back
  digitalWrite(in2, LOW);
  digitalWrite(in1, HIGH);

  Serial.println("Right");
}
/*******************************************************************UTRASONIC FUNCTIONS ************************************************************/

int Distance_test() { 
  digitalWrite(Trig, LOW);     
  delayMicroseconds(2);  
  digitalWrite(Trig, HIGH);    
  delayMicroseconds(20);  
  digitalWrite(Trig, LOW);

  float Fdistance = pulseIn(Echo, HIGH);   
  Fdistance = Fdistance / 58;        
  return (int)Fdistance;
  
}
///////////////////////////////////////////////////////////////////////////////////////////////
int Check_Front() {
  myservo.write(90); //90 degrees
  //setservo position according to scaled value
  delay(100);
  int Distance = Distance_test();
  return (int)Distance;

  Serial.println("FrontDistance");
  Serial.println(Distance);
}

////////////////////////////////////////////////////////////////////////////////////////////////
int Check_Left() {
  myservo.write(15); //0 degrees
  //setservo position according to scaled value
  delay(100);
  int Distance = Distance_test();
  return (int)Distance;

  Serial.println("LeftDistance");
  Serial.println(Distance);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
int Check_Right() {
  myservo.write(165); //180 degrees
  //setservo position according to scaled value
  delay(100);
  int Distance = Distance_test();
  return (int)Distance;

  Serial.println("RightDistance");
  Serial.println(Distance);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
void Forward_Sweep() {
  bool path_Clear = true;
  int degree = 90;
  bool rotRight = true; //true if rotating right false if rotating left

  while (path_Clear == true) {
    Serial.println("pathclear");
    Forward();

    myservo.write(degree);
    Serial.println(degree);
    int Distance = Distance_test();
    delay(200);


    if (rotRight) {
      if (degree > 0) {
        degree = degree - 15;
      }
      else {
        degree = degree + 15;
        rotRight = false;
      }
    }
    else { //rotating left
      if (degree < 180) {
        degree = degree + 15;
      }
      else {
        degree = degree - 15;
        rotRight = true;
      }
    }


    if (Distance < StopDistance) {
      path_Clear = false;
      Serial.println("ObjectDetected");
      Serial.println(Distance);
      Stop();
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void Forward_CheckFront() {
  bool path_Clear = true;
  
  while (path_Clear == true) {
    Forward();
    Serial.println("pathclear");
    int Distance = Check_Front();
    delay(100);

    if (Distance < StopDistance) {
      path_Clear = false;
      Serial.println("ObjectDetected");
      Stop();
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Right_CheckRight() {
  bool path_Clear = true;
  
  while (path_Clear == true) {
    Right();
    Serial.println("pathclear");
    int Distance = Check_Right();
    delay(100);

    if (Distance < StopDistance) {
      path_Clear = false;
      Serial.println("ObjectDetected");
      Stop();
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
void Left_CheckLeft() {
  bool path_Clear = true;
  
  while (path_Clear == true) {
    Left();
    Serial.println("pathclear");
    int Distance = Check_Left();
    delay(100);

    if (Distance < StopDistance) {
      path_Clear = false;
      Serial.println("ObjectDetected");
      Stop();
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////
void Ultrasonic_FLRCheck() {
myservo.write(90); 
    //setservo position according to scaled value    
    delay(500);     
int    middleDistance = Distance_test();
    Serial.println(middleDistance);
    
    if (middleDistance <= StopDistance) {
      Stop();      
      delay(500);
                                     
      myservo.write(10);
      delay(1000);            
     int rightDistance = Distance_test();
      delay(500);
            
      myservo.write(90);
      delay(1000);
      
      myservo.write(180);                    
      delay(1000);
             
      int leftDistance = Distance_test();
      delay(500);
            
      myservo.write(90);                    
      delay(1000);
            
      if (rightDistance > leftDistance) {
        Right();
        delay(350);
        Stop();
      }      else if (rightDistance < leftDistance) {
        Left();
        delay(325);
        Stop();
      }      else if ((rightDistance <= StopDistance) || (leftDistance <= StopDistance)) {
        Back();
        delay(325);
        Stop();
      }
      else {
        Forward();
      }
    }      else {
      Forward();
    }
}

/******************************************************************* LINE TRACKER FUNCTIONS **************************************************************************/
void TrackLine_CheckFront() {
bool track = true;
while (track) {
  if (LT_M == HIGH && LT_R == HIGH && LT_L == HIGH) {
  Forward();
  }
  else if (LT_M == LOW) {
    Forward();
  }
  else if (LT_R == LOW) {
    Right();
    while (LT_M);
  }
  else if (LT_L == LOW) {
    Left();
    while (LT_M);
  }

    int Distance = Check_Front();
    if (Distance < StopDistance) {
      Stop();
      track=false;
    }
    
}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Forward_TrackLine() {
  bool track = true;
while (track) {
  if (LT_M == HIGH && LT_R == HIGH && LT_L == HIGH) {
  Forward();
  }
  else if (LT_M == LOW) {
    Forward();
  }
  else if (LT_R == LOW) {
    Right();
    while (LT_M);
  }
  else if (LT_L == LOW) {
    Left();
    while (LT_M);
  }
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Forward_TrackLine(int duration) {
long Start_Time = micros();
  Serial.println("Start");
  Serial.println(Start_Time);
  bool track = true;
  
  while (track) {
    long Current_Time = micros();
    long TimeDiff =(Current_Time-Start_Time)/1000;
    Serial.println(TimeDiff);
    if (TimeDiff < duration){
      if (LT_M == HIGH && LT_R == HIGH && LT_L == HIGH) {
      Forward();
      track=false;
      }
      else if (LT_M == LOW) {
        Forward();
      }
      else if (LT_R == LOW) {
        Right();
        while (LT_M);
      }
      else if (LT_L == LOW) {
        Left();
        while (LT_M);
      }
    }
    else {
      Stop();
      track = false;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TrackLine_Stop(long duration) {
  long Start_Time = micros();
  Serial.println("Start");
  Serial.println(Start_Time);
  bool track = true;
  
  while (track) {
    long Current_Time = micros();
    long TimeDiff =(Current_Time-Start_Time)/1000;
    Serial.println(TimeDiff);
    if (TimeDiff < duration){
      if (LT_M == HIGH && LT_R == HIGH && LT_L == HIGH) {
      Stop();
      track=false;
      }
      else if (LT_M == LOW) {
        Forward();
      }
      else if (LT_R == LOW) {
        Right();
        while (LT_M);
      }
      else if (LT_L == LOW) {
        Left();
        while (LT_M);
      }
    }
    else {
      Stop();
      track = false;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TrackLine_Stop() {
  bool track = true;
while (track) {
  if (LT_M == HIGH && LT_R == HIGH && LT_L == HIGH) {
  Stop();
  track=false;
  }
  else if (LT_M == LOW) {
    Forward();
  }
  else if (LT_R == LOW) {
    Right();
    while (LT_M);
  }
  else if (LT_L == LOW) {
    Left();
    while (LT_M);
  }
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TrackLine_Spin() {
  bool track = true;
  
while (track) {
  if (LT_M == HIGH && LT_R == HIGH && LT_L == HIGH) {
  Right();
  }
  else if (LT_M == LOW) {
    Forward();
  }
  else if (LT_R == LOW) {
    Right();
    while (LT_M);
  }
  else if (LT_L == LOW) {
    Left();
    while (LT_M);
  }
}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FindLine_Right(){
    bool track = true;
  
    while (track) {
      Right();
      if(LT_M == LOW){
         Stop();
         break;
       }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FindLine_Left(){
    bool track = true;
  
    while (track) {
      Left();
      if(LT_M == LOW){
         Stop();
         break;
       }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FindLine_Forward(){
    bool track = true;
  
    while (track) {
      Forward();
      if(LT_M == LOW || LT_R == LOW || LT_L == LOW){
         Stop();
         break;
       }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FindLine_Back(){
    bool track = true;
  
    while (track) {
      Back();
      if(LT_M == LOW || LT_R == LOW || LT_L == LOW){
         Stop();
         break;
       }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BoxTrap() {
bool trapped=true;

while(trapped){
  FindLine_Forward();
  Back(250);
  Right(250); 
}
 
}


