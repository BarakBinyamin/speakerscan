#include <Arduino.h>

#pragma once

#define SPEAKER_LIST_SIZE    30

struct Speaker{
  String address;
  String name;
  String RSSI;
};
struct Speakers{
  int     num;
  Speaker speakers[sizeof(Speaker)*SPEAKER_LIST_SIZE]; 
};
