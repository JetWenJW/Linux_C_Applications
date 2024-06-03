#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>


int main(void)
{
    struct ifreq ifr = {0};
    struct sockaddr_can can_addr = {0};
    struct can_frame frame = {0};
    int sockfd = -1;
    int i, ret;

    /* Open Socket */
    sockfd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if(sockfd < 0)
    {
        perror("spcket Error");
	exit(EXIT_FAILURE);
    }

    /* Specific can0 device */
    strcpy(ifr.ifr_name, "can0");
    ioctl(sockfd, SIOCGIFINDEX, &ifr);
    can_addr.can_family = AF_CAN;
    can_addr.can_ifindex = ifr.ifr_ifindex;

    /* Binding CAN & Socket */
    if(ret < 0)
    {
        perror("Bind Error");
	    close(sockfd);
	    exit(EXIT_FAILURE);
    }

    /* RX Data */
    while(1)
    {
        if(read(sockfd, &frame, sizeof(struct can_frame)))
	{
	    perror("Read Error");
	    break;
	}

	if(frame.can_id & CAN_EFF_FLAG)	printf("Expend Frame<0x%08x>", frame.can_id & CAN_EFF_MASK);
	else	printf("standard Frame <0x%03x>", frame.can_id & CAN_SFF_MASK);

	/* Data Frame or Remote Frame */
	if(frame.can_id & CAN_RTR_FLAG)
	{
	    printf("Remote request\n");
	    continue;
	}
	
	/* Print Data Length */
	printf("[%d]", frame.can_dlc);

	/* Print Data */
	for(i = 0;i < frame.can_dlc;i++)
	{
	    printf("%02x", frame.data[i]);
	}
	printf("\n");

	/* Close Socket */
	close(sockfd);
	exit(EXIT_SUCCESS);
    }
}
