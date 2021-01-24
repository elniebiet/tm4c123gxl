#include "delay.h"

void delay(int time){
  int volatile counter;
  counter = 0;
  while (counter < time) {  // delay loop
      ++counter;
  }
}