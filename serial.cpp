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

  tcsetattr(fd, TCSANOW, &opt);
}

int Serial::myRead(char* read_buffer, int len) {
  int n = read(fd, read_buffer, len);
  return n;
}

int Serial::myWrite(string write_buffer) {
  int n = write(fd, write_buffer.c_str(), write_buffer.length());
  return n;
}

