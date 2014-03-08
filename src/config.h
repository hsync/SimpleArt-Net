#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>

#define PACKET_SIZE		530
#define DEFAULT_IP		"192.168.0.10"
#define DEFAULT_PORT	6454

class config
{
	private:
	char ip[16];
	int port;

	public:
	config(void);
	char *getIp(void);
	int getPort(void);
};

#endif
