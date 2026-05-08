#include "arbori.h"
#include <string.h>
#include <stdlib.h>



void addAtBeginning(StockList** head, char sym[MAX_SYM], int index)
{
    StockList *newNode = (StockList*)malloc(sizeof(StockList));
    strcpy(newNode->symbol, sym);
    newNode->index = index; 
    newNode->next = *head;
    *head = newNode;
}

void addAtEnd(StockList** head, char sym[MAX_SYM], int index)
{
    if (*head == NULL) {
        addAtBeginning(head, sym, index); 
    } else {
        StockList *aux = *head;
        StockList *newNode = (StockList*)malloc(sizeof(StockList));
        newNode->index = index; 
        strcpy(newNode->symbol, sym);
        newNode->next = NULL;
        
        while (aux->next != NULL) 
            aux = aux->next;
        aux->next = newNode;
    }
}

int nr_zile(FILE *infile)
{
    int nr = 0;
    char linie[100];
    while(fgets(linie, sizeof(linie), infile) != NULL)
    {
        nr++;
    }
    rewind(infile);
    return nr-1;
}

double **create_matrice(int n)
{
    double **mat = (double **) calloc(n, sizeof(double *));
    for(int i = 0; i < n; i++)
    {
        mat[i] = (double *) calloc(10, sizeof(double));
    }
    return mat;
}

void citire(StockList **head, double **mat, int n, FILE *infile)
{

    if(infile == NULL)
    {
        printf("Eroare la deschiderea fisierului!\n");
        exit(1);
    }


    char symbols[100];

    fgets(symbols, sizeof(symbols), infile);

    symbols[strcspn(symbols, "\n")] = '\0';
    char s[256];
    char *p = strtok(symbols, ",");
    
    int index = 0;
    while(p != NULL)
    {
        addAtEnd(head, p, index++);
        p = strtok(NULL, ",");
    }

    for(int i = 0; i < n; i++)
    {
        fgets(s, 256, infile);
        s[strcspn(s, "\n")] = '\0';
        p = strtok(s, ",");

        int j = 0;
        while(p != NULL)
        {
            double val = atof(p);
            mat[i][j++] = val;
            p = strtok(NULL, ",");
        }
        
    }
    fclose(infile);



}

TreeNode* createNodeStocks(StockList *stocks) 
{
    TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->stocks = NULL;
    newNode->left = NULL;
    newNode->right = NULL;

    StockList *aux = stocks;
    while(aux != NULL) {
        addAtEnd(&(newNode->stocks), aux->symbol, aux->index);
        aux = aux->next;
    }

    return newNode;
    
}

void clear_lista(StockList **head)
{
    StockList *temp;
    while((*head)!=NULL)
    {
        temp = *head;
        (*head) = (*head)->next;
        free(temp);
    }
}

TreeNode *create(double **mat, StockList *head, int i, int nr_zile)
{
    if(head == NULL) return NULL;
    TreeNode *node = createNodeStocks(head);

    if(i >= nr_zile) {
        node->left = NULL;
        node->right = NULL;
        return node;
    }

    StockList *scazute = NULL;
    StockList *crescute = NULL;
    StockList *aux = head;
    
    while(aux != NULL)
    {
        int j = aux->index;
        // printf("Pentru actiunea %s ziua %d este %.3f si ziua %d este %.3f\n",aux->symbol , i, mat[i][j], i-1, mat[i-1][j]);
        if(mat[i][j] < mat[i-1][j])
            addAtEnd(&scazute, aux->symbol, j);
        else
            addAtEnd(&crescute, aux->symbol, j);
        aux = aux->next;
    }

    node->left = create(mat, scazute, i+1, nr_zile);
    node->right = create(mat, crescute, i+1, nr_zile);

    if (scazute != NULL) clear_lista(&scazute);
    if (crescute != NULL) clear_lista(&crescute);
    
    return node;

}