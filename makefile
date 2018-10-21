all: main.o main.exe
main.o: main.c
	gcc -std=c99 -c main.c
main.exe: main.o
	gcc -o main.exe main.o
clear:
	rm *.exe *.o
