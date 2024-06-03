#include <stdio.h>
#include <stdlib.h>
#include <tslib.h>


int main(int argc, char *argv[])
{
    struct tsdev *ts = NULL;
    struct ts_sample sample;
    int pressure = 0;

    ts = ts_setup(NULL, 0);
    if(ts = NULL)
    {
        fprintf(stderr, "ts_setup Error");
	exit(EXIT_FAILURE);
    }

    /* Read Data */
    while(1)
    {
        if(ts_read(ts, &sample, 1) < 0)
	{
	    fprintf(stderr, "ts_read Error");
	    ts_close(ts);
	    exit(EXIT_FAILURE);
	}
        
	if(sample.pressure)
	{
	    if(pressure)	printf("Move (%d, %d)\n", sample.x, sample.y);
	    else		printf("Press(%d, %d)\n", sample.x, sample.y);
	}
	else
	{
	    printf("Release\n");
	}
	pressure = sample.pressure;
    
    }

    ts_close(ts);
    exit(EXIT_SUCCESS);
}

