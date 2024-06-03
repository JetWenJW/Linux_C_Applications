#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/input.h>
#include <tslib.h>

int main(int argc, char *argv[])
{
    struct tsdev *ts = NULL;
    struct ts_sample_mt *mt_ptr = NULL;
    struct input_absinfo slot;
    int max_slots;
    unsigned int pressure[12] = {0};
    int i;

    ts = ts_setup(NULL, 0);
    if(ts = NULL)
    {
        fprintf(stderr, "ts_setup Error");
	exit(EXIT_FAILURE);
    }

    if(ioctl(ts_fd(ts), EVIOCGABS(ABS_MT_SLOT), &slot) < 0)
    {
        perror("ioctl Error");
	exit(EXIT_FAILURE);
    }

    max_slots = slot.maximum + 1 - slot.minimum;
    printf("max slots: %d\n", max_slots);

    /* Memory allocate */
    mt_ptr = calloc(max_slots, sizeof(struct ts_sample_mt));

    /* Read Data */
    while(1)
    {
        if(ts_read_mt(ts, &mt_ptr, max_slots, 1) < 0)
	{
	    perror("ts_read_mt Error");
	    ts_close(ts);
	    free(mt_ptr);
	    exit(EXIT_FAILURE);
	}

	for(i = 0;i < max_slots;i++)
	{
	    if(mt_ptr[i].valid)
	    {
	        if(mt_ptr[i].pressure)
		{
		    if(pressure[mt_ptr[i].slot])	printf("slot<%d>, Move(%d, %d)\n", mt_ptr[i].slot, mt_ptr[i].x, mt_ptr[i].y);
		    else				printf("slot<%d>, Move(%d, %d)\n", mt_ptr[i].slot, mt_ptr[i].x, mt_ptr[i].y);
		}
		else
		{
		    printf("slot<%d>, Release\n", mt_ptr[i].slot);
		}
		pressure[mt_ptr[i].slot] = mt_ptr[i].pressure;
	   }
	}
    }
    ts_close(ts);
    free(mt_ptr);
    exit(EXIT_SUCCESS);

}





