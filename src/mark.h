#include <stdio.h>

typedef struct
{
    int up;
    int down;
}grafic;



int convert(double value, double d);
void citire_fis(int *N, double *d, int *k, int *p_start, int *p_target, int **values, FILE *infile, int *maxim, int *minim);
void creare_grafic(grafic **mark, const int *values, int N, int n, int minim);