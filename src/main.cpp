#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "connection.h"
#include "modus.h"

using namespace std;


int main()
{
	config configuration;
	modus mode;
	connection artNet(configuration.getIp(), configuration.getPort());
	int wahl = 0;

	cout << "\033[2J\033[1;1H";
	cout << "Art-Net packets to: " << configuration.getIp() << ":" << configuration.getPort();
	cout << "\nChoose mode\n";
	cout << "<1> manuell\n";
	cout << "<2> rgb-fade\n";
	cout << "\n>> ";
	cin >> wahl;

	switch(wahl)
	{
		case 1:	mode.manualMode(artNet);
			break;

		case 2: mode.rgbMode(artNet, configuration);
			break;
	}
}
