#ifndef JOY_H
#define JOY_H
/*
 Joystick header file
*/

/*
 * structure to hold joystick data
 */
 
struct joy {
	int num_of_axis;
	int num_of_buttons;
	char joystick_name[80];
	char button[20];
	int axis[20];
};

/*
 * There is no reason why we can't have more than one joy stick.
 * However, to keep the code simple we read only one joystick.
 *
 */

extern struct joy joy;


long init_joy(); /* returns zero on success. Non zero on failure */

// Buttonmapping
#define BUTTONA     joy.button[0]
#define BUTTONB     joy.button[1]
#define BUTTONX     joy.button[2]
#define BUTTONY     joy.button[3]
#define BUTTONLB    joy.button[4]
#define BUTTONRB    joy.button[5]
#define BUTTONSTART     joy.button[6]
#define BUTTONPOWER     joy.button[7]
#define BUTTONLEFTJOY   joy.button[8]
#define BUTTONRIGHTJOY  joy.button[9]
#define BUTTONDUP       joy.button[10]
#define BUTTONDDOWN     joy.button[11]
#define BUTTONDLEFT     joy.button[12]
#define BUTTONDRIGHT    joy.button[13]
#define BUTTONBACK      joy.button[14]



#endif
