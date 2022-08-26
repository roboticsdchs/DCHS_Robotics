#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "serial.h"
/* This is the short version */

int open_serial(char *port, int baud) {
	int fd;
	struct termios options;
	fd = open(port, O_RDWR |O_NOCTTY | O_NONBLOCK);
	if (fd==-1) return fd;
    
	if( tcgetattr(fd,&options) == -1) {
		close(fd);
		return -1;
	}
	cfsetispeed(&options, baud);
	cfsetospeed(&options, baud);
	options.c_cflag |= CS7;
	options.c_cflag &= ~PARENB;
//	options.c_cflag &= ~PARODD;
//	options.c_cflag |= PARODD; // odd parity
	if( tcsetattr(fd, TCSANOW, &options) == -1) {
		close(fd);
		return -1;
	}
	return fd;
}

void toggle_bit(int fd, int mask) {
	int status;
	ioctl(fd,TIOCMGET, &status);
	status ^=mask;
	ioctl(fd, TIOCMSET, &status);
}

void flush_serial(int fd) {
	struct termios options;
	tcgetattr(fd, &options);
	tcsetattr(fd, TCSAFLUSH, &options);
}

void set_bit(int fd, int mask) {
	int status;
	ioctl(fd,TIOCMGET, &status);
	status |=mask;
	ioctl(fd, TIOCMSET, &status);
}

void clr_bit(int fd, int mask) {
	int status;
	ioctl(fd,TIOCMGET, &status);
	status &=~mask;
	ioctl(fd, TIOCMSET, &status);
}
