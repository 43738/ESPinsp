/*
 * Based on the arduino-audio-tools example
 * https://github.com/pschatzmann/arduino-audio-tools/tree/main/examples/examples-stream/streams-memory_mp3-analog
 *
 * :)
*/
#include "AudioTools.h"
#include "Inspiration.h"
#include "AudioTools/AudioCodecs/CodecMP3Helix.h"

// PIR out -> ESP32 16 motion sensor
const int motionSensor = 16;
int sensorValue;
boolean motion = false;

// Speaker -> GPIO 25/26
MemoryStream mp3(miracles_often_begin_on_mondays_mp3, miracles_often_begin_on_mondays_mp3_len);
AnalogAudioStream analog;
EncodedAudioStream out(&analog, new MP3DecoderHelix());
StreamCopy copier(out, mp3);

void setup() {
  // serial
  Serial.begin(115200);
  AudioToolsLogger.begin(Serial, AudioToolsLogLevel::Info);  

  // speaker
  analog.begin(analog.defaultConfig(TX_MODE));  
  out.begin();

  //motion sensor
  pinMode(motionSensor, INPUT);
}

void loop() {
  sensorValue = digitalRead(motionSensor);
  if(sensorValue == HIGH){
    Serial.println("MOTION DETECTED");

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
    Serial.println("NO MOTION");
    motion = false;
  }
  delay(200);
}


