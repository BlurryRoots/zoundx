clean:
	rm -f *.o
	rm -f zoundx

main:
	gcc -c -o z.o zoundx.c 2> error.log
	gcc -c -o m.o main.c 2> error.log
	gcc -o zoundx m.o z.o 2> error.log
	chmod +x zoundx

all: clean main