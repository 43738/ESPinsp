/*
* :)
*/

// PIR out -> ESP32 16
const int motionSensor = 16;
int sensorValue;
boolean motion = false;

// void IRAM_ATTR detectsMovement() {
//   motion = true;
// }

void setup() {
  Serial.begin(115200);
  pinMode(motionSensor, INPUT);
  // attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);
}

void loop() {
  // if(motion) {
  //   Serial.println("MOTION DETECTED!!!");
  //   motion=false;
  // }
  sensorValue = digitalRead(motionSensor);
  if(sensorValue == HIGH){ Serial.println("YES"); }
  else{Serial.println("NO");}
  delay(200);
}

