
kalman1d: main.c KalmanFilter.c kmath.c KalmanFilter.h kmath.h
	gcc -o kalman1d.o main.c KalmanFilter.c kmath.c -g -lm

clean:
	find . -name "*.o" -type f -delete
	find . -name "*.o.d" -type f -delete
	find . -name "*.log" -type f -delete