#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int random_number_arr[8];
    int count;

    /* set seed */
    srand(time(NULL));

    /* random number */
    for (count = 0; count < 8; count++)
    {
        random_number_arr[count] = rand() % 100;
    }
    printf("[");
    for (count = 0; count < 8; count++) 
    {
        printf("%d", random_number_arr[count]);
        if (count != 8 - 1)
        printf(", ");
    }
    printf("]\n");
return 0;

}