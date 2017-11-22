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

int setup_signal_handler(int fd);

int main(int argc, char *argv[])
{
	int fbfd = 0;
	int gpfd = 0;

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

	if(setup_signal_handler(gpfd) == -1){
		exit(EXIT_FAILURE);
	}

	printf("SNAKE GAME\n");

	init_snakegame(&fbfd);

	while(1){
		move_snake(snake.dir, &fbfd, &gpfd);
		if(snake.length >= 3){
			usleep(100*1000);
		}
		if(snake.length >= 6){
			usleep(50*1000);
		}
		usleep(150*1000);
	}

 
	exit_success(&fbfd, &gpfd);

	return 0; 
}
 
	exit_success();

	return 0; 
}
