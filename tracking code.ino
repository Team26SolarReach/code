#include <Servo.h>
//#include <PWM.h>
Servo servoleftright;
Servo servoupdown;
#define servoPin 9
#define servoPin 11
//int pwm = 9;               
//int32_t frequency = 300;
void setup() {
  //InitTimersSafe(); 
  //bool success = SetPinFrequencySafe(pwm, frequency);
  int anglelr = 0;//angle left right
  int angleud = 0;//angle up down
  Serial.begin(9600);
  servoleftright.attach(9);
  servoupdown.attach(11);
  servoleftright.write(anglelr);
  servoupdown.write(angleud);
}
void loop() {
  int anglelr;
  int angleud;
  int right = analogRead(A0);
  int left = analogRead(A1);
  int upper = analogRead(A2);
  int lower = analogRead(A3);
  //pwmWrite(pwm, 127);
  //SET TOLERANCE HIGH WHEN THE ROOM IS NOT LIT WELL
  if (right>(left+100)){
    anglelr=anglelr+5;
    if(anglelr<0){
      anglelr=0;
    }
    else if(anglelr>180){
      anglelr=180;
    }
  }
  else if (left>(right+100)){
    anglelr=anglelr-5;
    if(anglelr<0){
      anglelr=0;
    }
    else if(anglelr>180){
      anglelr=180;
    }
  }
  else{
    anglelr=anglelr;
  }
  servoleftright.write(anglelr);
//upper and lower controls
  if (upper>(lower+100)){
    angleud=angleud+5;
    if(angleud<0){
      angleud=0;
    }
    else if(angleud>180){
      anglelr=180;
    }
  }
  else if (lower>(upper+100)){
    angleud=angleud-5;
    if(angleud<0){
      angleud=0;
    }
    else if(angleud>180){
      angleud=180;
    }
  }
  else{
    angleud=angleud;
  }
  servoupdown.write(angleud);  
  //DIAMOND PRINT
  Serial.print("          ");//five tabs
  Serial.print(upper);
  Serial.println();
  Serial.println(left);
  Serial.print("                    ");//ten tabs
  Serial.print(right);
  Serial.println("          ");
  Serial.print(lower);
  Serial.println('\n');
  Serial.print(anglelr);
  Serial.println();
  Serial.print(angleud);
  Serial.println();
  Serial.println();
  delay(250);
}