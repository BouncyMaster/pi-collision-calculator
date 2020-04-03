CC=c99
files=src/main.c src/file_ops.c

build: $(files)
	$(CC) -O2 -o pi-collision-calculator $(files) glad.c \
		-Wall -Iinclude -lGL -lglfw -ldl
