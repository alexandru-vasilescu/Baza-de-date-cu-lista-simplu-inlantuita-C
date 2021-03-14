build: tema1.o lib.o
	gcc -Wall -g tema1.o lib.o -o tema1
.c.o:
	gcc -Wall -g -c $?
clean:
	rm *.o
	rm tema1

