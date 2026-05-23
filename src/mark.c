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


void reset(grafic *next, int n)
{
    for(int i = 0; i < n; i++)
    {
        next[i].up = 0;
        next[i].down = 1;
    }
}

void copiaza(grafic *next, grafic *current, int n)
{
    for(int i = 0; i < n; i++)
    {
        current[i].up = next[i].up;
        current[i].down = next[i].down;
    }
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

void markov(grafic **mark, int p_start, int p_target, int n, int k, FILE *outfile)
{
    grafic *current = calloc(n, sizeof(grafic));
    grafic *next = calloc(n, sizeof(grafic));

    char **matrice = (char **)calloc(50, sizeof(char *));
    for(int i = 0; i < 50; i++)
    {
        matrice[i] = (char *)calloc(15, sizeof(char));
    }

    for(int i = 0; i < n; i++) {
        current[i].down = 1;
        next[i].down = 1;
    }


    current[p_start].up = 1;
    current[p_start].down = 1;

    int contor = 0;

    if(p_start == p_target)
    {
        strcpy(matrice[contor++], "1");
    }
    else
    {
        strcpy(matrice[contor++], "0");
    }


    for(int i = 2; i <= k; i++)
    {
        reset(next, n); 
        
        for(int j = 0; j < n; j++)
        {
            if(current[j].up > 0)
            {
                for(int l = 0; l < n; l++)
                {
                    if(mark[j][l].up > 0)
                    {
                        grafic temp = inmultire(current[j], mark[j][l]);
                        next[l] = adunare(next[l], temp);
                    }
                }
            }
        }
        
        copiaza(next, current, n);
        
    if(current[p_target].up == 1 && current[p_target].down == 1)
    {
        strcpy(matrice[contor++], "1");
    }
    else if(current[p_target].up == 0)
    {
        strcpy(matrice[contor++], "0");
    }
    else
        sprintf(matrice[contor++], "%d/%d", current[p_target].up, current[p_target].down);
    }

    for(int i = 0; i < contor; i++)
    {
        fprintf(outfile, "%s", matrice[i]);
        if(i != contor-1) fprintf(outfile, "\n");
    }

    for(int i = 0; i < 50; i++) {
        free(matrice[i]);
    }
    free(matrice);
    free(current);
    free(next);
}