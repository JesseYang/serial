#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include "tool.h"
#include "serial.h"

using namespace std;
 
main()
{
	int fd;
	int i;
	int len;
	int n = 0;
	char read_buf[512];
	char write_buf[512];
	
	string server_ip = "192.168.0.104";
	int server_port = 8888;


/*
	struct termios opt;
	fd = open("/dev/ttyATH0", O_RDWR|O_NOCTTY|O_NDELAY);
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
 
	printf("configure complete\n");

	if(tcsetattr(fd, TCSANOW, &opt) != 0)
	{
		perror("serial error");
		return -1;
	}

	printf("start send and receive data\n");
*/

	Serial serial;

	while(1)
	{
		n = serial.write("AT+ENBR");
		// n = write(fd, "AT+ENBR\n", 8);
		printf("write %d chars\n", n);

		n = serial.read(read_buf, sizeof(read_buf));
		// bzero(read_buf, sizeof(read_buf));
		// n = read(fd, read_buf, sizeof(read_buf));
		printf("read %d chars\n", n);
		printf("read content: %s\n", read_buf);

		// send content to the server
		send_request(server_ip, server_port, read_buf);

		sleep(2);
	}
}
