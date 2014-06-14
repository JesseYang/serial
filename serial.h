#include <string>

#ifndef SERIAL_H
#define SERIAL_H

using namespace std;

class Serial {
  private:
    int fd;
  public:
    int myRead(char*, int);
    int myWrite(string);
    Serial();
};

#endif
