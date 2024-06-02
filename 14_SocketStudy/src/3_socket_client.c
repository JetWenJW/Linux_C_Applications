#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define SERVER_PORT 8888
#define SERVER_IP   "192.168.1.134"


int main (void)
{
    struct sockaddr_in server_addr = {0};
    char buf[512];
    int sockfd;
    int ret = 0;

    /* Step1. Open Socket & Get Socket Descriptor */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        perror("socket Error");
        exit(EXIT_FAILURE);
    }

    /* Step2. Call Connect Function to connect to Server */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    ret = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(ret < 0)
    {
        perror("Connect Error");
	close(sockfd);
	exit(EXIT_FAILURE);
    }

    printf("Server Connected Succeed ~~\n");
    
    /* Send Data to Server */
    while(1)
    {
	/* Clear Buffer */
        memset(buf, 0x0, sizeof(buf));
    
        /* Get User Input String */
        printf("Please Enter A String: ");
	fgets(buf, sizeof(buf), stdin);
    
	/* Send User Input String to Server */
        ret = send(sockfd, buf, strlen(buf), 0);
        if(ret < 0)
	{
	    perror("Send Error");
	    break;
	}

	/* Input "exit" exit the while loop */
	if(strncmp(buf, "exit", 4) == 0)
	{
	    break;
	}
    }

    close(sockfd);
    exit(EXIT_SUCCESS);
}









