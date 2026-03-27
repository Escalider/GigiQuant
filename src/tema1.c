#include "liste.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double volatility(Node *head, double rand_avg, int n)
{
    Node *p = head;
    p = p->next;
    double sum = 0;
    while(p!=NULL)
    {
        sum+=pow((p->rand-rand_avg), 2);
        p = p->next;
    }
    sum/=(n-1);

    return sqrt(sum);
}


int main(int argc, char *argv[])
{
    double rand_avg;
    int n;
    FILE *infile = fopen(argv[1], "rt");
    if(infile == NULL)
    {
        puts("Nu s a deschis fisierul");
        exit(1);
    }
    Node *head = create_list(&rand_avg, &n, infile);
    fclose(infile);

    double vol = volatility(head, rand_avg, n);

    double Sharpe = (long)(rand_avg/vol * 1000)/1000.0;

    double rand_trun = (long)(rand_avg * 1000)/1000.0;
    double vol_trun = (long)(vol * 1000)/1000.0;

    FILE *outfile = fopen(argv[2], "wt");

    printf("%s", argv[2]);

    fprintf(outfile, "%.3f\n", rand_trun);
    fprintf(outfile, "%.3f\n", vol_trun);
    fprintf(outfile, "%.3f\n", Sharpe);

    fclose(outfile);

    clear_list(&head);
    return 0;
}