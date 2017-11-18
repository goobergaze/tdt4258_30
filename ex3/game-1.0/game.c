#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int setup_signal_handler();
void button_handler(int);
void iterate_game(void);

// Driver file descriptors
int fd_fb0, fd_gamepad;


int main(int argc, char *argv[])
{
	/****************************** Framebuffer ******************************/

	// Open the framebuffer device
	fd_fb0 = open("/dev/fb0", 0);
	if(fd_fb0 == -1)
	{
		puts("Failed to open framebuffer device.");
		exit(EXIT_FAILURE);
	}

	/******************************** Gamepad ********************************/

	// Open the gamepad driver with asynchronous signaling
	fd_gamepad = open("/dev/gamepad", O_RDONLY);
	if(fd_gamepad == -1)
	{
		puts("Failed to open gamepad driver.");
		exit(EXIT_FAILURE);
	}

	// Enable listening to signals from the gamepad driver
	if(setup_signal_handler() == -1)
	{
		exit(EXIT_FAILURE);
	}

	/**************************** The Game Itself ****************************/

	while(1)
	{
		iterate_game();
	}

	// Release the drivers and skedaddle
	close(fd_fb0);
	close(fd_gamepad);

	exit(EXIT_SUCCESS);
}


int setup_signal_handler()
{
	// Indicate that no signal besides SIGIO should be blocked
	sigset_t empty_mask;
	sigemptyset(&empty_mask);

	// Define the action for receiving a signal from the gamepad driver
	const struct sigaction act =
	{
		.sa_handler = button_handler,
		.sa_mask = empty_mask
	};

	// Enable the button handler using the action object
	if(sigaction(SIGIO, &act, NULL) == -1)
	{
		puts("Failed to install signal-catching function.");
		return -1;
	}

	// Specify that this process is the owner of the gamepad driver
	if(fcntl(fd_gamepad, F_SETOWN, getpid()) == -1)
	{
		puts("Failed to specify gamepad driver owner.");
		return -1;
	}

	// Set the FASYNC flag so that this process can receive notifications
	if(fcntl(fd_gamepad, F_SETFL, FASYNC | fcntl(fd_gamepad, F_GETFL)) == -1)
	{
		puts("Failed to set FASYNC flag in gamepad driver.");
		return -1;
	}

	return 0;
}

void button_handler(int signo)
{
	puts("I felt a button press ( ͡º ͜ʖ ͡º)");
}

void iterate_game(void)
{
	sleep(1);
	puts("I slept for a second. It probably was not good.");
}
