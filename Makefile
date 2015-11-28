GCCFLAGS=-Wall -g

main.x: main.c
	gcc $(GCCFLAGS) -o main.x main.c
