#include <cstring>
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
#include "main.h"
#include "log.h"

using namespace std;
 
main()
{
	log_init(LL_DEBUG, "log", "/root/");
	int n = 0;
	int loc_data_len = 2048;
	char read_buf[2048];
	char *data_with_code;
	Serial serial;

	while(1)
	{
		n = serial.write("AT+ENBR");

		data_with_code = new char[loc_data_len + 1 + strlen(CODE)];
		strcpy(data_with_code, CODE);
		strcat(data_with_code, "#");

		sleep(LOC_INFO_INTERVAL);

		n = serial.read(&data_with_code[strlen(CODE) + 1], loc_data_len);

		send_request(SERVER_IP, SERVER_PORT, data_with_code);
		sleep(LOC_INFO_INTERVAL);
	}
}
