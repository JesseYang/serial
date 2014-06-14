#include <iostream>
#include <thread>
#include <string>
#include "serial.h"
using namespace std;

int main() {
  Serial serial;
  string cmd = "AT+ENBR";
  int numWrite = serial.myWrite(cmd);
  cout << numWrite << endl;

  char* content = new char[50];
  int numRead = serial.myRead(content, 50);

  cout << numRead << endl;

  cout << content << endl;
}
