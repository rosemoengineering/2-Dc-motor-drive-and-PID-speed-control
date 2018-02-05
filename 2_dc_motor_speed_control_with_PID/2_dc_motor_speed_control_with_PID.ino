#include<Encoder.h> // Adding encoder library
#include <PID_v1.h> // Add PID library

Encoder left_enc(2,0); // Left dc motor encoder output pin is 2.
Encoder right_enc(5,0); //Right dc motor encoder output pin is 5.
const int PWMA = 9;  // TB6612FNG dc motor driver pins
const int AIN1 = 11;
const int AIN2 = 10;
const int STBY = 12;
const int BIN1 = 6;
const int BIN2 = 7;
const int PWMB = 3;
double Setpoint, Input, Output;
//PID gain parameters
double Kp1=0.185, Ki1=0.875, Kd1=0.0125;
PID myPID1(&Input, &Output, &Setpoint, Kp1, Ki1, Kd1, DIRECT);


void setup() {
 float Input1  = 0;
  float Input2 = 0;
  Setpoint = 100; // Desired RPM values

  //turn the PID on
  myPID1.SetMode(AUTOMATIC);

  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Starting...");
  pinMode(PWMA,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(PWMB,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
  pinMode(STBY,OUTPUT);
  digitalWrite(STBY,HIGH);
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,HIGH);
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,HIGH);

}
//right dc motor is A left dc motor is B.
float start;
float start_2;
float stop_2=0;
float diff_2;
float stop_=0;
float diff;
float rpm = 0;
float rpm2=0;
long oldPosition  = -999;
long oldPosition2 = -999;
int counter=0;
int counter2 = 0;
int dev;
int pwm=150;
int PWM_B;
int PWM_A;
void loop() {
  start = millis();

  long newPosition = right_enc.read();
  
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    counter++;
    if(counter%40==0){
      diff = start-stop_;
      rpm=1/(diff/60000);
      stop_=start;
  Serial.print("right :\t");Serial.print(rpm);
       Serial.println();
      }
  }
    long newPosition2 = left_enc.read();
    start_2 = millis();
 
  if(newPosition2!=oldPosition2){
    oldPosition2 = newPosition2;
    counter2++;

    if(counter2%40==0){
       
      diff_2=start_2-stop_2;
      
      rpm2=1/(diff_2/60000);
      stop_2=start_2;
   Serial.print("left : \t");Serial.print(rpm2);
    Serial.println();
      }
    
    
    }
  
   left(rpm2);
   right(rpm);   

  analogWrite(PWMB,PWM_B);
  analogWrite(PWMA, PWM_A);
}

void right(int input_1 )
{
  Input = input_1;
  myPID1.Compute();
  PWM_B=Output;

}
 

void left(int input_2 )
{
  Input = input_2;
  myPID1.Compute();
  PWM_A=Output;

}

