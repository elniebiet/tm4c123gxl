#include "lm4f120h5qr.h"
#include "delay.h"

#define LED_RED   (1U << 1) //set first bit for red led
#define LED_BLUE  (1U << 2) //set second bit for blue
#define LED_GREEN (1U << 3) //...

unsigned fact(unsigned num);

int main() {
    unsigned volatile x;
    x = fact(0u);
    x = 2u + 3u * fact(1u);
    (void)fact(5u);
  
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
        delay(1000000);

    }
    //return 0;
}

//recursive function
unsigned fact(unsigned num){
  //0! = 1
  //n! = n * (n-1) for all n > 0
  if(num == 0u){
    return 1u;
  } else {
    return num * fact(num - 1u);
  }
}
