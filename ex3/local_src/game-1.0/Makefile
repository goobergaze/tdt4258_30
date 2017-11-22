CC = arm-cortexm3-uclinuxeabi-gcc
LD = arm-cortexm3-uclinuxeabi-gcc
OBJCOPY = arm-cortexm3-uclinuxeabi-objcopy

CFLAGS += -O3 -Wall -Wextra -Wno-unused -Wfloat-equal -Wformat-security
CPPFLAGS +=
LDFLAGS +=

game: game.o setup.o snake.o splash.o
	${LD} $^ -o $@ ${LDFLAGS}

splash.o: splash.bin
	${OBJCOPY} -I binary -O elf32-littlearm -B arm $< $@

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

.PHONY: all clean install

all: game

clean:
	-rm -f game *.o

install:
