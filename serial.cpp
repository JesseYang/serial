#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include "serial.h"

using namespace std;

Serial::Serial() {
	struct termios opt;
	this->fd = open("/dev/ttyATH0", O_RDWR|O_NOCTTY|O_NDELAY);
	if(fd == -1)
	{
		perror("open serial 0\n");
		exit(0);
	}

	tcgetattr(fd, &opt);
	bzero(&opt, sizeof(opt));

	tcflush(fd, TCIOFLUSH);

	cfsetispeed(&opt, B115200);
	cfsetospeed(&opt, B115200);

	opt.c_cflag &= ~CSIZE;
	opt.c_cflag |= CS8;
	opt.c_cflag &= ~CSTOPB;
	opt.c_cflag &= ~PARENB;
	opt.c_cflag &= ~CRTSCTS;
	opt.c_cflag |= (CLOCAL | CREAD);

	opt.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
 
	opt.c_oflag &= ~OPOST;

	opt.c_cc[VTIME] = 0;
	opt.c_cc[VMIN] = 0;
 
	tcflush(fd, TCIOFLUSH);

	if(tcsetattr(fd, TCSANOW, &opt) != 0)
	{
		perror("serial error");
		return -1;
	}
}

int Serial::read(char* read_buf, int len) {
	bzero(read_buf, len);
	int n = read(this->fd, read_buf, len);
	return n;
}

int Serial::write(string write_buffer) {
	int n = write(this->fd, (write_buffer + "\n").c_str(), write_buffer.length() + 1);
	return n;
}

