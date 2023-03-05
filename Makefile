all: compile exec

compile:
	gcc -Wall -pedantic -g matrixExample.c vector.c matrix.c -o ./bin/matrixExample

exec:
	./bin/matrixExample

debug:
	gcc matrixExample.c matrix.c -g -o ./bin/matrixExample

assembler:
	gcc -S -masm=intel matrixExample.c matrix.c

decompile:
	objdump -d -M intel ./bin/matrixExample.exe > ./bin/matrixExample.s