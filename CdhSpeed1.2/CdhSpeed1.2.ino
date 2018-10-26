#define WHITE   1
#define BLACK   0
#define CROSSING_LINE 0
#define FOLLOWING_LINE 1
#define NO_LINE 2
#define DEGREETURN90 0 //UNSOLVED 
#define FULL    190
#define MIN     80

/* read line sensors values 

Sensor Array   Error Value
0 0 0 0 1  4              
0 0 0 1 1  3              
0 0 0 1 0  2              
0 0 1 1 0  1              
0 0 1 0 0  0              
0 1 1 0 0 -1              
0 1 0 0 0 -2              
1 1 0 0 0 -3
*/

int mode;
int pushButton = 13;
/*#################### SENSORS SETUP ####################*/
int SensorMatrix[5] = {0,0,0,0,0}; //Sensor matrix for measuring the IR sensor 
int LFsensor0 = 2;
int LFsensor1 = 3;
int LFsensor2 = 4;
int LFsensor3 = 5;
int LFsensor4 = 6;

/*#################### MOTORS SETUP ####################*/
int baseMotorSpeed = 100;
int rightMotorSpeed;
int leftMotorSpeed; 

int motorLEFT_1 = 9; //
int motorLEFT_0 = 10; //

int motorRIGHT_1 = 11;
int motorRIGHT_0 = 12;

/*#################### PDI Control####################*/
int error;
int previousError;
int Kp = 25;
int Kd = 0;
int Ki = 0;
int P, I, D;
int PIDvalue;

void readLFsensor();
void motorPIDControl();
void readLFsensor();
void calculatePID();
void motorForward();
void motorStop();
/*#################### Button Control ####################*/
int state = LOW;
int readBtt;
int before = HIGH;
int timer  = 0;
int debounce = 200;

void setup() {
  // put your setup code here, to run once:
  pinMode (LFsensor0, INPUT);
  pinMode (LFsensor1, INPUT);
  pinMode (LFsensor2, INPUT);
  pinMode (LFsensor3, INPUT);
  pinMode (LFsensor4, INPUT);

  pinMode (motorLEFT_1, OUTPUT);
  pinMode (motorLEFT_0, OUTPUT);

  pinMode (motorRIGHT_1, OUTPUT);
  pinMode (motorRIGHT_1, OUTPUT);

  pinMode(pushButton, INPUT_PULLUP);//button
  Serial.begin(9600);
}

void loop() {
    readBtt = digitalRead(pushButton);
    if((readBtt == HIGH) && (before == LOW )&&  (millis() - timer > debounce)){
      if(state == HIGH){
          state =  LOW;        
      }
      else{
          state = HIGH; 
      }      
      timer = millis();  
    }
    if(state){
          readLFsensor();  
          switch(mode){
            case FOLLOWING_LINE:
              calculatePID();
              motorPIDControl();
            break;
            case CROSSING_LINE:
              motorForward();
              previousError = 0; //Dunno
            case NO_LINE:
              motorForward();
              previousError = 0; //Dunno
          }
          Serial.println("Deu certo");
    }else{
        motorStop();
          Serial.println("N deu certo");
    }
    before = readBtt;
}



void motorPIDControl(){
  /*------------- Motor Speed ----------------*/
  rightMotorSpeed = baseMotorSpeed - PIDvalue;
  leftMotorSpeed = baseMotorSpeed + PIDvalue;


  rightMotorSpeed = constrain(rightMotorSpeed, MIN, FULL);
  leftMotorSpeed = constrain(leftMotorSpeed, MIN, FULL);

  analogWrite(motorLEFT_1, leftMotorSpeed);
  analogWrite(motorLEFT_0, 0);

  analogWrite(motorRIGHT_1, rightMotorSpeed);
  analogWrite(motorRIGHT_0, 0);
}
void motorForward(){
  analogWrite(motorLEFT_1, baseMotorSpeed);
  analogWrite(motorLEFT_0, 0);

  analogWrite(motorRIGHT_1, baseMotorSpeed);
  analogWrite(motorRIGHT_0, 0);
}

void readLFsensor(){
  //------------- LÊ SENSORES ----------------*/
  SensorMatrix[0] = digitalRead(LFsensor0);
  SensorMatrix[1] = digitalRead(LFsensor1);
  SensorMatrix[2] = digitalRead(LFsensor2);
  SensorMatrix[3] = digitalRead(LFsensor3);
  SensorMatrix[4] = digitalRead(LFsensor4);

  if((SensorMatrix[0] == WHITE) && (SensorMatrix[1] == WHITE) && (SensorMatrix[2] == WHITE) && (SensorMatrix[3] == WHITE) && (SensorMatrix[4] == BLACK)){
      mode = FOLLOWING_LINE;
      error = 4;
  } else if ((SensorMatrix[0] == WHITE) && (SensorMatrix[1] == WHITE) && (SensorMatrix[2] == WHITE) && (SensorMatrix[3] == BLACK) && (SensorMatrix[4] == BLACK)){
      mode = FOLLOWING_LINE;
      error = 3;
  } else if ((SensorMatrix[0] == WHITE) && (SensorMatrix[1] == WHITE) && (SensorMatrix[2] == WHITE) && (SensorMatrix[3] == BLACK) && (SensorMatrix[4] == WHITE)){
      mode = FOLLOWING_LINE;
      error = 2;
  } else if ((SensorMatrix[0] == WHITE) && (SensorMatrix[1] == WHITE) && (SensorMatrix[2] == BLACK) && (SensorMatrix[3] == BLACK) && (SensorMatrix[4] == WHITE)){
      mode = FOLLOWING_LINE;
      error = 1;
  } else if ((SensorMatrix[0] == WHITE) && (SensorMatrix[1] == WHITE) && (SensorMatrix[2] == BLACK) && (SensorMatrix[3] == WHITE) && (SensorMatrix[4] == WHITE)){
      mode = FOLLOWING_LINE;
      error = 0;
  } else if ((SensorMatrix[0] == WHITE) && (SensorMatrix[1] == BLACK) && (SensorMatrix[2] == BLACK) && (SensorMatrix[3] == WHITE) && (SensorMatrix[4] == WHITE)){
      mode = FOLLOWING_LINE;
      error = -1;
  } else if ((SensorMatrix[0] == WHITE) && (SensorMatrix[1] == BLACK) && (SensorMatrix[2] == WHITE) && (SensorMatrix[3] == WHITE) && (SensorMatrix[4] == WHITE)){
      mode = FOLLOWING_LINE;
      error = -2;
  } else if ((SensorMatrix[0] == BLACK) && (SensorMatrix[1] == BLACK) && (SensorMatrix[2] == WHITE) && (SensorMatrix[3] == WHITE) && (SensorMatrix[4] == WHITE)){
      mode = FOLLOWING_LINE;
      error = -3;
  } else if ((SensorMatrix[0] == BLACK) && (SensorMatrix[1] == WHITE) && (SensorMatrix[2] == WHITE) && (SensorMatrix[3] == WHITE) && (SensorMatrix[4] == WHITE)){
      mode = FOLLOWING_LINE;
      error = -4;
  }else if ((SensorMatrix[0] == WHITE) && (SensorMatrix[1] == WHITE) && (SensorMatrix[2] == WHITE) && (SensorMatrix[3] == WHITE) && (SensorMatrix[4] == WHITE)){
      mode = NO_LINE;
      error = 0;
  }else if ((SensorMatrix[0] == BLACK) && (SensorMatrix[1] == BLACK) && (SensorMatrix[2] == BLACK) && (SensorMatrix[3] == BLACK) && (SensorMatrix[4] == BLACK)){
      mode = CROSSING_LINE;
      error = 0;
  }
}
void motorStop(){
  analogWrite(motorLEFT_1, 0);
  analogWrite(motorLEFT_0, 0);

  analogWrite(motorRIGHT_1, 0);
  analogWrite(motorRIGHT_0, 0);
}
void calculatePID(){
  P = error;
  I = I + error;
  D = error-previousError;
  PIDvalue = (Kp*P) + (Ki*I) + (Kd*D);
  previousError = error;
}



