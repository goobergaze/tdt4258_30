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


// Screen definitions
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SCREEN_BPP 16

// Defining an element to consist of 8*8 pixels
#define ELEM_PIXELS 8
#define ELEMS_X (SCREEN_WIDTH/ELEM_PIXELS)   //40
#define ELEMS_Y (SCREEN_HEIGHT/ELEM_PIXELS)  //30
#define MAX_LENGTH 10

// Colour definitions
const uint16_t RED = 0xf800;
const uint16_t GREEN = 0x07e0;
const uint16_t WHITE = 0xffff;


typedef struct {
	int x;
	int y;
}Position;

enum direction {
	UP = 1,
	DOWN = -1,
	RIGHT = 2,
	LEFT = -2
};

typedef struct {
	Position pos[MAX_LENGTH];
	enum direction dir;
	uint16_t col;
	uint8_t length;
}Snake;

typedef struct {
	Position pos;
	uint16_t col;
}Food;

Snake snake;
Food food;
uint16_t *framebuffer;

struct fb_copyarea rect;
int fbfd = 0, gpfd = 0;

//Functions:
void init_snakegame();
void place_food();
void draw_pixel(int x, int y, uint16_t colour);
void draw_element(int x, int y, uint16_t colour);
int collision(Position pos);
void move_snake(enum direction dir);
void exit_success();
void flush_fb();
void button_handler(int signal);
void delay(int milliseconds);

void delay(int milliseconds)
{
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}

void init_snakegame(){
	snake.col = GREEN;
	snake.pos[0].x = ELEMS_X/2;
	snake.pos[0].y = ELEMS_Y;
	snake.dir = UP;
	snake.length = 1;

    food.col = RED;

    // Fill background 
    memset(framebuffer, WHITE, SCREEN_WIDTH * SCREEN_HEIGHT * SCREEN_BPP/8);
   /* for (uint8_t i = 0; i < SCREEN_WIDTH; i++){
		for (uint8_t j = 0; j < SCREEN_HEIGHT; j++) {
			draw_pixel(i,j, WHITE);
		}
	}*/

	draw_element(snake.pos[0].x, snake.pos[0].y, snake.col);
	place_food();

	flush_fb();
}

void place_food(){
	srand(time(NULL));
	food.pos.x = random() % ELEMS_X; 
	food.pos.y = random() % ELEMS_Y;

	if(collision(food.pos)) {
		place_food();
	} else {
		draw_element(food.pos.x, food.pos.y, food.col);
	}
}

void draw_pixel(int x, int y, uint16_t colour) {
	if(x < SCREEN_WIDTH && x >= 0 && y < SCREEN_HEIGHT && y >= 0) {
		framebuffer[x + y * SCREEN_WIDTH] = colour;
	} else {
		printf("Error, can't draw pixel outside of screen.");
	}
}

void draw_element(int x, int y, uint16_t colour) {
	uint8_t i, j;
	for(i = 0; i < ELEM_PIXELS; i++) {
		for(j = 0; j < ELEM_PIXELS; j++) {
			draw_pixel(x * ELEM_PIXELS + i, y * ELEM_PIXELS + j, colour);
		}
	}
}

int collision(Position pos){
	if(pos.x < 0 || pos.x > ELEMS_X || pos.y < 0 || pos.y > ELEMS_Y) return 1;
	uint8_t i;
	for( i = 0;i < snake.length;i++) {
		if(snake.pos[i].x == pos.x && snake.pos[i].y == pos.y) return 1;
	}
	return 0;
};

void move_snake(enum direction dir){
	
	if (snake.dir == -dir) return;
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

	if (collision(temp)){
		printf("GAME OVER: You crashed and lost! Your score: %d\n", snake.length-1);
		memset(framebuffer, RED, SCREEN_WIDTH * SCREEN_HEIGHT * SCREEN_BPP/8);
		flush_fb();
		exit_success();
		
	}
    uint8_t i;
    for (i = snake.length; i > 0; i--) {
		snake.pos[i] = snake.pos[i-1];
	}

	snake.pos[0] = temp;

	if (temp.x == food.pos.x && temp.y == food.pos.y){
		snake.length++;
		if(snake.length == MAX_LENGTH){
			printf("You won!\n");
			memset(framebuffer, GREEN, SCREEN_WIDTH * SCREEN_HEIGHT * SCREEN_BPP/8);
			flush_fb();
			exit_success();
		}
		place_food();
	}else{
		draw_element(snake.pos[snake.length].x, snake.pos[snake.length].y, WHITE);
	}
	draw_element(temp.x, temp.y, snake.col);
	flush_fb();
};

void exit_success(){
	close(fbfd);
	close(gpfd);
	exit(EXIT_SUCCESS);
};

void flush_fb() {
	ioctl(fbfd, 0x4680, &rect);
};

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
		delay(500);
	}

 
	exit_success();

	return 0; 
}

void button_handler(int signal) {
	char input;
	if(read(gpfd, &input, 1) != -1) { 


		switch(input) {
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

		if(input) flush_fb();
		
	} else{
		printf("Failed to read input from buttons\n");
	}
}