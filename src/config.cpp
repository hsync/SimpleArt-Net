
#include "config.h"
using namespace std;

config::config(void)
{
	char buffer[20];
	FILE *fp;
	if((fp = fopen("conf/config", "r")) == NULL)
	{
		port = DEFAULT_PORT;
		cout << "ART-Net IP: ";
		cin >> ip;
		cout << "\nCant open config file";
		return;
	}

	// IP suchen
	for(int i = 0; i<20; i++)
	{
		fgets(buffer, 20, fp);
		buffer[3] = 0;
		if((strcmp(buffer, "ip:"))==0)
		{
			for(int i = 0; i<20; i++)
				if((buffer[i] < 0x30 || buffer[i] > 0x39) && buffer[i] != 0x2E) buffer[i] = 0;

			strcpy(ip, &buffer[4]);
			break;
		}
	}
	fclose(fp);

	fp = fopen("conf/config", "r");
	// Port suchen
    for(int i = 0; i<20; i++)
    {
		fgets(buffer, 20, fp);
        buffer[5] = 0;
		if((strcmp(buffer, "port:"))==0)
		{
			port =  atoi(&buffer[6]);
			break;
		}
    }
	fclose(fp);
	
	fp = fopen("conf/config", "r");
	//Channel rot suchen
    for(int i = 0; i<20; i++)
    {
		fgets(buffer, 20, fp);
		buffer[12] = 0;
		if((strcmp(buffer, "channel_rot:"))==0)
		{
		    rgbChRot =  atoi(&buffer[13]);
			break;
		}
    }
	fclose(fp);
	
	fp = fopen("conf/config", "r");
	//Channel gruen suchen
    for(int i = 0; i<20; i++)
    {
		fgets(buffer, 20, fp);
		buffer[14] = 0;
		if((strcmp(buffer, "channel_gruen:"))==0)
		{
		    rgbChGruen =  atoi(&buffer[15]);
			break;
		}
    }
	fclose(fp);

	fp = fopen("conf/config", "r");
	//Channel blau suchen
    for(int i = 0; i<20; i++)
    {
		fgets(buffer, 20, fp);
		buffer[13] = 0;
		if((strcmp(buffer, "channel_blau:"))==0)
		{
		    rgbChBlau =  atoi(&buffer[14]);
			break;
		}
    }
	fclose(fp);

	

}

char *config::getIp()
{
	return ip;
}

int config::getPort(void)
{
	return port;
}

int config::getChRot()
{
	return rgbChRot;
}
int config::getChGruen()
{
	return rgbChGruen;
}
int config::getChBlau()
{
	return rgbChBlau;
}

