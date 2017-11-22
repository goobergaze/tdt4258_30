#include "snake.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <time.h>

int main(int argc, char *argv[])
{
	rect.dx = 0;
	rect.dy = 0;
	rect.width = SCREEN_WIDTH;
	rect.height = SCREEN_HEIGHT;
	fbfd = open("/dev/fb0", O_RDWR);
	if(fbfd == -1) {
		printf("Error when trying to open framebuffer\n)");
		exit(EXIT_FAILURE);
	}
	int screensize = SCREEN_WIDTH * SCREEN_HEIGHT * SCREEN_BPP/8; 	
	framebuffer = (uint16_t*) mmap(NULL,screensize,PROT_READ |PROT_WRITE, MAP_SHARED, fbfd, 0);
	if(framebuffer == MAP_FAILED) {
		printf("Error when trying to map framebuffer\n");
		close(fbfd);
		exit(EXIT_FAILURE);
	}

	gpfd = open("/dev/gamepad", O_RDWR);
	if(gpfd == -1) {
		printf("Error when trying to open gamepad device\n)");
		close(fbfd);
		exit(EXIT_FAILURE);
	}
	if(signal(SIGIO, &button_handler) == SIG_ERR) {
		printf("Error when trying to create signal handler\n");
		close(fbfd);
		close(gpfd);
		exit(EXIT_FAILURE);
	}
	
	if(fcntl(gpfd, F_SETOWN, getpid()) == -1) {
		printf("Error when trying to set owner of gamepad device\n");
		close(fbfd);
		close(gpfd);
		exit(EXIT_FAILURE);
	}

	long flags = fcntl(gpfd, F_GETFL);
	if(fcntl(gpfd, F_SETFL, flags | FASYNC) == -1) {
		printf("Error: failed to set FASYNC flag\n");
		close(fbfd);
		close(gpfd);
		exit(EXIT_FAILURE);
	}


	printf("SNAKE GAME\n");

	init_snakegame();

	while(1){
		move_snake(snake.dir);
		if(snake.length >= 3){
			sleep(100);
		}
		if(snake.length >= 6){
			sleep(50);
		}
		sleep(50);
	}

 
	exit_success();

	return 0; 
}
