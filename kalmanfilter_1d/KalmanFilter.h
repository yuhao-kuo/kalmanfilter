
/**
 * file: KalmanFilter.h
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

#ifndef FALMANFILTER_H
#define FALMANFILTER_H

#include <stdint.h>

#define ARRAY_SIZE  16

typedef double KalmanFilter_t;

typedef struct {

    KalmanFilter_t V[ARRAY_SIZE];
    KalmanFilter_t Z;
    KalmanFilter_t R;
    KalmanFilter_t W[ARRAY_SIZE];
    KalmanFilter_t Q;

    KalmanFilter_t _X;
    KalmanFilter_t _P;
    KalmanFilter_t K;
    KalmanFilter_t X;
    KalmanFilter_t P;

    uint16_t Index;
} KalmanFilter_Obj_t;

extern KalmanFilter_t KalmanFilter(void *obj, KalmanFilter_t source, KalmanFilter_t cmd);

#endif  //FALMANFILTER_H
