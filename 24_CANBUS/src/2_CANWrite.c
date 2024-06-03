#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>

int main(void)
{
    struct ifreq ifr = {0};
    struct sockaddr_can can_addr = {0};
    struct can_frame frame = {0};
    int sockfd = -1;
    int ret;

    /* Open Socket */
    sockfd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if(sockfd < 0)
    {
        perror("Socket Error");
	exit(EXIT_FAILURE);
    }

    /* Specific can0 device */
    strcpy(ifr.ifr_name, "can0");
    ioctl(sockfd, SIOCGIFINDEX, &ifr);
    can_addr.can_family = AF_CAN;
    can_addr.can_ifindex = ifr.ifr_ifindex;

    /* Binding Socket & CAN */
    ret = bind(sockfd, (struct sockaddr *)&can_addr, sizeof(can_addr));
    if(ret < 0)
    {
        perror("Bind Error");
	close(sockfd);
	exit(EXIT_FAILURE);
    }

    /* Set Filter: Don't report Only send Data */
    setsockopt(sockfd, SOL_CAN_RAW, CAN_RAW_FILTER, NULL, 0);

    /* Send Data */
    frame.data[0] = 0xA0;
    frame.data[1] = 0xB0;
    frame.data[2] = 0xC0;
    frame.data[3] = 0xD0;
    frame.data[4] = 0xE0;
    frame.data[5] = 0xF0;
    frame.can_dlc = 6;		//send 6 bytes data
    frame.can_id = 0x123;	//frame_ID is 0x123,standard frame

    while(1)
    {
        ret = write(sockfd, &frame, sizeof(frame));	/* Send Data */
        if(sizeof(frame) != ret)
	{
	    perror("Write Error");
	    goto out;
	}
        sleep(1);	/* Send Data per second */
    }

out:
    /* close Socket */
    close(sockfd);
    exit(EXIT_SUCCESS);
}










