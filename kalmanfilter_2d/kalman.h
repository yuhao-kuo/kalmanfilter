


#ifndef __KALMAN_H__
#define __KALMAN_H__

#ifdef __cpluplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#define __weak __attribute__((weak))

typedef struct {
    /* Kalman filter variables */
    double P;
    double Q;
    double X[2];
    double R[2];
} Kalman_t;

extern void kalmanInit(Kalman_t *obj);

int32_t kalmanfilter(Kalman_t *obj, int32_t sen1, int32_t sen2);

#ifdef __cpluplus
}
#endif

#endif
