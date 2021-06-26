LIBS = -lGL -lglfw -ldl -lm
INCS = -Iexternal/glad/include
CFLAGS = -std=c99 -O2 -march=znver1 -Wall

SRC = src/main.c src/file_ops.c external/glad/src/glad.c

pi-collision-calculator: $(SRC)
	$(CC) -o $@ $^ $(INCS) $(LIBS) $(CFLAGS)

gentags:
	ctags `find src -name "*.c"`

clean:
	rm -f pi-collision-calculator tags
