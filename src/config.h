#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PACKET_SIZE		530
#define DEFAULT_IP		"192.168.0.10"
#define DEFAULT_PORT	6454

class config
{
	private:
	char ip[16];
	int port;
	int rgbChRot;
	int rgbChGruen;
	int rgbChBlau;

	public:
	config(void);
	char *getIp(void);
	int getPort(void);
	int getChRot();
	int getChGruen();
	int getChBlau();
};

#endif
