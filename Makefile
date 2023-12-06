#MakeFile

CC = gcc
CFLAGS = -Wall -Wextra $(shell pkg-config --cflags sdl2 SDL2_image) -lm
SRC = hough.c cutter.c
LDLIBS = $(shell pkg-config --libs sdl2 SDL2_image) -lm
OBJ = ${SRC:.c=.o}
EXE = ${SRC:.c=}



all : cutter test

clean : 
	${RM} ${OBJ}
	${RM] ${EXE}
	
cutter : cutter.c hough.c
test : test.c

.PHONY : clean all
