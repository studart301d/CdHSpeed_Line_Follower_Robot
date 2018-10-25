int SensorMatrix[5] = {0,0,0,0,0}; //Sensor matrix for measuring the IR sensor 
int LFsensor0 = 2;
int LFsensor1 = 3;
int LFsensor2 = 4;
int LFsensor3 = 5;
int LFsensor4 = 6;

void readLFsensor();
void setup() {
  pinMode(LFsensor0, INPUT);
  pinMode(LFsensor1, INPUT);
  pinMode(LFsensor2, INPUT);
  pinMode(LFsensor3, INPUT);
  pinMode(LFsensor4, INPUT);  
  Serial.begin(9600);

  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  readLFsensor();
  Serial.print(SensorMatrix[0]);
  Serial.print(" ");
  Serial.print(SensorMatrix[1]);
    Serial.print(" ");
  Serial.print(SensorMatrix[2]);
    Serial.print(" ");
  Serial.print(SensorMatrix[3]);
    Serial.print(" ");
  Serial.println(SensorMatrix[4]);
  delay(400);
}

void readLFsensor(){
  //------------- LÊ SENSORES ----------------*/
  SensorMatrix[0] = digitalRead(LFsensor0);
  SensorMatrix[1] = digitalRead(LFsensor1);
  SensorMatrix[2] = digitalRead(LFsensor2);
  SensorMatrix[3] = digitalRead(LFsensor3);
  SensorMatrix[4] = digitalRead(LFsensor4);
}
