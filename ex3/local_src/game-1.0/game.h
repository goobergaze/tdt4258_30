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
#define RED    0x00f8;
#define GREEN  0xe007;
#define WHITE  0xffff;

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