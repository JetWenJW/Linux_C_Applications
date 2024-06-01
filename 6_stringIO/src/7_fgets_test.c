#include <stdio.h>


int main (void)
{
    char str[100] = {0};
    printf("please input string: ");
    fgets(str, sizeof(str), stdin);
    printf("%s", str);


    return 0;
}