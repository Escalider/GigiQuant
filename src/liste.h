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