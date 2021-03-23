build:
	gcc -o hello-world hello-world.c -lulfius

start:
	./hello-world

dev: build start
