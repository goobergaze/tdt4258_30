#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int setup_signal_handler(int);
void button_handler(int);
void iterate_game(void);

// Framebuffer file descriptor
int fb0;


int main(int argc, char *argv[])
{
	/****************************** Framebuffer ******************************/

	// Open the framebuffer device
	fb0 = open("/dev/fb0", 0);
	if(fb0 == -1)
	{
		puts("Failed to open framebuffer device.");
		exit(EXIT_FAILURE);
	}

	/******************************** Gamepad ********************************/

	// Open the gamepad driver with asynchronous signaling
	int gamepad = open("/dev/gamepad", O_ASYNC);
	if(gamepad == -1)
	{
		puts("Failed to open gamepad driver.");
		exit(EXIT_FAILURE);
	}

	// Enable listening to signals from the gamepad driver
	if(setup_signal_handler(gamepad) == -1)
	{
		exit(EXIT_FAILURE);
	}

	/**************************** The Game Itself ****************************/

	while(1)
	{
		iterate_game();
	}

	// Release the drivers and skedaddle
	close(fb0);
	close(gamepad);

	exit(EXIT_SUCCESS);
}


int setup_signal_handler(int fd)
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
	if(fcntl(fd, F_SETOWN, getpid()) == -1)
	{
		puts("Failed to specify gamepad driver owner.");
		return -1;
	}

	// Set the FASYNC flag so that this process can receive notifications
	if(fcntl(fd, F_SETFL, FASYNC | fcntl(STDIN_FILENO, F_GETFL)) == -1)
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
