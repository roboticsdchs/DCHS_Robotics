#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <linux/joystick.h>
#include <unistd.h> //Added by NN on May 29
#include "joy.h"

#define WHEREAMI fprintf(stderr, "%s: %d\n", __FILE__, __LINE__)
#define DEBUG(x) fprintf(stderr, "%s = %ld\n", #x, (long) x)



static char *joy_locations[] = {
	"/dev/js0",
	"/dev/input/js0",
	NULL
}; /* A more sensible solution is to read from a configuration file */

struct joy joy;

#define SAMPLES_PER_SECOND 100
#define USLEEP (1000000/SAMPLES_PER_SECOND)

static int joystick_started;

void static monitor_joy(){
	int i, joy_fd, x;
	struct js_event js;

	if (joystick_started) return; /* Already running */
	joystick_started = 1;

	for (joy_fd=-1, i=0; joy_fd==-1 && joy_locations[i]!=NULL;i++) {
		 joy_fd = open(joy_locations[i] , O_RDONLY);
	}
		
	if(  joy_fd == -1 ){
		puts( "Couldn't open joystick " );
		while(1)usleep(USLEEP*10);
	}

	ioctl( joy_fd, JSIOCGAXES, &joy.num_of_axis );
	ioctl( joy_fd, JSIOCGBUTTONS, &joy.num_of_buttons );
	ioctl( joy_fd, JSIOCGNAME(80), joy.joystick_name );
	

	fprintf(stderr, "Found: %s\n", joy.joystick_name );

	fprintf(stderr, "number of axis: %d\n", joy.num_of_axis);
	fprintf(stderr, "number of buttons: %d\n", joy.num_of_buttons);

	fcntl( joy_fd, F_SETFL, O_NONBLOCK );   

	while( 1 ){
		usleep(USLEEP);
	
		read(joy_fd, &js, sizeof(struct js_event));

		switch (js.type & ~JS_EVENT_INIT){
			case JS_EVENT_AXIS:
				joy.axis   [ js.number ] = js.value;
				break;
			case JS_EVENT_BUTTON:
				joy.button [ js.number ] = js.value;
				break;
		}
                       
	}
}
void static *ThreadProcs(void *threadid){
	fprintf(stderr, "Starting joy thread\n");
	monitor_joy();
}
long init_joy() {
	pthread_t joy_thread;
	int timeout_count;
	long rc;

	fprintf(stderr, "Initializing joystick\n");
	
	rc = pthread_create(&joy_thread, NULL, ThreadProcs, NULL);
	WHEREAMI;
	if (rc){
		fprintf(stderr, "pthread error:  %ld\n", rc);
		return rc;
	}

	timeout_count=0;
	fprintf(stderr, "waiting for joystick to be found\n");
	while (joy.num_of_axis==0 && joy.num_of_buttons==0) {
		sleep(1); 
		timeout_count++;
		if (timeout_count==10) {
			fprintf(stderr, "No joystick found!\n");
			return rc;
		}
	}
	return rc;
}

