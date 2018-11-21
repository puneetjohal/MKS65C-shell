#include <stdio.h>

int main()
{
    char buf[100];
    fgets(buf, 100, stdin);
    printf("string is: %s\n", buf); 

    return 0;
}
