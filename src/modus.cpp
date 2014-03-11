
#include "modus.h"

using namespace std;

void modus::manualMode(connection x)
{
	int channel;
	int value;
	while(1)
	{
		cout << "\033[2J";
		for(int i = 1; i <= 20; i++)
		{
			printf("\033[%d;1HCh: %d", i, i);
			printf("\033[%d;9HValue: %d", i, x.getValue(i));
		}
                for(int i = 21; i <= 40; i++)
                {
                        printf("\033[%d;20HCh: %d", i-20, i);
                        printf("\033[%d;28HValue: %d", i-20, x.getValue(i));
                }
                for(int i = 41; i <= 60; i++)
                {
                        printf("\033[%d;39HCh: %d", i-40, i);
                        printf("\033[%d;47HValue: %d", i-40, x.getValue(i));
                }
                for(int i = 61; i <= 80; i++)
                {
                        printf("\033[%d;58HCh: %d", i-60, i);
                        printf("\033[%d;66HValue: %d", i-60, x.getValue(i));
                }
                for(int i = 81; i <= 100; i++)
                {
                        printf("\033[%d;77HCh: %d", i-80, i);
                        printf("\033[%d;85HValue: %d", i-80, x.getValue(i));
                }


		cout << "\n\nKanal : ";
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

	cout << "\033[2J\033[1;1H";
	cout << "rgb-fade";
	cout << "\nred    channel: " <<y.getChRot();
	cout << "\ngreen channel: " <<y.getChGruen();
	cout << "\nblue  channel: " <<y.getChBlau() << "\n";

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
