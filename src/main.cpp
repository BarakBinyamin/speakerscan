#include <Arduino.h>
#include "AudioTools.h"
#include "AudioLibs/AudioA2DP.h"

#define LED_PIN LED_BUILTIN
#define SPEAKER_LIST_SIZE    30
#define SCAN_DURATION        5000

Speakers speakers;                                        // Added to BluetoothA2DPSource.h in speakers/speakers.h
BluetoothA2DPSource a2dp_source;

void scan(){
  digitalWrite(LED_PIN, HIGH);
  a2dp_source.scan(&speakers);                            // Start adding speakers to the list
  int now   = millis(); int later = now + 5000;           // wait SCAN_DURATION
  while (now<later){ now=millis(); delay(SCAN_DURATION);} // wait SCAN_DURATION
  a2dp_source.stopScan();                                 // Stop adding speakers to the list
  for (int i=0; i<speakers.num; i++){
    Serial.print("Name: ");Serial.println(speakers.speakers[i*sizeof(Speaker)].name);
    Serial.print("\tAddress: ");Serial.println(speakers.speakers[i*sizeof(Speaker)].address);
    Serial.print("\tRSSI: ");Serial.println(speakers.speakers[i*sizeof(Speaker)].RSSI);
  }
  digitalWrite(LED_PIN, LOW);
}

void setup(void) {
  Serial.begin(115200);
  //AudioLogger::instance().begin(Serial, AudioLogger::Debug);
  Serial.println("Setting up scan...");
  a2dp_source.scanSetup();                                // a2dp_source.shutdown(); doesn't work
  a2dp_source.stopScan();  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

// API
// get scan   -> return list of speakers
// clear list -> clear list of speakers
void loop(){
  while (Serial.available()>0){
    char c = Serial.read();
    switch(c){
      case 'S': scan();break;    // get scan
      case 's': scan();break;    // get scan
      case 'C': break;    // clear list
      case 'c': break;    // Clear list
      default:  break;    // ignore
    }
  }
}