#ifndef MODUS_H
#define MODUS_H

#include <iostream>
#include "config.h"
#include "connection.h"



class modus
{
	public:
	void manualMode(connection x);
	void rgbMode(connection x, config y);

};

#endif
