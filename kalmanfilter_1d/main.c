
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
#include <getopt.h>
#include <time.h>
#include "KalmanFilter.h"
#include "kmath.h"

/************************* Data ******************************/

/** matlab linspace create datas */
double matlab_linspace(double min, double max, int location, int allsize)
{
    return min + ((max - min) / allsize) * location;
}

/** matlab randn */
double randn(void)
{
    return ((double)(rand() % 100000) / 10000) * ((rand() % 2) ? 1 : -1);
}



/************************ Waveform simulation *****************************/

/** create runner speed model */

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


/************************** Data operation ********************************/

/** data cmp */
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

int main(int argc, char *argv[])
{
    int16_t i = 0;
    int opt;
    char *logPath = "./kalman.log";
    
    if((opt = getopt(argc, argv, "ho:")) != -1) {
        switch(opt) {
            case 'o':   // output path
                logPath = optarg;
                break;
            case 'h':
            default:
                printf("help:\n");
                printf("\to: output data name, -o [output name]\n");
                return 0;
        }
    }

    printf("log name: %s\n", logPath);

    // test data
    double pathpz[3][maxdata];
    double pz[maxdata];
    double z[maxdata];
    double w[maxdata];
    double v[maxdata];

    /* 亂數種子 */
    srand(time(NULL));

    for(i=0; i<maxdata; i++)
    {
        pz[i] = matlab_linspace(4, 5, i, maxdata);
        w[i] = 0.5 * randn();

        z[i] = pz[i] + w[i];
        v[i] = 0.01 * randn();
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
    pf = fopen(logPath, "w+");
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
