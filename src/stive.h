#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Element
{
    double val;
    struct Element *next;
};
typedef struct Element City;


struct ElemQ
{
    char mes[40];
    struct ElemQ *next;
};

typedef struct ElemQ NodeQ;

struct Q
{
    NodeQ *front, *rear;
};

typedef struct Q queue;


int isEmpty(const City *top);
void push(City **top, double val);
double pop(City **top);
char **create_mat();
void show_stack(City *top);
void read_file(City **top, FILE *infile);
void create(City **top1, City **top2, City **top3, FILE *infile, char ***mat);
void free_stack(City **top);
void free_mat(char **mat);
queue *create_queue();
void show_queue(queue *q, FILE *outfile);
void free_queue(queue *q);
void enque(queue *q, const char *s);
void opportunity(City *top1, City *top2, City *top3, queue *q, char **mat);
