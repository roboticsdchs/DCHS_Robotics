#include <stdio.h>
#include <unistd.h>
#include "robot.h"

int main(int arc, char *argv[]) {

    int iRobot_fd;
    int k;

    char cmd[] = { 128, 132, 140, 0, 4, 62, 12, 66, 12, 69, 12, 74, 36, 44, 44, 141, 0};  // play a song
//    char cmd[] = { 128, 131, 137, 0, 200, 128, 0};

    iRobot_fd = iRobot_Init("/dev/ttyUSB0");

    while(1) {
        for (k=0; k<sizeof(cmd); k++) {
            write(iRobot_fd, &cmd[k], 1);
            usleep(100*1000);
        }
        usleep(500*1000);
    }

    return 0;
}
