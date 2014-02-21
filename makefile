clean:
	rm -f *.o
	rm -f zoundx
	rm -rf bin
	mkdir bin

main:
	gcc -c -o bin/z.o src/zoundx.c 2> error.log
	gcc -c -o bin/m.o src/main.c 2> error.log
	gcc -o bin/zoundx bin/m.o bin/z.o 2> error.log
	chmod +x bin/zoundx

all: clean main