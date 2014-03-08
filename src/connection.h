#ifndef CONNECTION_H
#define CONNECTION_H

#include "config.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

class connection
{
	private:
	struct sockaddr_in sock_conf;
	int sockfd;
	char dat[PACKET_SIZE];

	public:
	connection(char *ip, int port);
	void setValue(int channel, int value);
	void resetValues();
	int sendPackage(void);
};

#endif
