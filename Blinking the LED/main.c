
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
  
  *((unsigned int *)0x400FE608u) = 0x20U; //enable clock gating
  *((unsigned int *)0x40025400u) = 0x0EU; //enable GPIO Port F 123 as output
  *((unsigned int *)0x4002551Cu) = 0x0EU; //enable GPIO Port F 123 as digital output
  //*((unsigned int *)0x400253FCu) = 0x08U; //write to pins 
  
  while(1){
      *((unsigned int *)0x400253FCu) = 0x04U; //write to pins 
      volatile int counter = 0;
      while(counter < 1000000){
          *((unsigned int *)0x400253FCu) = 0x04U; //write to pins 
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
