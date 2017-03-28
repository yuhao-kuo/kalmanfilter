
/**
 * file: kmath.c
 * remark: kalman filter math library
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

#include <math.h>
#include "kmath.h"

/** ���� */
double kmath_square(double d)
{
    return d * d;
}

/** ������ */
double kmath_mean(void *data, int len)
{
    int i;
    double x = 0;
    double *buffer = (double*)data;
    for(i=0; i<len; i++)
    {
        x += buffer[i];
    }
    return (double)(x / len);
}

/** ��t */
double kmath_var(void *data, int len)
{
    double *buf = (double *)data;
    double m = kmath_mean(data, len);
    double sigma = 0.0;
    int i;
    for(i=0; i<len; i++)
    {
        sigma += kmath_square(buf[i] - m);
    }
    return sigma / (double)(len - 1);
}

/** �зǮt */
double kmath_std(void *data, int len)
{
    return sqrt(kmath_var(data, len));
}

/** ���x�} */
void kmath_transpose(int *src, int *dst, int w, int h)
{
    int x, y;
    for (x=0; x<w; x++)
    {
        for (y=0; y<h; y++)
        {
            *(dst + x * h + y) = *(src + y * w + x);
        }
    }
}
