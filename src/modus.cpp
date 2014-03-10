
#include "modus.h"

using namespace std;

extern volatile int run;

void modus::manualMode(connection x)
{
	int channel;
	int value;
	char buffer[10];
	while(1)
	{
		cout << "\033[2J";
		for(int i = 1; i <= 20; i++)
		{
			printf("\033[%d;1HCh: %d", i, i);
			printf("\033[%d;9HValue: %d", i, x.getValue(i));
			printf("\033[%d;20HCh: %d", i, i+20);
            printf("\033[%d;28HValue: %d", i, x.getValue(i+20));
            printf("\033[%d;39HCh: %d", i, i+40);
            printf("\033[%d;47HValue: %d", i, x.getValue(i+40));
			printf("\033[%d;58HCh: %d", i, i+60);
            printf("\033[%d;66HValue: %d", i, x.getValue(i+60));
            printf("\033[%d;77HCh: %d", i, i+80);
            printf("\033[%d;85HValue: %d", i, x.getValue(+80));
		}
		
		cout << "\n\nc[channel] 	--> set channel";
		cout << "\nv[value] 	--> set value";
		cout << "\nq		--> quit mode";

		cout << "\n\n>> ";
		cin >> buffer;
		if(buffer[0] == 'c')
			channel = atoi(&buffer[1]);	
		if(buffer[0] == 'v')
			value = atoi(&buffer[1]);
		if(buffer[0] == 'q')
			break;
			

		
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
	cout << "\nred   channel: " <<y.getChRot();
	cout << "\ngreen channel: " <<y.getChGruen();
	cout << "\nblue  channel: " <<y.getChBlau() << "\n";
	
	while(run)
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
