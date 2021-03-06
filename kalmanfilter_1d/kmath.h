
/**
 * file: kmath.h
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

#ifndef KMATH_H
#define KMATH_H

/** キよ
 * d      : キよ计
 * return : d ^ 2
*/
extern double kmath_square(double d);

/** キА计
 * data : ―キА计戈皚
 * len  : 皚
*/
extern double kmath_mean(void *data, int len);

/** よ畉
 * data : ―よ畉戈皚
 * len  : 皚
*/
extern double kmath_var(void *data, int len);

/** 夹非畉
 * data : ―夹非畉戈皚
 * len  : 皚
*/
extern double kmath_std(void *data, int len);

#endif // KMATH_H
