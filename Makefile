CC=c99

build: main/main.c
	$(CC) -O3 -o pi-collision-calculator src/main.c glad.c -Wall -Iinclude -lGL -lglfw -ldl

