#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(int argc, char *argv[])
{
    clock_t t_start;
    clock_t t_end;
    int i, j;

    /* Start Time */
    t_start = clock();
    if (0 > t_start)    return 1;

    
    /* *****Test Code Runtimes***** */
    for (i = 0; i < 20000; i++)
    for (j = 0; j < 20000; j++)
    ;

    /* *************end************** */
    /* End Time */

    t_end = clock();
    if (0 > t_end)     return (1);


    /* Print  out */
    printf("Total CPU Runtime: %f\n", (t_end - t_start) / (double)CLOCKS_PER_SEC);

    return (0);
}