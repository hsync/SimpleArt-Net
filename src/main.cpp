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
