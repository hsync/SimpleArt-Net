
#include "config.h"
using namespace std;

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
