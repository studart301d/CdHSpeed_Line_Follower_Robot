#define BLACK   0
#define WHITE   1
#define FULL    255
#define MIN     150 

/*#################### SENSORS SETUP ####################*/
int SensorMatrix[5] = {0,0,0,0,0} //Sensor matrix for measuring the IR sensor 
int LFsensor0 = 2;
int LFsensor1 = 3;
int LFsensor2 = 4;
int LFsensor3 = 5;
int LFsensor4 = 6;

/*/*#################### MOTORS SETUP ####################*/
int motorLEFT-1 = 9;
int motorLEFT-0 = 10;
int motorRIGHT-1 = 11;
int motorRIGHT-0 = 12;


void setup() {
  // put your setup code here, to run once:
  pinMode (LFsensor0, INPUT);
  pinMode (LFsensor1, INPUT);
  pinMode (LFsensor2, INPUT);
  pinMode (LFsensor3, INPUT);
  pinMode (LFsensor4, INPUT);

  pinMode (motorLEFT-1, OUTPUT);
  pinMode (motorLEFT-0, OUTPUT);

  pinMode (motorRIGHT-1, OUTPUT);
  pinMode (motorRIGHT-1, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

}



void Motor(int motorPin1, int motorPin0, int velocity){
   analogWrite(motorPin1, velocity);
   analogWrite(motorPin0, 0); 
}

void motorPIDcontrol()
{
  
  int leftMotorSpeed = 1500 - iniMotorPower - PIDvalue;
  int rightMotorSpeed = 1500 + iniMotorPower*adj - PIDvalue;
  
  // The motor speed should not exceed the max PWM value
   constrain(leftMotorSpeed, 1000, 2000);
   constrain(rightMotorSpeed, 1000, 2000);
  
  leftServo.writeMicroseconds(leftMotorSpeed);
  rightServo.writeMicroseconds(rightMotorSpeed);
  
  //Serial.print (PIDvalue);
  //Serial.print (" ==> Left, Right:  ");
  //Serial.print (leftMotorSpeed);
  //Serial.print ("   ");
  //Serial.println (rightMotorSpeed);
}
