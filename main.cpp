#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define PACKET_SIZE	530
#define DEFAULT_IP	"192.168.0.10"
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

config::config(void)
{
	port = DEFAULT_PORT;
	cout << "ART-Net IP: ";
	cin >> ip;
}

char *config::getIp()
{
	return ip;
}

int config::getPort(void)
{
	return port;
}


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


class modus
{
	public:
	void manualMode(connection x);
	void rgbMode(connection x);

};

void modus::manualMode(connection x)
{
	int channel;
	int value;
	while(1)
	{
		cout << "\nKanal : ";
		cin >> channel;
		cout << "Wert  : ";
		cin >> value;
		x.setValue(channel, value);
		x.sendPackage();
	}
}

void modus::rgbMode(connection x)
{
	static int mode = 0;
	int rot = 255;
	int gruen = 0;
	int blau = 0;

	while(1)
	{
		if(mode == 0){rot --; gruen ++;}
		if(mode == 1){gruen --; blau ++;}
		if(mode == 2){blau --; rot ++;}

		if(gruen == 255) mode = 1;
		if(blau == 255) mode = 2;
		if(rot == 255) mode = 0;
		x.setValue(1, rot);
		x.setValue(2, gruen);
		x.setValue(3, blau);
		x.sendPackage();
		for(int i = 0; i < 1E6; i++);
	}
}

int main()
{
	config configuration;
	modus mode;
	connection artNet(configuration.getIp(), configuration.getPort());
	int wahl = 0;

	cout << "Sende Packete an: " << configuration.getIp() << ":" << configuration.getPort();
	cout << "\nModus auswählen\n";
	cout << "<1> Manuell\n";
	cout << "<2> RGB-Fade\n";
	cout << "\nBitte wählen: ";
	cin >> wahl;

	switch(wahl)
	{
		case 1:	cout << "\nManueller Modus";
			mode.manualMode(artNet);
			break;

		case 2:	cout << "\nRGB-Fade";
			mode.rgbMode(artNet);
			break;
	}
}
