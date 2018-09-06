
kalman: kalman.c
	gcc -c kalman.c kalman.h -I . -g

test: main.c kalman
	gcc -o main.o main.c kalman.o -I . -g

clean:
	rm -rf *.o
	rm -rf *.gch
