#MakeFile

CC = gcc
CFLAGS = -Wall -Wextra 'pkg-config --cflags sdl2 SDL2_image'
SRC = hough.c cutter.c
LDLIBS = 'pkg-config --libs sdl2 SDL2_image'
OBJ = ${SRC:.c=.o}
EXE = ${SRC:.c=}



all : cutter 

clean : 
	${RM} ${OBJ}
	${RM] ${EXE}
	
cutter : cutter.c hough.c

.PHONY : clean all
