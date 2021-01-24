#include "lm4f120h5qr.h"

#define LED_RED   (1U << 1) //set first bit for red led
#define LED_BLUE  (1U << 2) //set second bit for blue
#define LED_GREEN (1U << 3) //...

void delay(int time);

void delay(int time){
  int volatile counter;
  counter = 0;
  while (counter < time) {  // delay loop
      ++counter;
  }
}

int main() {
    SYSCTL_RCGCGPIO_R |= (1U << 5);  /* enable clock for GPIOF */ //i.e bit 5 
    SYSCTL_GPIOHBCTL_R |= (1U << 5); /* enable AHB for GPIOF */ //i.e bit 5, switching from APB to AHB
    GPIO_PORTF_AHB_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN); // set port direction to output
    GPIO_PORTF_AHB_DEN_R |= (LED_RED | LED_BLUE | LED_GREEN); //set port direction to digital enable
    
    
    
    GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] = LED_BLUE; //turn on blue led
    while (1) {
        //*((unsigned long volatile *)(0x40025000 + (LED_RED << 2))) = LED_RED;
        //*(GPIO_PORTF_DATA_BITS_R + LED_RED) = LED_BLUE;
        GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_RED;
        delay(1000000);

        GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = 0; //clear red led
        delay(500000);

    }
    //return 0;
}
