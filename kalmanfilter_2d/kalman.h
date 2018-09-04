


#ifndef __KALMAN_H__
#define __KALMAN_H__

#ifdef __cpluplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    /* Kalman filter variables */
    uint32_t P;
    uint32_t Q;
    uint32_t X[2];
    uint32_t R[2];
    uint16_t DB;
} Kalman_t;

extern void kalmanInit(Kalman_t *obj);

bool kalmanSetP(Kalman_t *obj, uint32_t p);
bool kalmanSetQ(Kalman_t *obj, uint32_t q);
bool kalmanSetR(Kalman_t *obj, uint32_t r1, uint32_t r2);
bool kalmanSetDB(Kalman_t *obj, uint16_t db);
bool kalmanSetNewX(Kalman_t *obj, uint32_t x1, uint32_t x2);
uint16_t kalmanfilter(Kalman_t *obj, uint16_t sen1, uint16_t sen2);

#ifdef __cpluplus
}
#endif

#endif
