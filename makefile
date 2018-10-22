all: main.o main.exe test.o test.exe
main.o: main.c
	gcc -std=c99 -c main.c
main.exe: main.o
	gcc -o main.exe main.o
test.o: test.c
	gcc -std=c99 -c test.c
test.exe: test.o
	gcc -o test.exe test.o
run_tests:
	./test.exe
run:
	./main.exe
clear:
	rm *.exe *.o
