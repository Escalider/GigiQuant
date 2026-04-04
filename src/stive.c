#include "stive.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


int isEmpty(const City *top)
{
    return (top == NULL);
}


void push(City **top, double val)
{
    City *newNode = (City *)malloc(sizeof(City));
    newNode->val = val;
    newNode->next = *top;
    *top = newNode;
}


double pop(City **top)
{
    if(isEmpty(*top)) return INT_MIN;
    City *temp = (*top);
    double aux = temp->val;
    *top = (*top)->next;
    free(temp);
    return aux;
}


char **create_mat()
{
    char **mat = (char **)calloc(3, sizeof(char *));
    for(int i = 0; i < 3; i++)
    {
        mat[i] = (char *)calloc(20, sizeof(char));
    }

    return mat;
}


void free_mat(char **mat)
{
    if (mat == NULL) return ; 

    for (int i = 0; i < 3; i++) {
        free(mat[i]); 
    }
    free(mat);
}


void show_stack(City *top)
{
    City *p = top;
    while(p != NULL)
    {
        printf("%.2f\n", p->val);
        p = p->next;
    }
}


void read_file(City **top, FILE *infile)
{
    double val;
    while(fscanf(infile, "%lf", &val) == 1)
    {
        push(top, val);
    }
    int c;
    while ((c = fgetc(infile)) != EOF && (c == ' ' || c == '\n' || c == '\r' || c == '\t'));
    if (c != EOF) {
        ungetc(c, infile);
    }
}


void free_stack(City **top) {
    while (!isEmpty(*top)) {
        pop(top); 
    }
}


void create(City **top1, City **top2, City **top3, FILE *infile, char ***mat)
{    
    *mat = create_mat();
    char *s = calloc(20, sizeof(char));
    fgets(s, 20, infile);
    s[strcspn(s, "\n")] = 0;
    strcpy((*mat)[0], s);
    read_file(top1, infile);

    fgets(s, 20, infile);
    s[strcspn(s, "\n")] = 0;
    strcpy((*mat)[1], s);
    read_file(top2, infile);

    fgets(s, 20, infile);
    s[strcspn(s, "\n")] = 0;
    strcpy((*mat)[2], s);
    read_file(top3, infile);
    free(s);
}