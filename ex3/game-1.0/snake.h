#include <stdint.h>

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