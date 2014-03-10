#include <iostream>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "config.h"
#include "connection.h"
#include "modus.h"

using namespace std;
volatile int run = true;

void my_handler(int x)
{
	if(x==2)
		run = false;
}

int main()
{
	signal(SIGINT, my_handler);
	
	config configuration;
	modus mode;
	connection artNet(configuration.getIp(), configuration.getPort());
	int wahl = 0;

	cout << "Art-Net packets to: " << configuration.getIp() << ":" << configuration.getPort();

	
	while(1)
	{
		cout << "\033[2J\033[1;1H";
		cout << "choose mode\n";
		cout << "<1> manuell\n";
		cout << "<2> rgb-fade\n";
		cout << "<3> exit\n";
		cout << "\n>> ";
		cin >> wahl;
		run = true;
		switch(wahl)
		{
			case 1:	mode.manualMode(artNet);
				break;

			case 2: mode.rgbMode(artNet, configuration);
				break;
			
			case 3: exit(1);
		}
	}
}
