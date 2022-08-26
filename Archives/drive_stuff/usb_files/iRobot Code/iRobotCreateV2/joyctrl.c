//kbechamp@umich.edu
//nattu7@gmail.com

#include <stdio.h>
#include "robot.h"
#include "joy.h"

int main(int arc, char *argv[]) {
    int iRobot_fd;

    init_joy();

    iRobot_fd = iRobot_Init("/dev/ttyUSB0");

    if (iRobot_fd < 0) {
        fprintf(stderr, "fd = %d, failed to open\n", iRobot_fd);
        return -1;
    }

    while(1) {
        double x, y, boost;

        if (BUTTONBACK && BUTTONSTART) break;
        if (BUTTONY) wakerobot(iRobot_fd);
        if (BUTTONA) {

            x = joy.axis[0]/32768.0;
            x /= 2.0;
            y = -joy.axis[1]/32768.0;

            //boost = (joy.button[5]) ? 1.5 : 1.0;
            if(BUTTONRB){
              boost=1.5;
            }
            else{
              boost=1;            
            }
            fprintf(stderr, "%g %g %g\n", x, y, boost);

            robot_go(iRobot_fd, x, y, boost);

        }
        else robot_go(iRobot_fd, 0.0, 0.0, 1.0);
    }

    robot_go(iRobot_fd, 0.0, 0.0, 1.0);
    return 0;
}

