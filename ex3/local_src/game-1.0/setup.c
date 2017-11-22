#include "game.h"

void button_handler(int);

// Symbols for accessing binary data included by the linker
extern unsigned char _binary_splash_bin_start;
extern unsigned char _binary_splash_bin_end;


int draw_splash_screen(int fd)
{
	// '_binary_splash_bin_size' does not work, probably because OS prevents it
	if (&_binary_splash_bin_end - &_binary_splash_bin_start != FRAMEBUFFER_SIZE) {
		puts("Splash graphic size does not match framebuffer size.");
		return -1;
	}

	// Feed the image data to the framebuffer
	if (write(fd, &_binary_splash_bin_start, FRAMEBUFFER_SIZE) == -1) {
		puts("Failed to draw splash screen.");
		return -1;
	}

	return 0;
}

int setup_signal_handler(int fd)
{
	// Indicate that no signal besides SIGIO should be blocked
	sigset_t empty_mask;
	sigemptyset(&empty_mask);

	// Define the action for receiving a signal from the gamepad driver
	const struct sigaction act = {
		.sa_handler = button_handler,
		.sa_mask = empty_mask
	};

	// Enable the button handler using the action object
	if (sigaction(SIGIO, &act, NULL) == -1) {
		puts("Failed to install signal-catching function.");
		return -1;
	}

	// Specify that this process is the owner of the gamepad driver
	if (fcntl(fd, F_SETOWN, getpid()) == -1) {
		puts("Failed to specify gamepad driver owner.");
		return -1;
	}

	// Set the FASYNC flag so that this process can receive notifications
	if (fcntl(fd, F_SETFL, FASYNC | fcntl(fd, F_GETFL)) == -1) {
		puts("Failed to set FASYNC flag in gamepad driver.");
		return -1;
	}

	return 0;
}
