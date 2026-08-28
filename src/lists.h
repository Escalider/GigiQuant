#include <stdio.h>
struct Elem
{
    double val;
    double rand;
    struct Elem* next;
};


typedef struct Elem Node;

Node *create_list(double *rand_avg, int *n, FILE *infile);
Node *create_node();
void show_list(Node *head);
void clear_list(Node **head);
double volatility(Node *head, double rand_avg, int n);
int check_num(const char num[]);