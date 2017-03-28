
/**
 * file: main.c
 * remark: kalman filter test main function
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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "KalmanFilter.h"
#include "kmath.h"

/************************* 數據 ******************************/

/** matlab linspace 產生線性數據 */
double matlab_linspace(double min, double max, int location, int allsize)
{
    return min + ((max - min) / allsize) * location;
}

/** matlab randn 模擬randn功能 */
double randn(void)
{
    return ((double)(rand() % 100000) / 10000) * ((rand() % 2) ? 1 : -1);
}



/************************ 波形模擬 *****************************/

/** 產生加速模型 */

void *speed_profile(const int32_t startSpeed,
                    const int32_t endSpeed,
                    const int32_t maxSpeed,
                    int32_t accSpeed,
                    int32_t distance,
                    void *data)
{
    double *d = (double*)data;
    const int32_t dist = (int32_t)distance;
    int32_t thisSpeed = startSpeed;
    int32_t dtims = 0;
    int32_t startaddr = 0;

    while(distance--)
    {
        if(accSpeed != 0)
            dtims = (thisSpeed - endSpeed) / accSpeed;

        if(dtims < distance)
        {
            if(thisSpeed != maxSpeed)
            {
                *(d + startaddr)  = (double)(thisSpeed >= maxSpeed) ? maxSpeed : thisSpeed + accSpeed;
                thisSpeed = (thisSpeed >= maxSpeed) ? maxSpeed : thisSpeed + accSpeed;
            }
            else
            {
                *(d + startaddr) = (double)thisSpeed;
                thisSpeed = maxSpeed;
            }
        }
        if(dtims >= distance)
        {
            *(d + startaddr)  = thisSpeed - accSpeed;
            thisSpeed = thisSpeed - accSpeed;
        }
        startaddr++;
    }
}


/************************** 資料操作 ********************************/

/** 資料串接 */
void doublencmp(double *destination, ssize_t cmpadd, const double *source, ssize_t len)
{
    ssize_t cnt;
    for(cnt=0; cnt<len; cnt++, cmpadd++)
    {
        *(destination + cmpadd) = *(source + cnt);
    }
}


/***************************************************************/

#define maxdata 3000
#define testdata    maxdata/3
int main()
{
    int16_t i = 0;

    // test data
    double pathpz[3][maxdata];
    double pz[maxdata];   //完美值
    double z[maxdata];  //加上觀測雜訊的觀測值
    double w[maxdata];
    double v[maxdata];

    /* 亂數種子 */
    srand(time(NULL));

    /* 產生模擬資料 */
    /*speed_profile(0, 0, 0, 10, testdata, pathpz[0]);  //產生加減速狀態模擬數據
    speed_profile(0, 0, 1500, 1, testdata, pathpz[1]);
    speed_profile(0, 0, 0, 0, testdata, pathpz[2]);
    doublencmp(pz, 0, pathpz[0], testdata);
    doublencmp(pz, testdata, pathpz[1], testdata);
    doublencmp(pz, testdata*2, pathpz[2], testdata);*/
    for(i=0; i<maxdata; i++)
    {
        pz[i] = matlab_linspace(4, 5, i, maxdata);     // 線性命令數據
        w[i] = 0.5 * randn();   // 隨機雜訊

        z[i] = pz[i] + w[i];    // 實際回授數值
        v[i] = 0.01 * randn();  // 隨機高斯分布
    }

    printf("data create ok !!!\n");

    /* kalman filter */
    KalmanFilter_Obj_t kf;

    kf.K = 0;
    kf.P = 1;
    kf.X = 1;
    kf._P = 1;
    kf._X = 0;


    /* file io */
    FILE *pf;
    pf = fopen("C:\\Users\\User\\Desktop\\test.txt", "w+");
    if(pf == NULL)
    {
        printf("file open error!!\n");
        fclose(pf);
        exit(-1);
    }

    for(i=0; i<maxdata; i++)
    {
        /** kelman filter */
        KalmanFilter(&kf, z[i] ,pz[i]);

        /** save to file */
        fprintf(pf, "%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n",
                pz[i],
                z[i],
                kf.Q,
                kf.Z,
                kf.R,
                kf._X,
                kf._P,
                kf.X,
                kf.P,
                kf.K
        );
    }

    /* close file io */
    fclose(pf);
    printf("data test done\n");

    return 0;
}
