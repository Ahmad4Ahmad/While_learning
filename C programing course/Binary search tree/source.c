#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct treeNode
{
	float key;
	struct treeNode *right;
	struct treeNode *left;
}treeNode;

void insert(float key, Ptree* root,int* s)
{
	if(*root==NULL)
	{
		treeNode* newNode=(treeNode*)malloc(sizeof(treeNode));
		if(newNode==NULL)
		{
			printf("Memory allocation failed");
			emptyTree(root);
			exit(1);
		}
		else
		{
			newNode->right=NULL;
			newNode->left=NULL;
			newNode->key=key;
			*s+=1;
			*root=newNode;
		}
	}
	else
	{
		if((*root)->key>key)
			insert(key, &(*root)->left, s);
		else
			insert(key, &(*root)->right, s);
	}
}

void printPreorder(Ptree t)
{
	if(t==NULL)
		return;
    printf("%.2f ", t->key);
    printPreorder(t->left);
    printPreorder(t->right);
}

int height(Ptree t)
{
	int left;
	int right;
	if(t==NULL)
		return -1;
	else
	{
		left=height(t->left);
		right=height(t->right);
		if(right>left)
			return 1+right;
		else
			return 1+left;
	}
}

void minKey(Ptree t)
{
	while(t->left!=NULL)
	{
		t=t->left;
	}
	printf("%.2f", t->key);
}

void searchKey(Ptree t, float k, bool* flag)
{
	if(t==NULL)
		return;
	searchKey(t->left, k, flag);
	if (t->key==k)
	{
		*flag+=1;
		return;
	}
	searchKey(t->right, k, flag);
}

void printKmax(Ptree t, int x, int size, int* count)
{
	if(x>size)
	{
		printf("Out of bounds");
		return;
	}
	else
	{
		if(t==NULL || *count>x)
			return;
		printKmax(t->right, x, size, count);
		*count+=1;
		if (x==(*count))
		{
			printf("%.2f ", t->key);
			return;
		}
		printKmax(t->left, x, size, count);
	}
}

void emptyTree(Ptree* t)
{
	if(*t==NULL)
		return;
	else
	{
		emptyTree(&(*t)->left);
		emptyTree(&(*t)->right);
		free(*t);
		(*t)=NULL;
	}
}