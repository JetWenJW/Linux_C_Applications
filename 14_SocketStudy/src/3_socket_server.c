#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define SERVER_PORT 8888



int main(void)
{
    struct sockaddr_in server_addr = {0};
    struct sockaddr_in client_addr = {0};
    char ip_str[20];
    int sockfd, connfd;
    int addrlen = sizeof(client_addr);
    char recvbuf[512];
    int ret = 0;

    /* Step1. Get Socket Descriptor & Open Socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        perror("Socket Error");
	exit(EXIT_FAILURE);
    }

    /* Step2. binding Socket & IP address */
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_PORT);

    ret = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(ret < 0)
    {
        perror("Bind Error");
	close(sockfd);
        exit(EXIT_FAILURE);
    }

    /* Step3. Server go tp Listen State */
    ret = listen(sockfd, 50);
    if(ret < 0)
    {
        perror("Listen Error");
        close(sockfd);
	exit(EXIT_FAILURE);
    }

    /* Step4. Blocking Waiting Client connet */
    connfd = accept(sockfd, (struct sockaddr *)&client_addr, &addrlen);
    if(connfd < 0)
    {
        perror("Accept Error");
	close(sockfd);
        exit(EXIT_FAILURE);
    }
 
    printf("Having Client Request to Connect\r\n");
    inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, ip_str, sizeof(ip_str));
    printf("Client Host IP Address : %s\n", ip_str);
    printf("Client Processor Port Number: %d\n", client_addr.sin_port);


    /* Get The Data from Client */
    while(1)
    {
	/* Clear buffer */
        memset(recvbuf, 0x0, sizeof(recvbuf));
    
        /* Read Data */
        ret = recv(connfd, recvbuf, sizeof(recvbuf), 0);
	if(ret <= 0)
	{
	    perror("recv Error");
	    close(connfd);
	    break;
	}
        
        /* Print Out Data via String */     
        printf("Fron Client: %s\n", recvbuf);
        
        /* Read "exit", then exit */
        if(strncmp("exit", recvbuf, 4) == 0)
	{
	    printf("Server Exit\n");
	    close(connfd);
	    break;
	}
    }

    /* Close Socket */
    close(sockfd);
    exit(EXIT_FAILURE);
}
