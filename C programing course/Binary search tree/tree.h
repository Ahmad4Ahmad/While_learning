#ifndef ex1tree
#define ex1tree
#include <stdbool.h>

typedef struct treeNode* Ptree;
void insert (float, Ptree*, int*);
void printPreorder(Ptree);
int height(Ptree);
void minKey(Ptree);
void searchKey(Ptree, float, bool*);
void printKmax(Ptree, int, int, int*);
void emptyTree(Ptree*);

#endif
