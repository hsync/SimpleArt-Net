#include "connection.h"
#include "config.h"

using namespace std;

connection::connection(char *ip, int port)
{

	char dmx_prae[] = {0x41, 0x72, 0x74, 0x2D, 0x4E, 0x65, 0x74, 0x00, 0x00, 0x50, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00};  
	memset(dat, 0, PACKET_SIZE);

	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		perror("socket()");


	sock_conf.sin_family = AF_INET;
	sock_conf.sin_port = htons(port);
	sock_conf.sin_addr.s_addr = inet_addr(ip);

	if(connect(sockfd, (struct sockaddr *) &sock_conf, sizeof(sock_conf)) == -1)
		perror("connect()");

	memcpy(dat, dmx_prae, 18);
}

void connection::setValue(int channel, int value)
{
	if(channel > 512 || value > 255)
		return;
	dat[17+channel] = value;
}

void connection::resetValues(void)
{
	memset(&dat[18], 0, 512);
}

int connection::sendPackage(void)
{
	if(send(sockfd, dat, PACKET_SIZE, 0) == -1)
		perror("send()");
}
