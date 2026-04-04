#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Element
{
    double val;
    struct Element *next;
};
typedef struct Element City;



int isEmpty(const City *top);
void push(City **top, double val);
double pop(City **top);
char **create_mat();
void show_stack(City *top);
void read_file(City **top, FILE *infile);
void create(City **top1, City **top2, City **top3, FILE *infile, char ***mat);
void free_stack(City **top);
void free_mat(char **mat);