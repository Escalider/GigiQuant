#include "stacks.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>


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


// void show_stack(City *top)
// {
//     City *p = top;
//     while(p != NULL)
//     {
//         printf("%.2f\n", p->val);
//         p = p->next;
//     }
// }


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


void create_s(City **top1, City **top2, City **top3, FILE *infile, char ***mat)
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

queue *create_queue()
{
    queue *q = (queue *)malloc(sizeof(queue));
    if(q == NULL) return NULL;
    q->front = NULL;
    q->rear = NULL;
    return q;
}

void show_queue(queue *q, FILE *outfile)
{
    NodeQ *temp = q->front;
    while(temp != NULL)
    {
        fprintf(outfile, "%s\n", temp->mes);
        temp = temp->next;
    }
}


void free_queue(queue *q)
{
    
    while(q->front != NULL)
    {
        NodeQ *aux = q->front;
        q->front = q->front->next;
        free(aux);
    }
    free(q);
}


void enque(queue *q, const char *s)
{
    NodeQ *newNodeQ = (NodeQ *)malloc(sizeof(NodeQ));
    strcpy(newNodeQ->mes, s);
    newNodeQ->next = NULL;
    

    if(q->rear == NULL)
    {
        q->rear = newNodeQ;
        q->front = newNodeQ;
    }
    else
    {
        (q->rear)->next = newNodeQ;
        (q->rear) = newNodeQ;
    }
    if(q->front == NULL) q->front = q->rear;
}

void opportunity(City *top1, City *top2, City *top3, queue *q, char **mat)
{
    int k = 1;
    City *p1 = top1;
    City *p2 = top2;
    City *p3 = top3;
    char s[40];
    while(p1 != NULL && p2 != NULL && p3 != NULL)
    {
        
        if(p1->val == p2->val && p1->val != p3->val)
        {
            double value = fabs(p1->val - p3->val);
            snprintf(s, 40, "ziua %d - %.2f - %s", k, value, mat[2]);
            enque(q, s);
        }

        if(p1->val == p3->val && p1->val != p2->val)
        {
            double value = fabs(p1->val - p2->val);
            snprintf(s, 40, "ziua %d - %.2f - %s", k, value, mat[1]);
            enque(q, s);
        }

        if(p3->val == p2->val && p1->val != p3->val)
        {
            double value = fabs(p1->val - p3->val);
            snprintf(s, 40, "ziua %d - %.2f - %s", k, value, mat[0]);
            enque(q, s);
        }
        k++;
        p1 = p1->next; 
        p2 = p2->next;
        p3 = p3->next;
        
    }
    
}