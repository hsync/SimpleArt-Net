
#include "modus.h"

using namespace std;

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

void modus::rgbMode(connection x, config y)
{
	int mode = 0;
	int rot = 255;
	int gruen = 0;
	int blau = 0;


	cout << "\nRot   Channel: " <<y.getChRot();
	cout << "\nGruen Channel: " <<y.getChGruen();
	cout << "\nBlau  Channel: " <<y.getChBlau() << "\n";

	while(1)
	{
		if(mode == 0){rot --; gruen ++;}
		if(mode == 1){gruen --; blau ++;}
		if(mode == 2){blau --; rot ++;}

		if(gruen == 255) mode = 1;
		if(blau == 255) mode = 2;
		if(rot == 255) mode = 0;
		x.setValue(y.getChRot(), rot);
		x.setValue(y.getChGruen(), gruen);
		x.setValue(y.getChBlau(), blau);
		x.sendPackage();
		for(int i = 0; i < 1E6; i++);
	}
}
