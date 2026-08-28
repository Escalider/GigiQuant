#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "lists.h"
#include <string.h>
#include <math.h>


Node *create_list(double *rand_avg, int *n, FILE *infile)
{

    fscanf(infile, "%d", n);

    Node *head = NULL;
    Node *last = NULL;
    
    *rand_avg = 0;
    double v;
    double r = 0;
    for(int i = 0; i < *n; i++)
    {
        Node *newNode = (Node *)malloc(sizeof(Node));
        
        if(newNode == NULL) return head;

        if(head == NULL)
        {
            fscanf(infile ,"%lf", &newNode->val);
            v = newNode->val;
            newNode->rand = 0;
            head = newNode;
            last = newNode;

        }
        else
        {
            fscanf(infile ,"%lf", &newNode->val);
            r = (newNode->val - v)/v;
            newNode->rand = r;
            v = newNode->val;
            last->next = newNode;
            last = newNode;
        }
        *rand_avg+=r;

        
    }
    *rand_avg/=(*(n)-1);
    return head;
}



// void show_list(Node *head)
// {
//     Node *p = head;
//     while(p != NULL)
//     {
//         printf("%.2f\n", p->val);
//         printf("%.3f\n", p->rand);
//         printf("\n");
//         p = p->next;
//     }
//     printf("\n");
// }

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

void clear_list(Node **head)
{
    while((*head)!=NULL)
    {
        Node *temp = *head;
        (*head) = (*head)->next;
        free(temp);
    }
}

int check_num(const char num[])
{
    int n = strlen(num), number = 0;
    for(int i = 0; i < n; i++)
    {
        if(isdigit(num[i]))
        {
            number = number * 10 +(num[i] - '0');
        }
    }
    return number;
}