#include <string>

#ifndef SERIAL_H
#define SERIAL_H

using namespace std;

class Serial {
	private:
		int fd;
	public:
		int read(char*, int);
		int write(string);
		Serial();
};

#endif
