#include     <stdio.h>  
#include     <stdlib.h>   
#include     <strings.h>   
#include     <unistd.h>    
#include     <sys/types.h>  
#include     <sys/stat.h>  
#include     <fcntl.h>   
#include     <termios.h>  
#include     <errno.h>  
     
main()  
{  
    int fd;  
    int i;  
    int len;  
    int n = 0;        
    char read_buf[512];  
    char write_buf[512];  
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
  
    while(1)  
    {      
        n = write(fd, "AT+ENBR\n", 8);
        printf("write %d chars\n", n);  

        bzero(read_buf, sizeof(read_buf));   
        n = read(fd, read_buf, sizeof(read_buf));
        printf("read %d chars\n", n);
        printf("read content: %s\n", read_buf);
        sleep(2);  
    }  
      
}  
