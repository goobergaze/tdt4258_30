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
#include "game.h"

void exit_success(void);
void exit_failure(void);
void flush_fb(void);
void button_handler(int);

// Snake functions
void setup_framebuffer(int);
void init_snakegame(void);
void place_food(void);
int collision(Position);
void draw_element(int, int, uint16_t);
void draw_pixel(int, int, uint16_t);
void fill_screen(uint16_t);
void move_snake(enum direction);
void iterate_game(void);

// File descriptors
int fbfd = 0, gpfd = 0;


int main(int argc, char *argv[])
{
	fbfd = open("/dev/fb0", O_RDWR);
	if (fbfd == -1) {
		printf("Error when trying to open framebuffer\n");
		exit(EXIT_FAILURE);
	}

	gpfd = open("/dev/gamepad", O_RDWR);
	if (gpfd == -1) {
		printf("Error when trying to open gamepad device\n");
		close(fbfd);
		exit(EXIT_FAILURE);
	}

	if (setup_signal_handler(gpfd) == -1) {
		exit_failure();
	}

	init_snakegame();

	if (draw_splash_screen(fbfd) == -1) {
		exit_failure();
	}
	// Wait until button press
	pause();

	if (setup_framebuffer(fbfd) == -1) {
		exit_failure();
	}

	// Fill in background
	fill_screen(WHITE);
	draw_element(ELEMS_X / 2, ELEMS_Y / 2, GREEN);
	place_food();
	flush_fb();

	while (1) {
		iterate_game();
	}

	exit_success();
	return 0;
}

void exit_success(void)
{
	close(fbfd);
	close(gpfd);
	exit(EXIT_SUCCESS);
}

void exit_failure(void)
{
	close(fbfd);
	close(gpfd);
	exit(EXIT_FAILURE);
}

void flush_fb(void)
{
	struct fb_copyarea rect;

	rect.dx = 0;
	rect.dy = 0;
	rect.width = SCREEN_WIDTH;
	rect.height = SCREEN_HEIGHT;

	ioctl(fbfd, 0x4680, &rect);
}

void button_handler(int signal)
{
	char input;
	if (read(gpfd, &input, 1) != -1) {
		switch (input) {
			case 0b11111110:
			case 0b11101111:
				move_snake(LEFT);
				break;
			case 0b11111101:
			case 0b11011111:
				move_snake(UP);
				break;
			case 0b11111011:
			case 0b10111111:
				move_snake(RIGHT);
				break;
			case 0b11110111:
			case 0b01111111:
				move_snake(DOWN);
				break;
		}
	} else {
		printf("Failed to read input from buttons\n");
	}
}
