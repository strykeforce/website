//Motor Test 
// 09/07/2017

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
int carspeed = 125;
int turnDelayLeft = 325;
int turnDelayRight = 350;
/*define stop function*/
void stop()
{ 
  digitalWrite(ENA,carspeed);
  digitalWrite(ENB,carspeed);

  //RIGHT Motor Spin Forward
  digitalWrite(in4,LOW);//digital output
  digitalWrite(in3,LOW);

  //Left Motor Spin Forward
  digitalWrite(in2,LOW);
  digitalWrite(in1,LOW);
  
  Serial.println("STOP");
}

/*define forward function*/
void forward()
{ 
  digitalWrite(ENA,carspeed);
  digitalWrite(ENB,carspeed);

  //RIGHT Motor Spin Forward
  digitalWrite(in4,HIGH);//digital output
  digitalWrite(in3,LOW);

  //Left Motor Spin Forward
  digitalWrite(in2,HIGH);
  digitalWrite(in1,LOW);
  
  Serial.println("Forward");
}

/*define back function*/
void back()
{
  digitalWrite(ENA,carspeed);
  digitalWrite(ENB,carspeed);
  
  //RIGHT Motor Spin Backward
  digitalWrite(in4,LOW);//digital output
  digitalWrite(in3,HIGH);

  //Left Motor Spin Backward
  digitalWrite(in2,LOW);
  digitalWrite(in1,HIGH);
  
  Serial.println("Back");
}
/*define left function*/
void left()
{
  digitalWrite(ENA,carspeed);
  digitalWrite(ENB,carspeed);
  
  //RIGHT Motor Spin Backward
  digitalWrite(in4,LOW);//digital output
  digitalWrite(in3,HIGH);

  //Left Motor Spin Forward
  digitalWrite(in2,HIGH);
  digitalWrite(in1,LOW);
  
  Serial.println("Left");
}
/*define right function*/
void right()
{
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  
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
stop();
delay(500);

forward();
delay(1000);
stop();
delay(500);

back();
delay(1000);
stop();
delay(500);

left();
delay(turnDelayLeft);
stop();
delay(1000);

right();
delay(turnDelayRight);
stop();
delay(1000);
}
