#include <stdio.h>
#include "robot.h"
#include "joy.h"

#define _LINUX_ 1
#if _LINUX_
#   include "serial.h"
#else
#   include "nnlib.h"
#endif

#define DEBUG(x) fprintf(stderr, "%s = %g\n", #x, (double) (x))

int wakerobot(int fd)
{
	int k;
	char buffer[80];
	char cmd[] = { 128, 132, 0 };
	fprintf(stderr, "Waking robot up\n");
	for (k = 0; k < 10; k++) {
		int reply;
		fprintf(stderr, "%d", k);
		toggle_RTS(fd);
		*buffer = 0;
		reply = read(fd, buffer, sizeof(buffer));
		if (reply > 0) {
			fprintf(stderr, "[%d]\n_robot says: \n\n%s\n", reply, buffer);
			return 0;
		} else
			fprintf(stderr, "[%d] ", reply);
		robot_send(fd, cmd);
		sleep(1);
	}
	return 1;
}

int Start_robot(int fd)
{
	unsigned char cmd[] = { 128, 131 };
	fprintf(stderr, "waitinn 1 second\n");
	sleep(1);
	if (wakerobot(fd) == 0) {
		robot_send(fd, cmd);
		return 0;
	}
	return 1;
}

void robot_motor(int fd, unsigned char cmd)
{
	unsigned char buf[2];
	buf[0] = 138;
	buf[1] = cmd;
	robot_send(fd, buf);
}

#define SIGN(z) ((z)>0? 1:-1)
#define MAX(a,b) ((a)>(b)?(a):(b))
#define ABS(x) ((x)>0?(x):-(x))

static int lastnchars;
static unsigned char lastcmd[100];

static int should_we_send(unsigned char cmd[], int nchars)
{
	int k;
	if (nchars != lastnchars)
		return 1;
	for (k = 0; k < nchars; k++)
		if (cmd[k] != lastcmd[k])
			return 1;
	return 0;
}

void send_as_needed(int fd, unsigned char cmd[], int nchars)
{
	static int skip_count;
	int k;

	if (should_we_send(cmd, nchars) == 0) {
		skip_count++;
		if (skip_count < 50)
			return;
	}

	/* Okay send the command */
	/* First keep track of what we send */
	skip_count = 0;
	lastnchars = nchars;
	for (k = 0; k < nchars; k++)
		lastcmd[k] = cmd[k];
#if 1
	fprintf(stderr, "sending: ");
	for (k = 0; k < nchars; k++)
		fprintf(stderr, "%3d ", cmd[k]);
	fprintf(stderr, "\n");
#endif 

	robot_sendL(fd, cmd, nchars);
}


void robot_go(int fd, double x, double y, double boost)
{
	int R;
	int speed;
	double ax, ay;
	unsigned char cmd[5];
	ax = ABS(x);
	ay = ABS(y);
	x = -x;						/* CC is +ve */
	if (y == 0 && x == 0)
		R = 0;
	else {
		if (y == 0)
			R = x > 0 ? 0 : -1;
		else if (x == 0)
			R = 32768;
		else
			R = (int) ((500 - 250 * ax) * SIGN(x));
	}
	speed = (int) (MAX(ax, ay) * 500 * SIGN(y) * boost);

	if (R < 0)
		R = R + 65536;
	if (speed < 0)
		speed = speed + 65536;
	cmd[0] = 137;
	cmd[1] = speed / 256;
	cmd[2] = speed % 255;
	cmd[3] = R / 256;
	cmd[4] = R % 256;
	send_as_needed(fd, cmd, sizeof(cmd));
}

int iRobot_Init(char *port) {
    int fd = open_serial(port, B57600);
    if (fd < 0) return -1;

    Start_robot(fd);

    return fd;
}
