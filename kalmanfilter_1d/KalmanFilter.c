
/**
 * file: KalmanFilter.c
 * remark: kalman filter one-dimensional
 * author: yuhao

 * license:
    MIT License

    Copyright (c) 2017 Yu-Hao Kuo

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
 */

#include "kmath.h"
#include "KalmanFilter.h"

KalmanFilter_t KalmanFilter(void *obj, KalmanFilter_t source, KalmanFilter_t cmd)
{
    KalmanFilter_Obj_t *kf = (KalmanFilter_Obj_t*)obj;
    kf->V[kf->Index] = 0.5 * ( source - cmd );
    kf->Z = cmd + kf->V[kf->Index];
    kf->R = kmath_square(kmath_std(kf->V, ARRAY_SIZE));
    kf->W[kf->Index] = 0.01 * source;
    kf->Q = kmath_square(kmath_std(kf->W, ARRAY_SIZE));
    kf->_X = kf->X;
    kf->_P = kf->P + kf->Q;
    kf->K = kf->_P / ( kf->_P + kf->R );
    kf->X = kf->_X + kf->K * ( kf->Z - kf->_X );
    kf->P = ( 1 - kf->K ) * kf->_P;
    kf->Index++;
    kf->Index %= ARRAY_SIZE;
    return kf->X;
}


