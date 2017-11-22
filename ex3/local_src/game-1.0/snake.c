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

void setup_framebuffer(int);
void init_snakegame(void);
void place_food(void);
int collision(Position);
void draw_element(int, int, uint16_t);
void draw_pixel(int, int, uint16_t);
void fill_screen(uint16_t);
void move_snake(enum direction);
void iterate_game(void);
void exit_success(void);
void flush_fb(void);

Snake snake;
Food food;

uint16_t *framebuffer;

void setup_framebuffer(int fd)
{
	framebuffer = (uint16_t*) mmap(NULL, FRAMEBUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	if (framebuffer == MAP_FAILED) {
		printf("Error when trying to map framebuffer\n");
	}
}

void init_snakegame(void)
{
	snake.col = GREEN;
	snake.pos[0].x = ELEMS_X / 2;
	snake.pos[0].y = ELEMS_Y / 2;
	snake.dir = UP;
	snake.length = 2;
	snake.speed = 250 * 1000;

	food.col = RED;
}

void place_food(void)
{
	srand(time(NULL));
	food.pos.x = random() % ELEMS_X;
	food.pos.y = random() % ELEMS_Y;

	if (collision(food.pos)) {
		place_food();
	} else {
		draw_element(food.pos.x, food.pos.y, food.col);
	}
}

int collision(Position pos)
{
	if (pos.x < 0 || pos.x >= ELEMS_X || pos.y < 0 || pos.y >= ELEMS_Y) {
		return 1;
	}

	uint8_t i;
	for (i = 0; i < snake.length; i++)
	{
		if (snake.pos[i].x == pos.x && snake.pos[i].y == pos.y) {
			return 1;
		}
	}

	return 0;
}

void draw_element(int x, int y, uint16_t colour)
{
	uint8_t i, j;
	for (i = 0; i < ELEM_PIXELS; i++) {
		for (j = 0; j < ELEM_PIXELS; j++) {
			draw_pixel(x * ELEM_PIXELS + i, y * ELEM_PIXELS + j, colour);
		}
	}
}

void draw_pixel(int x, int y, uint16_t colour)
{
	if (x < SCREEN_WIDTH && x >= 0 && y < SCREEN_HEIGHT && y >= 0) {
		framebuffer[x + y * SCREEN_WIDTH] = colour;
	} else {
		printf("Error, can't draw pixel outside of screen.");
	}
}

void fill_screen(uint16_t colour)
{
	memset(framebuffer, colour, FRAMEBUFFER_SIZE);
}

void move_snake(enum direction dir)
{
	if (snake.dir == -dir) {
		return;
	}

	snake.dir = dir;
	Position temp = snake.pos[0];

	switch (dir) {
		case UP:
			temp.y--;
			break;
		case DOWN:
			temp.y++;
			break;
		case RIGHT:
			temp.x++;
			break;
		case LEFT:
			temp.x--;
			break;
	}

	if (collision(temp)) {
		printf("GAME OVER: You crashed and lost! Your score: %d\n", snake.length - 2);
		fill_screen(RED);
		flush_fb();
		exit_success();
	}

	uint8_t i;
	for (i = snake.length; i > 0; i--) {
		snake.pos[i] = snake.pos[i - 1];
	}

	snake.pos[0] = temp;

	if (temp.x == food.pos.x && temp.y == food.pos.y) {
		snake.length++;
		if (snake.length == MAX_LENGTH) {
			printf("You won!\n");
			fill_screen(GREEN);
			flush_fb();
			exit_success();
		}

		place_food();
		if (snake.speed > 10 * 1000) {
			snake.speed -= 35 * 1000;
		}
	} else {
		draw_element(snake.pos[snake.length].x, snake.pos[snake.length].y, WHITE);
	}

	draw_element(temp.x, temp.y, snake.col);
	flush_fb();
}

void iterate_game(void)
{
	move_snake(snake.dir);
	usleep(snake.speed);
}
