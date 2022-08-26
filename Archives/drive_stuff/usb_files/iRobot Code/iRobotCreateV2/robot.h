#ifndef ROBOT_H
#define ROBOT_H

#define IROBOT_START 128
#define IROBOT_BAUD 129
#define IROBOT_B4800 4
#define IROBOT_B9600 5
#define IROBOT_B19200 7
#define IROBOT_B57600 10
#define IROBOT_SAFE_MODE 131
#define IROBOT_FULL_MODE 132
#define IROBOT_DEMO_MODE 136
#define IROBOT_ABORT_DEMO 255
#define IROBOT_DEMO_COVER 0
#define IROBOT_DEMO_MOUSE 3
#define IROBOT_DEMO_FIG8 4
#define IROBOT_DEMO_WIMP 5
#define IROBOT_DEMO_BANJO 9

#define robot_sendL(fd, cmd, numchars) write(fd,cmd,numchars)
#define robot_send(fd, cmd) robot_sendL(fd, cmd, sizeof(cmd))

int wakerobot(int fd);
int iRobot_Init(char *port);
int Start_robot(int fd);
void robot_go(int fd, double x, double y,  double boost);
long monitor_robot(int fd) ;
void get_robot_config();
#endif

