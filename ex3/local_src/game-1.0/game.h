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
#define SCREEN_WIDTH   320
#define SCREEN_HEIGHT  240
#define SCREEN_BPP     16

// Defining an element to consist of 8*8 pixels
#define ELEM_PIXELS  8
#define ELEMS_X      (SCREEN_WIDTH / ELEM_PIXELS)   // 40
#define ELEMS_Y      (SCREEN_HEIGHT / ELEM_PIXELS)  // 30
#define MAX_LENGTH   100

// Size of framebuffer memory
#define FRAMEBUFFER_SIZE  SCREEN_WIDTH * SCREEN_HEIGHT * SCREEN_BPP / 8

// Colour definitions
#define RED    0xf800
#define GREEN  0x07e0
#define WHITE  0xffff

enum direction {
	UP = 1,
	DOWN = -1,
	RIGHT = 2,
	LEFT = -2
};

typedef struct {
	int x;
	int y;
} Position;

typedef struct {
	Position pos[MAX_LENGTH];
	enum direction dir;
	uint16_t col;
	uint8_t length;
	int speed;
} Snake;

typedef struct {
	Position pos;
	uint16_t col;
} Food;