#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int draw_splash_screen(int);
int setup_signal_handler(int);
void button_handler(int);
void iterate_game(void);

// Driver file descriptors
int fd_fb0, fd_gamepad;


int main(int argc, char *argv[])
{
	// Open the gamepad driver
	fd_gamepad = open("/dev/gamepad", O_RDONLY);
	if(fd_gamepad == -1)
	{
		puts("Failed to open gamepad driver.");
		exit(EXIT_FAILURE);
	}

	// Open the framebuffer device
	fd_fb0 = open("/dev/fb0", O_WRONLY);
	if(fd_fb0 == -1)
	{
		puts("Failed to open framebuffer device.");
		exit(EXIT_FAILURE);
	}

	// Draw the splash screen
	if(draw_splash_screen(fd_fb0) == -1)
	{
		exit(EXIT_FAILURE);
	}

	// Enable listening to signals from the gamepad driver
	if(setup_signal_handler(fd_gamepad) == -1)
	{
		exit(EXIT_FAILURE);
	}



	// Main game loop
	while(1)
	{
		iterate_game();
	}

	// Release the drivers and skedaddle
	close(fd_fb0);
	close(fd_gamepad);

	exit(EXIT_SUCCESS);
}


void button_handler(int signo)
{
	uint8_t button_status;
	read(fd_gamepad, &button_status, 1);
	printf("Button status: %u\n", button_status);
}

void iterate_game(void)
{
	sleep(1);
	puts("I slept for a second. It probably was not good.");
}
