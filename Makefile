compile: list.c list.h main.c hash.c hash.h
	gcc -Wall -o dictionary list.c hash.c main.c
run: dictionary
	./dictionary words.txt 2
