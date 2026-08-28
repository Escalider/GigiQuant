#include "trees.h"
#include <string.h>
#include <stdlib.h>



void addAtBeginning(StockList** head, const char sym[MAX_SYM], int index)
{
    StockList *newNode = (StockList*)malloc(sizeof(StockList));
    strcpy(newNode->symbol, sym);
    newNode->index = index; 
    newNode->next = *head;
    *head = newNode;
}

void addAtEnd(StockList** head, const char sym[MAX_SYM], int index)
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
    
    while((*head)!=NULL)
    {
        StockList *temp = *head;
        (*head) = (*head)->next;
        free(temp);
    }
}

void clear_tree(TreeNode *root)
{
    if (root == NULL) {
        return;
    }
    clear_tree(root->left);
    clear_tree(root->right);
    if (root->stocks != NULL) {
        clear_lista(&(root->stocks));
    }

    free(root);
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
        // printf("Pentru actiunea %s ziua %d este %.2f si ziua %d este %.2f\n",aux->symbol , i, mat[i][j], i-1, mat[i-1][j]);
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

void gasire_drum(TreeNode *root, StockList *head, char *s, int i, int *gasit)
{
    if(root == NULL || *gasit == 1) return;
    if(root->left == NULL && root->right == NULL)
    {   
        StockList *aux = root->stocks;
        while(aux != NULL) {
            if(strcmp(aux->symbol, head->symbol) == 0) {
                s[i] = '\0';
                *gasit = 1; 
                return;
            }
            aux = aux->next;
        }
        return; 
    }

    if(*gasit == 0)
    {
        s[i] = 's';
        gasire_drum(root->left, head, s, i+1, gasit);
    }

    if(*gasit == 0)
    {
        s[i] = 'd';
        gasire_drum(root->right, head, s, i+1, gasit);
    }
}

void opuse(TreeNode *root, StockList *head, int nr_zile, FILE *outfile)
{
    char **matrice = (char **) calloc(100, sizeof(char *));
    for(int i = 0; i < 100; i++)
    {
        matrice[i] = (char *) calloc(32, sizeof(char));
    }
    
    char *s = (char *)calloc((nr_zile) , sizeof(char));
    char *drum = (char *)calloc((nr_zile) , sizeof(char));
    StockList *aux = head;
    int j = 0;
    while(aux != NULL)
    {
        TreeNode *tree1 = root;
        TreeNode *tree2 = root;
        int gasit = 0, gol = 0;
        gasire_drum(root, aux, s, 0, &gasit);
        strcpy(drum, s);
        int n = strlen(drum);
        for(int i = 0; i < n; i++)
        {
            if(drum[i] == 's') 
            {
                tree1 = tree1->left;
                if(tree2->right!=NULL) tree2 = tree2->right;
                else
                {
                    gol = 1;
                    break;
                }                
            }
            else 
            {
                tree1 = tree1->right;
                if(tree2->left != NULL) tree2 = tree2->left;
                else
                {
                    gol = 1;
                    break;
                }
            }
        }

        if(gol == 0)
        {
            StockList *p2 = tree2->stocks;
            while(p2 != NULL)
            {
                sprintf(matrice[j], "%s-%s", tree1->stocks->symbol, p2->symbol);
                j++;
                p2 = p2->next;
            }
                
            StockList *temp = tree1->stocks;
            tree1->stocks = tree1->stocks->next;
            free(temp);
        }
        memset(s, 0, nr_zile);
        memset(drum, 0, nr_zile);
        aux = aux->next;
    }
    
    for(int i = 0; i < j; i++)
    {
        fprintf(outfile, "%s", matrice[i]);
        if(i != j-1) fprintf(outfile, "\n");
    }

    for(int i = 0; i < 100; i++) {
        free(matrice[i]);
    }
    free(matrice);
    
    free(s);
    free(drum);
}