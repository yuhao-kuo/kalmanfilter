
#include <stdint.h>
#include <stdbool.h>
#include "kalman.h"

void kalmanInit(Kalman_t *obj)
{
    // changed
    obj->P = 10;

    // static change
    obj->Q = 120;
    obj->R[0] = 120;
    obj->R[1] = 120;
}

bool kalmanSetP(Kalman_t *obj, uint32_t p)
{
    obj->P = p;
    return true;
}

bool kalmanSetQ(Kalman_t *obj, uint32_t q)
{
    obj->Q = q;
    return true;
}

bool kalmanSetR(Kalman_t *obj, uint32_t r1, uint32_t r2)
{
    obj->R[0] = r1;
    obj->R[1] = r2;
    return true;
}

bool kalmanSetDB(Kalman_t *obj, uint16_t db)
{
    obj->DB = db;
    return true;
}

bool kalmanSetNewX(Kalman_t *obj, uint32_t x1, uint32_t x2)
{
    obj->X[0] = (x1 + x2) >> 1;
    return true;
}

uint16_t kalmanfilter(Kalman_t *obj, uint16_t sen1, uint16_t sen2)
{
    uint32_t var = 0;
    uint32_t var1 = sen1 * obj->DB;
    uint32_t var2 = sen2 * obj->DB;

    uint32_t a, d, e, p, g1, g2;

    // Predict
    obj->X[1] = obj->X[0];
    obj->P += obj->Q;
    p = obj->P;

    // Update
    a = p + obj->R[0];
    d = p + obj->R[1];
    e = p / (a * d - p * p);

    g1 = e * d - e * p;
    g2 = e * a - e * p;

    obj->P = (1 - (g1 + g2)) * p;

    var = obj->X[1] + g1 * (var1 - obj->X[1]) + g2 * (var2 - obj->X[1]);
    obj->X[0] = var;

    return var / obj->DB;
}

