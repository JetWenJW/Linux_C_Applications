#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <signal.h>

typedef struct uart_hardware_cfg
{
    unsigned int baudrate;	/* Baud Rate  */
    unsigned char dbit;		/* Data Bit   */
    char parity;		/* Parity Bit */
    unsigned char sbit;		/* Stop Bit   */
} uart_cfg_t;

static struct termios old_cfg;	/* Use to store Configured Parameter */
static int fd;

static int uart_init(const char *device)
{
    /* Open Terminal */
    fd = open(device, O_RDWR | O_NOCTTY);
    if(fd < 0)
    {
        fprintf(stderr, "Open Error: %s: %s\n", device, strerror(errno));
	return -1;
    }

    /* Get Serial Port Configurations */
    if(tcgetattr(fd, &old_cfg) < 0)
    {
        fprintf(stderr, "tcgetattr Error: %s\n", strerror(errno));
	close(fd);
	return -1;
    }
    return 0;
}

static int uart_cfg(const uart_cfg_t * cfg)
{
    struct termios new_cfg = {0};
    speed_t speed;

    /* Set as RAW Mode */
    cfmakeraw(&new_cfg);

    /* Enable Receive */
    new_cfg.c_cflag |= CREAD;
	
    /* Set Baudrate */
    switch (cfg->baudrate) 
    {
    	case 1200: 
		speed = B1200;
        	break;
    	case 1800: 
		speed = B1800;
        	break;
    	case 2400: 
		speed = B2400;
        	break;
    	case 4800: 
		speed = B4800;
        	break;
    	case 9600: 
		speed = B9600;
        	break;
    	case 19200: 
		speed = B19200;
        	break;
    	case 38400: 
		speed = B38400;
        	break;
    	case 57600: 
		speed = B57600;
        	break;
    	case 115200: 
		speed = B115200;
        	break;
    	case 230400: 
		speed = B230400;
        	break;
    	case 460800: 
		speed = B460800;
        	break;
    	case 500000: 
		speed = B500000;
        	break;
    	default:  
        	speed = B115200;
        	printf("default baud rate: 115200\n");
        	break;
    }
    
    if(cfsetspeed(&new_cfg, speed) < 0)
    {
        fprintf(stderr, "cfserspeed Error: %s\n", strerror(errno));
	return -1;
    }

    /* Set Data bit size */
    new_cfg.c_cflag &= ~CSIZE;	/* Clear Data Bits */
    switch(cfg->dbit)
    {
    case 5:
	    new_cfg.c_cflag |= CS5;
    case 6:
	    new_cfg.c_cflag |= CS6;
    case 7:
	    new_cfg.c_cflag |= CS7;
    case 8:
	    new_cfg.c_cflag |= CS8;
    default:
	    new_cfg.c_cflag |= CS8;
   	    printf("Default data bits size : 8\n");
	    break;
    }
    
    /* Set Parity Bit */
    switch(cfg->parity)
    {
	    case 'N': 	/* No Parity */
		    new_cfg.c_cflag &= ~PARENB;
		    new_cfg.c_iflag &= ~INPCK;
		    break;
	    case 'O':	/* Odd Parity */
		    new_cfg.c_cflag |= (PARODD | PARENB);
		    new_cfg.c_iflag |= INPCK;
		    break;
    	    case 'E':
		    new_cfg.c_cflag |= PARENB;
		    new_cfg.c_cflag &= ~PARODD;	/* Clear PARODD Flag, Set as Even Parity */
		    new_cfg.c_iflag |= INPCK;
		    break;
	    default:
                    new_cfg.c_cflag &= ~PARENB;
                    new_cfg.c_iflag &= ~INPCK;
		    printf("Default Parity: N\n");
		    break;
    }
    
    /* Set Stop Bit */
    switch(cfg->sbit)
    {
	    case 1:	/* One Stop bit */
		    new_cfg.c_cflag &= ~CSTOPB;
		    break;
	    case 2:	/* Two Stop Bits */
		    new_cfg.c_cflag |= CSTOPB;
		    break;
	    default:
                    new_cfg.c_cflag &= ~CSTOPB;
                    printf("default stop bit size: 1\n");
		    break;
    }

    /* Set MIN & TIME as 0 */
    new_cfg.c_cc[VTIME] = 0;
    new_cfg.c_cc[VMIN] = 0;

    /* Clear Buffer */
    if(0 > tcsetattr(fd, TCSANOW, &new_cfg))
    {
        fprintf(stderr, "tcsetattr Error: %s\n", strerror(errno));
	return -1;
    }

    /* Config Ok & exit */
    return 0;

}

static void show_help(const char *app)
{
    printf("Usage: %s [options]\n"
        "\nMandatory options:\n"
        "  --dev=DEVICE     Specify the serial port device name, e.g., --dev=/dev/ttymxc2\n"
        "  --type=TYPE      Specify the operation type, read or write to the serial port, e.g., --type=read (read means read, write means write, other values are invalid)\n"
        "\nOptional options:\n"
        "  --brate=SPEED    Specify the baud rate of the serial port, e.g., --brate=115200\n"
        "  --dbit=SIZE      Specify the number of data bits, e.g., --dbit=8 (possible values: 5/6/7/8)\n"
        "  --parity=PARITY  Specify the parity check method, e.g., --parity=N (N means no parity, O means odd parity, E means even parity)\n"
        "  --sbit=SIZE      Specify the number of stop bits, e.g., --sbit=1 (possible values: 1/2)\n"
        "  --help           View the program usage information\n\n", app);
}

static void io_handler(int sig, siginfo_t *info, void *context)
{
    unsigned char buf[10] = {0};
    int ret, n;
    if(SIGRTMIN != sig) return;

    /* Seiral Port have Data or not */
    if(POLL_IN == info->si_code)
    {
        ret = read(fd, buf, 8);
	printf("[");
	for(n = 0;n < ret;n++)
	{
		printf("0x%hhx", buf[n]);
	}
	printf("]");
    }
}

static void async_io_init(void)
{
    struct sigaction sigatn;
    int flag;

    /* Enable Async I/O */
    flag = fcntl(fd, F_GETFL);
    flag |= O_ASYNC;
    fcntl(fd, F_SETFL, flag);

    /* Set the owner  of Async I/O */
    fcntl(fd, F_SETSIG, SIGRTMIN);

    /* Set Real-Time Signal(SIGRTMIN) as Async I/O */
    fcntl(fd, F_SETSIG, SIGRTMIN);

    /* Register a SIGNAL Handler to SIGRTMIN */
    sigatn.sa_sigaction = io_handler;
    sigatn.sa_flags = SA_SIGINFO;
    sigemptyset(&sigatn.sa_mask);
    sigaction(SIGRTMIN, &sigatn, NULL);
}

int main(int argc, char *argv[])
{
    uart_cfg_t cfg = {0};
    char *device = NULL;
    int rw_flag = -1;
    unsigned char w_buf[10] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};

    int n;

    /* Read The Parameter Fromm User */
    for (n = 1; n < argc; n++) 
    {
        if (!strncmp("--dev=", argv[n], 6))
            device = &argv[n][6];
        else if (!strncmp("--brate=", argv[n], 8))
            cfg.baudrate = atoi(&argv[n][8]);
        else if (!strncmp("--dbit=", argv[n], 7))
            cfg.dbit = atoi(&argv[n][7]);
        else if (!strncmp("--parity=", argv[n], 9))
            cfg.parity = argv[n][9];
        else if (!strncmp("--sbit=", argv[n], 7))
            cfg.sbit = atoi(&argv[n][7]);
        else if (!strncmp("--type=", argv[n], 7)) 
	{
            if (!strcmp("read", &argv[n][7]))
                rw_flag = 0;        //Read
            else if (!strcmp("write", &argv[n][7]))
                rw_flag = 1;        //Write
        }
        else if (!strcmp("--help", argv[n])) 
	{
            show_help(argv[0]); //Help Messages
            exit(EXIT_SUCCESS);
        }
    }

    if(NULL == device || -1 == rw_flag)
    {
        fprintf(stderr, "Error : the device and Read | Write type must be set !\n");
	show_help(argv[0]);
	exit(EXIT_FAILURE);
    }

    /* Uart Initial */
    if(uart_cfg(&cfg))
    {
        tcsetattr(fd, TCSANOW, &old_cfg);	/* Recover Previous Setting */
	close(fd);
	exit(EXIT_FAILURE);
    }

    /* Read/Write */
    switch (rw_flag) 
    {
    	case 0:  // Read serial port data
        	async_io_init();   // We use asynchronous I/O to read data from the serial port, call this function to initialize asynchronous I/O
        	for ( ; ; )
            		sleep(1);      // Enter sleep mode, wait for data to be read, and jump to io_handler() function when data is available
        	break;
    	case 1:   // Write data to the serial port
        	for ( ; ; ) 
		{      
	    		// Loop to write data to the serial port
            		write(fd, w_buf, 8); 	// Write 8 bytes to the serial port at a time
            		sleep(1);       		// Interval of 1 second
        	}
        	break;
    }

    /* Exit */
    tcsetattr(fd, TCSANOW, &old_cfg);   // Restore the previous configuration
    close(fd);
    exit(EXIT_SUCCESS);
}
















