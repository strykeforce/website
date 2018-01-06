//2017.09.06

//Line Tracking IO define
#define LT_R !digitalRead(2)
#define LT_M !digitalRead(4)
#define LT_L !digitalRead(11)

#define carspeed 125
/*define logic control output pin*/
//RIGHT Motor
//in4 in3 define motor direction for Right Motor
int in4=6; 
int in3=7;

//Left Motor
//in2 in1 define motor direction for Left Motor
int in2=8;
int in1=9;

/*define channel enable output pins*/
//ENA ENB Used for PWM control set both to HIGH for full Speed
int ENB=5;
int ENA=10;

/*define stop function*/
void _mSTOP()
{ 
  analogWrite(ENA,carspeed);
  analogWrite(ENB,carspeed);

  //RIGHT Motor Spin Forward
  digitalWrite(in4,LOW);//digital output
  digitalWrite(in3,LOW);

  //Left Motor Spin Forward
  digitalWrite(in2,LOW);
  digitalWrite(in1,LOW);
  
  Serial.println("STOP");
}

/*define forward function*/
void _mForward()
{ 
  analogWrite(ENA,carspeed);
  analogWrite(ENB,carspeed);

  //RIGHT Motor Spin Forward
  digitalWrite(in4,HIGH);//digital output
  digitalWrite(in3,LOW);

  //Left Motor Spin Forward
  digitalWrite(in2,HIGH);
  digitalWrite(in1,LOW);
  
  Serial.println("Forward");
}

/*define back function*/
void _mBack()
{
  analogWrite(ENA,carspeed);
  analogWrite(ENB,carspeed);
  
  //RIGHT Motor Spin Backward
  digitalWrite(in4,LOW);//digital output
  digitalWrite(in3,HIGH);

  //Left Motor Spin Backward
  digitalWrite(in2,LOW);
  digitalWrite(in1,HIGH);
  
  Serial.println("Back");
}
/*define left function*/
void _mleft()
{
  analogWrite(ENA,carspeed);
  analogWrite(ENB,carspeed);
  
  //RIGHT Motor Spin Backward
  digitalWrite(in4,LOW);//digital output
  digitalWrite(in3,HIGH);

  //Left Motor Spin Forward
  digitalWrite(in2,HIGH);
  digitalWrite(in1,LOW);
  
  Serial.println("Left");
}
/*define right function*/
void _mright()
{
  analogWrite(ENA,carspeed);
  analogWrite(ENB,carspeed);
  
  //RIGHT Motor Spin Forward
  digitalWrite(in4,HIGH);//digital output
  digitalWrite(in3,LOW);

  //Left Motor Spin Backward
  digitalWrite(in2,LOW);
  digitalWrite(in1,HIGH);
  
  Serial.println("Back");
  Serial.println("Right");
}
/*put your setup code here, to run once*/
void setup() {
 Serial.begin(9600); //Open the serial port and set the baud rate to 9600
/*Set the defined pins to the output*/
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
}
/*put your main code here, to run repeatedly*/
void loop() {
  if(LT_M == LOW){
    _mForward();
  }
  else if(LT_R == LOW) {
    _mright();
    while(LT_M);
  }
  else if(LT_L == LOW) {
    _mleft();
    while(LT_M);
  }
}
