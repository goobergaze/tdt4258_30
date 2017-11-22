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
#define RED 0xf800
#define GREEN 0X07e0
#define WHITE 0xffff



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


//Functions:
void init_snakegame(int *fbfd);
void place_food();
void draw_pixel(int x, int y, uint16_t colour);
void draw_element(int x, int y, uint16_t colour);
int collision(Position pos);
void move_snake(enum direction dir, int *fbfd, int *gpfd);
void exit_success(int *fbfd, int *gpfd);
void flush_fb(int *fbfd);
void button_handler(int signal, int *fbfd, int *gpfd);
