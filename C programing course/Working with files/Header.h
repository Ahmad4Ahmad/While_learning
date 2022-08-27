#define _CRT_SECURE_NO_WARNINGS
#ifndef resturant_list
#define resturant_list

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct meal
{
	char *name;
	float price;
	int quantity;
	struct meal* next;
}meal;

typedef struct Resturant
{
	meal* head, * tail;
	struct Resturant* arr;
}Resturant;

void CreateProducts(FILE* out,Resturant *r);
void AddItems(FILE *out,Resturant* r,char *p,int q);
void OrderItem(FILE* out,Resturant* r,int t,char *p,int q);
void RemoveItem(FILE* out, Resturant* r,int t, char *p, int q);
void RemoveTable(FILE* out,Resturant* r,int t);
void DeleteList(Resturant* r);

#endif
