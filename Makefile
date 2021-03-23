.DEFAULT_GOAL := dev

build:
	gcc -o hello-world hello-world.c -lulfius

clean:
	rm -f hello-world

dev: clean build start

start:
	./hello-world
