#include "liste.h"
#include "stive.h"
#include "arbori.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>





void task1(char *argv[])
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
}


void task2(char *argv[])
{
    City *top1 = NULL;
    City *top2 = NULL;
    City *top3 = NULL;
    char **mat;

    FILE *infile = fopen(argv[1], "rt");
    create_s(&top1, &top2, &top3, infile, &mat);

    // printf("%s\n\n", mat[0]);
    // show_stack(top1);

    // printf("%s\n\n", mat[1]);
    // show_stack(top2);

    // printf("%s\n\n", mat[2]);
    // show_stack(top3);

    queue *q = create_queue();


    opportunity(top1, top2, top3, q, mat);


    FILE *outfile = fopen(argv[2], "wt");

    show_queue(q, outfile);
    free_stack(&top1);
    free_stack(&top2);
    free_stack(&top3);
    free_mat(mat);
    free_queue(q);
    fclose(infile);
}


void task3(const char *argv[])
{
    FILE *infile = fopen(argv[1], "rt");
    if(infile == NULL)
    {
        puts("Nu se deschide");
        exit(1);
    }

    StockList *head = NULL;
    int n = nr_zile(infile);
    double **mat = create_matrice(n);
    
    citire(&head, mat, n, infile);
    fclose(infile);

    TreeNode *root = create(mat, head, 1, n);

}

int main(int argc, char *argv[])
{
    int task_nr = check_num(argv[1]);
    
    if(task_nr >=1 && task_nr <=5)
        task1(argv);

    if(task_nr >=6 && task_nr <=10)
        task2(argv);
    
    if(task_nr >= 11 && task_nr <= 15)
        task3(argv);
    return 0;
}