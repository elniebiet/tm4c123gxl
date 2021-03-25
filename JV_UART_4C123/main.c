
#include <stdio.h>
#include <stdint.h> // C99 variable types
void Output_Init(void);
void BookExamples(void){ // examples from the book
  int8_t cc = 0x56; // (‘V’)
  int32_t xx = 100;
  int16_t yy = -100;
  float zz = 3.14159265;
  printf("Hello world\n");	//Hello world
  printf("cc = %c %d %#x\n",cc,cc,cc);	//cc = V 86 0x56
  printf("xx = %c %d %#x\n",xx,xx,xx);	//xx = d 100 0x64
  printf("yy = %d %#x\n",yy,yy);	//yy = -100 0xffffff9c
  printf("zz = %e %E %f %g %3.2f\n",zz,zz,zz,zz,zz);	//zz = 3.14159 3.14
}
int main(void){ int32_t i,n;
  Output_Init();              // initialize output device
  BookExamples();
  n = 0;
  while(1){
    printf("\ni="); 
    for(i=0; i<5; i++){
      printf("%d ",i+n);
    }

    n = n+1000000; // notice what happend when this goes above 2,147,483,647
  }
}
