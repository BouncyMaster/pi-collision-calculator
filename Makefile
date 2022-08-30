LDFLAGS = -L/usr/X11R6/lib -L/usr/local/lib
LIBS = -lGL -lglfw -lm
INCS = -Iexternal/file_ops -Iexternal/glad/include -I /usr/local/include
CFLAGS = -std=c99 -O2 -march=native -Wall

SRC = src/main.c external/file_ops/file_ops.c external/glad/src/glad.c

pi-collision-calculator: ${SRC}
	${CC} -o $@ ${SRC} ${INCS} ${LDFLAGS} ${LIBS} ${CFLAGS}

tags:
	ctags `find src -name "*.c"`

clean:
	rm -f pi-collision-calculator tags
