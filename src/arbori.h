#include <stdio.h>
#include <stdlib.h>
#define MAX_SYM 5


typedef struct StockList {
    char symbol[MAX_SYM];
    int index;  
    struct StockList *next;
} StockList;


typedef struct TreeNode {
StockList *stocks;
struct TreeNode *left;
struct TreeNode *right; 
} TreeNode;

void addAtBeginning(StockList** head, char sym[MAX_SYM], int index);
void addAtEnd(StockList** head, char sym[MAX_SYM], int index);
int nr_zile(FILE *infile);
double **create_matrice(int n);
void citire(StockList **head, double **mat, int n, FILE *infile);
TreeNode* createNodeStocks(StockList *stocks);
void clear_lista(StockList **head);
void clear_tree(TreeNode *root);
TreeNode *create(double **mat, StockList *head, int i, int nr_zile);
void gasire_drum(TreeNode *root, StockList *head, char *s, int i, int *gasit);
void opuse(TreeNode *root, StockList *head, int nr_zile, FILE *outfile);