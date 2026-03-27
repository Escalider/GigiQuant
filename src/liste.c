#include <stdlib.h>
#include <stdio.h>
#include "liste.h"


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


void clear_list(Node **head)
{
    
    while((*head)!=NULL)
    {
        Node *temp = *head;
        (*head) = (*head)->next;
        free(temp);
    }
}