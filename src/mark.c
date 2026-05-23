#include <stdio.h>
#include "mark.h"
#include <stdlib.h>
#include <string.h>


int cmmdc(int a, int b)
{
    while(b != 0)
    {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}


grafic adunare(grafic a, grafic b)
{
    if (a.up == 0) return b;
    if (b.up == 0) return a;

    grafic c;
    c.up = a.up * b.down + b.up * a.down;
    c.down = a.down * b.down;
    
    int div = cmmdc(c.up, c.down);
    c.up /= div;
    c.down /= div;
    
    return c;
}

grafic inmultire(grafic a, grafic b)
{
    grafic c;
    c.up = a.up * b.up;
    c.down = a.down * b.down;
    
    int div = cmmdc(c.up, c.down);
    if (div != 0)
    {
        c.up /= div;
        c.down /= div;
    }
    return c;
}


int convert(double value, double d)
{
    return (int)(value/d);
}


void citire_fis(int *N, double *d, int *k, int *p_start, int *p_target, int **values, FILE *infile, int *maxim, int *minim)
{
    double start, target;
    fscanf(infile, "%d", N);
    fscanf(infile, "%lf", d);
    fscanf(infile, "%d", k);
    fscanf(infile, "%lf", &start);
    fscanf(infile, "%lf", &target);

    *values = malloc((*N) * sizeof(int));

    double temp;
    *maxim = 0;
    *minim = 10000000;
    for(int i = 0; i < *N; i++)
    {
        fscanf(infile, "%lf", &temp);
        int t = convert(temp, *d);
        if(t > *maxim) *maxim = t;
        if(t < *minim) *minim = t;
        (*values)[i] = t;
    }
    *p_start = convert(start, *d) - *minim;
    *p_target = convert(target, *d) - *minim;
}


void creare_grafic(grafic **mark, const int *values, int N, int n, int minim)
{
    for(int i = 0; i < N-1; i++)
    {
        mark[values[i]-minim][values[i+1]-minim].up++;
    }
    
    for(int i = 0; i < n; i++)
    {
        int k = 0;
        for(int j = 0; j < n; j++)
        {
            k+=mark[i][j].up;
        }
        for(int j = 0; j < n; j++)
        {
            if(mark[i][j].up != 0)
            {
                mark[i][j].down = k;
            }
        }
    }

}