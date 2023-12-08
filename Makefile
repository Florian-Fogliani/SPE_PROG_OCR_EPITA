#Makefile

CC=gcc
CFLAGS = -Wall -Wextra $(shell pkg-config --cflags sdl2 SDL2_image) -lm
LDLIBS = $(shell pkg-config --libs sdl2 SDL2_image) -lm

SRC3= hough.c cuttertest.c
OBJ3=${SRC3:.c=.o}
EXE3=${SRC3:.c=}


all:cuttertest

-include  ${DEP}

cuttertest: ${OBJ3}


.PHONY: clean


clean:
	${RM} ${OBJ} 
	${RM} ${OBJ2}
	${RM} ${OBJ3}
	${RM} ${OBJ4}
	${RM} ${DEP} 
	${RM} ${EXE2}
	${RM} ${EXE3}
	${RM} ${DEP4}
	${RM} solver 
	${RM} grayscale
	${RM} cuttertest
	${RM} process
	${RM} *result
	${RM} *result.bmp

#end
