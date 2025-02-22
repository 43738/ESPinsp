/*
* :)
*/
#include "AudioTools.h"
//#include "BabyElephantWalk60_mp3.h"
#include "Inspiration.h"
#include "AudioTools/AudioCodecs/CodecMP3Helix.h"

//#define MP3_MAX_OUTPUT_SIZE 1024 * 10
//#define DEFAULT_BUFFER_SIZE 1024*10

// PIR out -> ESP32 16 motion sensor
const int motionSensor = 16;
int sensorValue;
boolean motion = false;

// Speaker -> GPIO 26
MemoryStream mp3(miracles_often_begin_on_mondays_mp3, miracles_often_begin_on_mondays_mp3_len);
//MemoryStream mp3(BabyElephantWalk60_mp3, BabyElephantWalk60_mp3_len);
AnalogAudioStream analog;  // Analog output 
EncodedAudioStream out(&analog, new MP3DecoderHelix()); // output to decoder
StreamCopy copier(out, mp3);    // copy in to out

// void IRAM_ATTR detectsMovement() {
//   motion = true;
// }

void setup() {
  // serial
  Serial.begin(115200);
  AudioToolsLogger.begin(Serial, AudioToolsLogLevel::Info);  

  // speaker
  analog.begin(analog.defaultConfig(TX_MODE));  
  out.begin();

  //motion sensor
  pinMode(motionSensor, INPUT);
  // attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);
}

void loop() {
  // if(motion) {
  //   Serial.println("MOTION DETECTED!!!");
  //   motion=false;
  // }
  sensorValue = digitalRead(motionSensor);
  if(sensorValue == HIGH){
    Serial.println("DETECTED");

    if (mp3) {
      if(!motion){
        while(mp3) copier.copy();
        motion = true;
        mp3.begin();
      }
    } else {
      auto info = out.decoder().audioInfo();
      LOGI("The audio rate from the mp3 file is %d", info.sample_rate);
      LOGI("The channels from the mp3 file is %d", info.channels);
      out.end();
      stop();
    }
  }
  else{
    Serial.println("NO");
    motion = false;
  }
  delay(200);
}


