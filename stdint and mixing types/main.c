#include "lm4f120h5qr.h"
#include "delay.h"
#include <stdint.h>

#define LED_RED   (1U << 1) //set first bit for red led
#define LED_BLUE  (1U << 2) //set second bit for blue
#define LED_GREEN (1U << 3) //...

uint8_t u8a, u8b;
uint16_t u16c, u16d;
uint32_t u32e, u32f;

int8_t s8a, s8b;
int16_t s16c, s16d;
int32_t s32e, s32f;

int main() {
  
    u16c = 40000u;
    u16d = 30000u;
    u32e = (uint32_t)u16c + u16d; //enforcing promotion to the largest of the operands
    
    s32e = 10 - (int32_t)u16c; //10 is signed by default
  
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
