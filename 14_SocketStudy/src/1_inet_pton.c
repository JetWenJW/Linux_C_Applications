#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define IPv4_ADDR "192.168.1.222"


int main (void)
{
    struct in_addr addr;
    inet_pton(AF_INET, IPv4_ADDR, &addr);
    printf("IP Address: 0x%x\n", addr.s_addr);
    exit(0);

}






