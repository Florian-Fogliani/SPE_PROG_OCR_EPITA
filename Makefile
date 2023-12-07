#Makefile

CC=gcc
CFLAGS = -Wall -Wextra $(shell pkg-config --cflags sdl2 SDL2_image) -lm
LDLIBS = $(shell pkg-config --libs sdl2 SDL2_image) -lm

SRC= solver.c draw.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}


SRC2=grayscale.c
OBJ2=${SRC2:.c=.o}
EXE2=${SRC2:.c=}

SRC3= hough.c cutter.c
OBJ3=${SRC3:.c=.o}
EXE3=${SRC3:.c=}

SRC4=process.c useful_maths.c network.c training.c
OBJ4=${SRC4:.c=.o}
DEP4= ${SRC4:.c=.d}

all:solver grayscale process cutter

-include  ${DEP}

solver: ${OBJ}
grayscale: ${OBJ2}
cutter: ${OBJ3}
process: ${OBJ4}


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
	${RM} cutter
	${RM} process
	${RM} *result
	${RM} *result.bmp

#end
