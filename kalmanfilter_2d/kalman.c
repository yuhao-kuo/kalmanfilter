
#include <stdint.h>
#include <stdbool.h>
#include "kalman.h"

__weak void kalmanInit(Kalman_t *obj)
{
    // changed
    obj->P = 10;

    // static
    obj->Q = 0.002;
    obj->R[0] = 0.1600;
    obj->R[1] = 0.7050;
}

int32_t kalmanfilter(Kalman_t *obj, int32_t sen1, int32_t sen2)
{
    double var = 0;
    double var1 = (double)sen1;
    double var2 = (double)sen2;

    double a, d, e, p, g1, g2;

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

    return var;
}

