#include "lm4f120h5qr.h"
#include "delay.h"

#define LED_RED   (1U << 1) //set first bit for red led
#define LED_BLUE  (1U << 2) //set second bit for blue
#define LED_GREEN (1U << 3) //...

int *swap(int *x, int *y);
int *swap(int *x, int *y){
  static int temp[2];
  temp[0] = *x;
  temp[1] = *y;
  *x = temp[1];
  *y = temp[0];
  
  return temp;
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
        
        int x = 1000000;
        int y = 500000;
        int *time = swap(&x, &y);
        
        delay(time[0]);

        GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = 0; //clear red led
        delay(time[1]);

    }
    //return 0;
}
