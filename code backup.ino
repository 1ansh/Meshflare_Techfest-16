#include <QTRSensors.h> 


#define Kp 0.085
#define Kd 2 // experiment to determine this, slowly increase the speeds and adjust this value. ( Note: Kp < Kd) 
#define rightMaxSpeed 180 // max speed of the robot
#define leftMaxSpeed 180 // max speed of the robot
#define rightBaseSpeed 32 // this is the speed at which the motors should spin when the robot is perfectly on the line
#define leftBaseSpeed 32// this is the speed at which the motors should spin when the robot is perfectly on the line
#define NUM_SENSORS  6     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 us for sensor outputs to go low
#define EMITTER_PIN   2     // emitter is controlled by digital pin 2
#define turn_speed 100

#define rightMotor1 8
#define rightMotor2 7
#define rightMotorPWM 10
#define leftMotor1 4
#define leftMotor2 5
#define leftMotorPWM 3
#define motorPower 6

QTRSensorsAnalog qtr((unsigned char[]) {0,1,2,3,4,5,6,7}, 8);
void setup() {
  
  // put your setup code here, to run once:

  for (int i = 0; i < 100; i++)  
{
  /* comment this part out for automatic calibration 
  if ( i  < 25 || i >= 75 ) // turn to the left and right to expose the sensors to the brightest and darkest readings that may be encountered
     turn_right();  
   else
     turn_left(); */ 
   qtr.calibrate();   
  delay(20);
  }
Serial.begin (9600);

pinMode(46,OUTPUT);
pinMode(48,OUTPUT);
pinMode(50,OUTPUT);
pinMode(52,OUTPUT);
digitalWrite(46,0);
digitalWrite(48,0);
digitalWrite(50,0);
digitalWrite(52,0);


}

unsigned int sensors[8];
int lastError = 0;
int count =0;
int grid=0;
void loop() {

  digitalWrite(46,0);
digitalWrite(48,0);
digitalWrite(50,0);
digitalWrite(52,0);
  // put your main code here, to run repeatedly:


qtr.read(sensors);
//int position1 = qtr.readLine(sensors);
//unsigned int readLine(unsigned int *sensorValues, unsigned char readMode = QTR_EMITTERS_ON, unsigned char whiteLine = 0)
int position1= qtr.readLine(sensors,QTR_EMITTERS_ON,1);
int left=0,right=0,flag=0,straight=0,left_angled=0,right_angled=0;

if(sensors[1]>400 && sensors[6]>400 && sensors[3]>400 && sensors[4]>400)
{ uturn();
  }               //for U-turn


if(sensors[2]<200 && sensors[6] <200 )
{left=1;
 flag=1;
 forward();
 delay(2);  //BRRODA VERIFY

// stop_normal();
 qtr.read(sensors);
 if(sensors[1]<200 && sensors[5]<200)
{right=1;  // define
digitalWrite(46,1);
}
 
  digitalWrite(52,1);
}

if(sensors[1]<200 && sensors[5]<200)
{right=1;  // define
flag=1;
 forward();
 delay(2);  //BRRODA VERIFY

// stop_normal();
 qtr.read(sensors);
 if(sensors[2]<200 && sensors[6]<200)
{left=1;  // define
digitalWrite(52,1);
}
digitalWrite(46,1);} //set cnt 0


if(flag==1)
{ //impulse_stop();
 // while((sensors[3]<200 || sensors[4]<200) && (sensors[0]<200 || sensors[5]<200))
 while(1)
  {
qtr.read(sensors);
  forward();
  if(sensors[3]>400 && sensors[4]>400)
  break;
  if(sensors[0]>200 && sensors[7]>200)
  break;
  Serial.print(sensors[1]);
  Serial.print('\t');
  Serial.println(sensors[6]);
  }
  delay(40);
  qtr.read(sensors);
  delay(5);  //faltu extra
  //stop_normal();
  impulse_stop(); 
  
  
if(sensors[7]<200)
{left_angled=1;
left=0;
digitalWrite(52,0);
digitalWrite(50,1);
}

if(sensors[0]<200)
{right_angled=1;
right=0;
digitalWrite(48,1);
digitalWrite(46,0);
}
if((sensors[3]<200 || sensors[4]<200) && sensors[1]>200 && sensors[6]>200 )
{
  straight=1;
  digitalWrite(46,1);
  digitalWrite(48,1);
  digitalWrite(52,1);
  digitalWrite(50,1);

}


if(left==1)
{leftturn();
}

else if(left_angled==1)
{leftchota();
}

else if(straight==1)
{
}
else if(right==1)
{rightturn();
}

else if(right_angled==1)
{rightchota();
}

}









int error = position1 - 3500;
 //Serial.println(position1);

  int motorSpeed = Kp * error + Kd * (error - lastError);
  motorSpeed/=8;
  lastError = error;
  /*for (unsigned char i = 0; i <6; i++)
  {
    Serial.print(sensors[i]);
    Serial.print('\t'); // tab to format the raw data into columns in the Serial monitor
  }
  Serial.println();
  */
  
  int rightMotorSpeed = rightBaseSpeed + motorSpeed;
  int leftMotorSpeed = leftBaseSpeed - motorSpeed;
    if (rightMotorSpeed > rightMaxSpeed ) rightMotorSpeed = rightMaxSpeed; // prevent the motor from going beyond max speed
  if (leftMotorSpeed > leftMaxSpeed ) leftMotorSpeed = leftMaxSpeed; // prevent the motor from going beyond max speed
  if (rightMotorSpeed < 0) rightMotorSpeed = 0; // keep the motor speed positive
  if (leftMotorSpeed < 0) leftMotorSpeed = 0;


  digitalWrite(motorPower, HIGH); // move forward with appropriate speeds
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
  analogWrite(rightMotorPWM, rightMotorSpeed);
  //analogWrite(rightMotorPWM, 100);
  digitalWrite(motorPower, HIGH);
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  analogWrite(leftMotorPWM, leftMotorSpeed);
 //analogWrite(leftMotorPWM, 100);
  
  
}




//fn for left turn
void leftturn()
{
  digitalWrite(motorPower, HIGH); 
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
  analogWrite(rightMotorPWM, 22);
  digitalWrite(motorPower, HIGH);
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, HIGH);
  
  analogWrite(leftMotorPWM,22 );
  delay(250);    //DOUBLE CHECK BRODA
  qtr.readLine(sensors);
  while(sensors[2]>400)
  {qtr.readLine(sensors);
  }
  //stop_normal();
 
  }
  
  


//fn for right turn
void rightturn()
{
  digitalWrite(motorPower, HIGH); 
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, HIGH);
  analogWrite(rightMotorPWM, 22);
  digitalWrite(motorPower, HIGH);
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  analogWrite(leftMotorPWM,22 );
  delay(250);    //DOUBLE CHECK BRODA
  qtr.readLine(sensors);
  while(sensors[2]>400)
  {qtr.readLine(sensors);
  }
  //stop_normal();
  }  

//fn for 135 left
  void leftchota()
{
  digitalWrite(motorPower, HIGH); 
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
  analogWrite(rightMotorPWM, 22);
  digitalWrite(motorPower, HIGH);
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, HIGH);
  
  analogWrite(leftMotorPWM,22 );
  qtr.readLine(sensors);
  while(sensors[3]>400)
  {qtr.readLine(sensors);
  }
  //stop_normal();
 
  }

  //fn for right turn
void rightchota()
{
  digitalWrite(motorPower, HIGH); 
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, HIGH);
  analogWrite(rightMotorPWM, 22);
  digitalWrite(motorPower, HIGH);
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  analogWrite(leftMotorPWM,22 );
  
  qtr.readLine(sensors);
  while(sensors[2]>400)
  {qtr.readLine(sensors);
  }
  //stop_normal();
  } 


  void forward()
  {digitalWrite(motorPower, HIGH); // move forward with appropriate speeds
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
  analogWrite(rightMotorPWM, 28);

  digitalWrite(motorPower, HIGH);
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  analogWrite(leftMotorPWM, 25);
 // delay(50);


  
  }

  void impulse_stop()
  {
    digitalWrite(motorPower, HIGH); // move forward with appropriate speeds
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, HIGH);
  analogWrite(rightMotorPWM, 100);

  digitalWrite(motorPower, HIGH);
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, HIGH);
  analogWrite(leftMotorPWM, 100);
  delay(10);

  digitalWrite(motorPower, HIGH); // move forward with appropriate speeds
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);
  analogWrite(rightMotorPWM, 0);
 
  digitalWrite(motorPower, HIGH);
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  analogWrite(leftMotorPWM, 0);
  delay(50); //to pause
    
  
  }

  void stop_normal()
  {
     digitalWrite(motorPower, HIGH); // move forward with appropriate speeds
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);
  analogWrite(rightMotorPWM, 0);

  digitalWrite(motorPower, HIGH);
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  analogWrite(leftMotorPWM, 0);
    
  delay(50); //to pause
  }

  void uturn()
  {
    digitalWrite(motorPower, HIGH); 
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, HIGH);
  analogWrite(rightMotorPWM, 22);
  digitalWrite(motorPower, HIGH);
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  
  analogWrite(leftMotorPWM,22 );
  delay(250);    //DOUBLE CHECK BRODA
  qtr.readLine(sensors);
  while(sensors[2]>400)
  {qtr.readLine(sensors);
  }
    }


 