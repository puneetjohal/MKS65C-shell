#include <stdio.h>

int main()
{
    char * c = "hello";
    while (*c){
      printf("%c\n",c);
      c++;
    }
    return 0;
}
