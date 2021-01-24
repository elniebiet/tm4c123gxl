#define RCGCGPIO (*((unsigned int *)0x400FE608u)) //Run-mode Clock-Gating Control Register for GPIO
#define GPIOF_BASE (volatile unsigned long *)0x40025000u
#define GPIOF_DIR (*((unsigned int *)(GPIOF_BASE + 0x400u)))
#define GPIOF_DEN (*((unsigned int *)0x4002551Cu))

#include "tm4c123gh6pm.h"

int main()
{
  //0x4002.5000 //Port F start address
  //0x400F.E000 //base address clock gating instruction, bit 5 of register for port F
  //0x608 //Offset for clock gating instruction i.e 0x400F.E608
  //that is change bit 5 of 0x400F.E608, see change in 0x4002.5000
  //GPIO port F pins direction as output: 0x4002.5000 offset 400
  //set pins 1 2 3 for RGB i.e 123 of 0x40025400
  //additionally set pins 1 2 3 as digital outputs i.e offset 51C 
  // => 0x4002551C to 0e
  //control the LED using offset 3FC, set bit 1 i.e 0x02 to turn on led
  
  
  //RCGCGPIO = 0x20U; //enable clock gating FOR GPIO Port F
  //or from library
  SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R5;
  
  //GPIOF_DIR = 0x0EU; //enable GPIO Port F 123 as output
  //or from library
  GPIO_PORTF_DIR_R = 0x0EU;
    
  //GPIOF_DEN = 0x0EU; //enable GPIO Port F 123 as digital output i.e digital enable
  //or from library
  GPIO_PORTF_DEN_R = 0x0EU;
  
  
  //BITWISE OPERATIONS
  unsigned int a = 0x5A5A5A5A;
  unsigned int b = 0xDEADBEEF;
  unsigned int c;
  c = a | b;
  c = a & b;
  c = a ^ b;
  c = ~b;
  c = b >> 1; 
  c = b << 3; 
  
  
  GPIO_PORTF_DATA_R = 0X04U; //turn on blue LED
    
  while(1){
      *((unsigned int *)0x400253FCu) = 0x04U; //write to pins 
      
      volatile int counter = 0;
      while(counter < 1000000){
          //*((unsigned int *)0x400253FCu) = 0x04U; //write to pins 
          volatile unsigned long * gpiof_base = GPIOF_BASE;
          gpiof_base[2] = 2;
          ++counter;
      }
      
      counter = 0;
      while(counter < 1000000){
          *((unsigned int *)0x400253FCu) = 0x00U; //write to pins
          ++counter;
      }
  }
  
  
  return 0;
}
