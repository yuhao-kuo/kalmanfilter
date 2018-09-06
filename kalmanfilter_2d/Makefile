
kalman: kalman.c
	gcc -c kalman.c kalman.h -I . -g

kalman2d: main.c kalman
	gcc -o kalman2d.o main.c kalman.o -I . -g

clean:
	rm -rf *.o
	rm -rf *.gch
