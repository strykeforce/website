//www.elegoo.com
#include <Servo.h>  
//servo library 
Servo myservo;      
// create servo object to control servo
int Echo = A4;  
int Trig = A5;
#define carspeed 125
int stopDistance = carspeed/5;
int sideDistance = 20;
int rightDistance = 0, leftDistance = 0, middleDistance = 0;

/*define logic control output pin*/ //RIGHT Motor //in4 in3 define motor direction for Right Motor 
int in4=6; 
int in3=7;
//Left Motor //in2 in1 define motor direction for Left Motor 
int in2=8;
int in1=9;
/*define channel enable output pins*/ //ENA ENB Used for PWM control set both to HIGH for full Speed 
int ENB=5; 
int ENA=10;
/*define stop function*/ 
void stop() {
  digitalWrite(ENA, carspeed);  
  digitalWrite(ENB, carspeed);
  //RIGHT Motor Spin Forward  
  digitalWrite(in4,LOW);
  //digital output  
  digitalWrite(in3,LOW);
  //Left Motor Spin Forward  
  digitalWrite(in2,LOW);  
  digitalWrite(in1,LOW);
  Serial.println("STOP");
}
/*define forward function*/ 
void forward() {
  digitalWrite(ENA, carspeed);  
  digitalWrite(ENB, carspeed);
  //RIGHT Motor Spin Forward  
  digitalWrite(in4,HIGH);
  //digital output  
  digitalWrite(in3,LOW);
  //Left Motor Spin Forward  
  digitalWrite(in2,HIGH);  
  digitalWrite(in1,LOW);
  Serial.println("Forward");
}
/*define back function*/ 
void back() {
  digitalWrite(ENA, carspeed);
  digitalWrite(ENB, carspeed);
  //RIGHT Motor Spin Backward  
  digitalWrite(in4,LOW);
  //digital output  
  digitalWrite(in3,HIGH);
  //Left Motor Spin Backward 
  digitalWrite(in2,LOW);  
  digitalWrite(in1,HIGH);
  Serial.println("Back");
  
} /*define left function*/ 
void left() {
  digitalWrite(ENA, carspeed); 
  digitalWrite(ENB, carspeed);
  //RIGHT Motor Spin Backward  
  digitalWrite(in4,LOW);
  //digital output  
  digitalWrite(in3,HIGH);
  //Left Motor Spin Forward
  digitalWrite(in2, HIGH);  
  digitalWrite(in1, LOW);
  Serial.println("Left");
}
/*define right function*/ 
void right() {
  digitalWrite(ENA, carspeed);  
  digitalWrite(ENB, carspeed);
  //RIGHT Motor Spin Forward  
  digitalWrite(in4,HIGH);
  //digital output  
  digitalWrite(in3,LOW);
  //Left Motor Spin Backward  
  digitalWrite(in2,LOW);  
  digitalWrite(in1,HIGH);
  Serial.println("Back");  
  Serial.println("Right");
}

//Ultrasonic distance measurement Sub function
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

void setup() {
  myservo.attach(3);  // attach servo on pin 3 to servo object  
  Serial.begin(9600);
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  stop(); 
  }
  
  void loop() {
    myservo.write(90); 
    //setservo position according to scaled value    
    delay(500);     
    middleDistance = Distance_test();
    
    if (middleDistance <= stopDistance) {
      stop();      
      delay(500);
                                     
      myservo.write(10);
      delay(1000);            
      rightDistance = Distance_test();
      delay(500);
            
      myservo.write(90);
      delay(1000);
      
      myservo.write(180);                    
      delay(1000);
             
      leftDistance = Distance_test();
      delay(500);
            
      myservo.write(90);                    
      delay(1000);
            
      if (rightDistance > leftDistance) {
        right();
        delay(350);
        stop();
      }      else if (rightDistance < leftDistance) {
        left();
        delay(325);
        stop();
      }      else if ((rightDistance <= sideDistance) || (leftDistance <= sideDistance)) {
        back();
        delay(325);
        stop();
      }
      else {
        forward();
      }
    }      else {
      forward();
    }
  }
