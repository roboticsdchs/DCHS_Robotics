#ifndef SERIAL_H
#define SERIAL_H

#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

int open_serial(char *port, int baud);
void toggle_bit(int fd, int mask);
void set_bit(int fd, int mask);
void clr_bit(int fd, int mask);
void flush_serial(int fd);

#define toggle_DTR(fd) 	toggle_bit(fd, TIOCM_DTR)
#define set_DTR(fd) 	set_bit(fd, TIOCM_DTR)
#define clr_DTR(fd) 	clr_bit(fd, TIOCM_DTR)

#define toggle_RTS(fd) 	toggle_bit(fd, TIOCM_RTS)
#define set_RTS(fd) 	set_bit(fd, TIOCM_RTS)
#define clr_RTS(fd) 	clr_bit(fd, TIOCM_RTS)

#endif
