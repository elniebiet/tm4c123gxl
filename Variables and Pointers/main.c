
int counter = 0;

int main()
{
  int *p_int;
  p_int = &counter;
  while(*p_int < 20){
     ++(*p_int);
  }
  return 0;
}
