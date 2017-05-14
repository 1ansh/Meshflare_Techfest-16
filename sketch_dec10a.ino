#include <QTRSensors.h>
#define Kp 0.085
#define Kd 2
#define rightMaxSpeed 180
#define leftMaxSpeed 180
#define rightBaseSpeed 34
#define leftBaseSpeed 34
#define TIMEOUT       2500
#define EMITTER_PIN   2
#define turn_speed 100
#define rightMotor1 8
#define rightMotor2 7
#define rightMotorPWM 10
#define leftMotor1 4
#define leftMotor2 5
#define leftMotorPWM 3
#define motorPower 6
QTRSensorsAnalog qtr((unsigned char[]) {0,1,2,3,4,5,6,7},8);

typedef struct///////////////////////////////////////////
{
	int x,y,angle,array[8];
}Node;
Node node[30];
Node dupnode[30];////////////////////////////////////////////

void setup() {
  for (int i = 0; i < 100; i++)
{
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
int a=0,k=0,x=0,y=0;
int angle=0;
int dup_angle=0;
int dir[8]={0};
long tim=0;
long unit_time=1000;
int firsttime=1;
int count=0;/////////////////////////////////////////////
node[0].x=0;
node[0].y=0;
node[0].angle=0;
dupnode[0].x=0;
dupnode[0].y=0;
dupnode[0].angle=0;
for(int i=0;i<8;i++)
{
  if(i==6)
  {
    node[0].array[i]=2;
  }
  if(i==2)
  {
    node[0].array[i]=10;
  }
  else
  {
    node[0].array[i]=0;
  }
}
dupnode[0].array=node[0].array;//////////////////////////////////////


void loop() {
  if(firsttime==1)
    {tim=millis();

    firsttime=0;}

dir[8]={0};

  digitalWrite(46,0);
digitalWrite(48,0);
digitalWrite(50,0);
digitalWrite(52,0);
qtr.read(sensors);
int position1= qtr.readLine(sensors,QTR_EMITTERS_ON,1);
int left=0,right=0,flag=0,straight=0,left_angled=0,right_angled=0;
if(sensors[1]>400 && sensors[6]>400 && sensors[3]>400 && sensors[4]>400)
{  uturn();

dir[6]=1;
   a=dup_angle%360;

   if (a>180)
     a=a-360;
   else if(a<=-180)
     a=a+360;
   k=a/45;
switch(k)
{
case -2: x-=dic(millis()-tim);
      break;
case -1:x-=dic(millis()-tim)*0.707;
       y+=dic(millis()-tim)*0.707;
       break;
case 0:y+=dic(millis()-tim);
      break;
case 1:x+=dic(millis()-tim)*0.707;
       y+=dic(millis()-tim)*0.707;
       break;
case 2: x+=dic(millis()-tim);
      break;
case 4:y-=dic(millis()-tim);
      break;
}

angle+=180;
tim=millis();
  }               //for U-turn
if(sensors[2]<200 && sensors[6] <200 )
{left=1;
 flag=1;
 forward();
 delay(2);  //BRRODA VERIFY
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
 qtr.read(sensors);
 if(sensors[2]<200 && sensors[6]<200)
{left=1;  // define
digitalWrite(52,1);
}
digitalWrite(46,1);} //set cnt 0
if(flag==1)
{ Serial.println(angle);
 while(1)
  {
qtr.read(sensors);
  forward();
  if(sensors[3]>400 && sensors[4]>400)
  break;
  if(sensors[0]>200 && sensors[7]>200)
  break;
  }
  delay(40);
  qtr.read(sensors);
  delay(5);  //faltu extra
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

if (sensors[0]>400 && sensors[1]>400 && sensors[2]>400 &&sensors[3]>400 && sensors[4]>400 && sensors[5]>400 && sensors[6]>400&& sensors[7]>400)
{
}
else
{straight=1;
digitalWrite(46,1);
  digitalWrite(48,1);
  digitalWrite(52,1);
  digitalWrite(50,1);
}
dir[0]=left;
dir[1]=left_angled;
dir[2]=straight;
dir[3]=right_angled;
dir[4]=right;
if ((dir[0]+dir[4]+dir[3]+dir[1])>0)
{
   Serial.println(dup_angle);
   a=dup_angle%360;
   Serial.println(a);
   if (a>180)
     a=a-360;
   else if(a<=-180)
     a=a+360;
   k=a/45;
   Serial.println(k);
switch(k)
{
case -2:Serial.println("case-90");
         Serial.println(angle);
         x-=dic(millis()-tim);
         break;
case -1:x-=dic((millis()-tim)*0.707);
       y+=dic((millis()-tim)*0.707);
       break;
case 0:Serial.println("case 0");
       Serial.println(angle);
       Serial.println("millis  tim");
   Serial.print(millis());
   Serial.print("\t");
   Serial.println(tim);
      y+=dic(millis()-tim);
      break;
case 1:x+=dic((millis()-tim)*0.707);
       y+=dic((millis()-tim)*0.707);
       break;
case 2:Serial.println("case +90");
       Serial.println(angle);
       x+=dic(millis()-tim);
      break;
case 4:y-=dic(millis()-tim);
      break;
}
}
if(left==1)
{leftturn();
angle-=90;
tim=millis();
}
else if(left_angled==1)
{leftchota();
angle-=45;
tim=millis();
}
else if(straight==1)
{
  tim=millis();
}
else if(right==1)
{rightturn();
angle+=90;
tim=millis();
}
else if(right_angled==1)
{rightchota();
angle+=45;
tim=millis();
}
}
position1= qtr.readLine(sensors,QTR_EMITTERS_ON,1);
int error = position1 - 3500;
  int motorSpeed = Kp * error + Kd * (error - lastError);
  motorSpeed/=8;
  lastError = error;
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
dup_angle+=angle;
  Serial.print(x);
  Serial.print("\t");
   Serial.print(y);
   Serial.print("\t");
   Serial.println(dup_angle);
}
void leftturn()
{
  digitalWrite(motorPower, HIGH);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
  analogWrite(rightMotorPWM, 25);
  digitalWrite(motorPower, HIGH);
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, HIGH);
  analogWrite(leftMotorPWM,25 );
  delay(300);    //DOUBLE CHECK BRODA
  qtr.readLine(sensors);
  while(sensors[2]>400)
  {qtr.readLine(sensors);
  }
  }
void rightturn()
{
  digitalWrite(motorPower, HIGH);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, HIGH);
  analogWrite(rightMotorPWM, 25);
  digitalWrite(motorPower, HIGH);
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  analogWrite(leftMotorPWM,25 );
  delay(300);    //DOUBLE CHECK BRODA
  qtr.readLine(sensors);
  while(sensors[2]>400)
  {qtr.readLine(sensors);
  }
  }
  void leftchota()
{
  digitalWrite(motorPower, HIGH);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
  analogWrite(rightMotorPWM, 25);
  digitalWrite(motorPower, HIGH);
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, HIGH);
  analogWrite(leftMotorPWM,25 );
  qtr.readLine(sensors);
  while(sensors[3]>400)
  {qtr.readLine(sensors);
  }
  }
void rightchota()
{
  digitalWrite(motorPower, HIGH);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, HIGH);
  analogWrite(rightMotorPWM, 25);
  digitalWrite(motorPower, HIGH);
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  analogWrite(leftMotorPWM,25 );
  qtr.readLine(sensors);
  while(sensors[2]>400)
  {qtr.readLine(sensors);
  }
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
  analogWrite(rightMotorPWM, 27);
  digitalWrite(motorPower, HIGH);
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  analogWrite(leftMotorPWM,27 );
  qtr.readLine(sensors);
  while(sensors[2]>400)
  {qtr.readLine(sensors);
  }
    }
int dic(double t)
{ int ans;
    float p = t/unit_time;
    Serial.println(p);
  if(p>0)
    ans=int(p+0.5);
  if(p<0)
    ans=int(p-0.5);
    Serial.println("fn hua call");
    Serial.println(ans);
    delay(1000);
return ans;
}
