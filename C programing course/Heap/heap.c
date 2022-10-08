#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 20

#include <stdio.h>
#include <stdlib.h>

typedef struct heapNode
{
	int data;
	int twinIndex;
}heapNode;

void init(heapNode*, heapNode*, int*, int);
void buildMaxHeap(heapNode*, heapNode*, int);
void buildMinHeap(heapNode*, heapNode*, int);
void heapifyDownMax(heapNode*, heapNode*, int, int);
void heapifyDownMin(heapNode*, heapNode*, int, int);
void insert(heapNode*, heapNode*, int, int*);
void heapifyUpMax(heapNode*, heapNode*, int);
void heapifyUpMin(heapNode*, heapNode*, int);
int findMin(heapNode*);
int findMax(heapNode*);
void delMin(heapNode*, heapNode*, int*);
void delMax(heapNode*, heapNode*, int*);

int main()
{
	int size=0;
	int arr[MAX_SIZE];
	char c = ' ';
	heapNode maxHeap[MAX_SIZE];
	heapNode minHeap[MAX_SIZE];
	int n;
	int newValue;

	printf("NOTE: the maximum capacity is 20.\n");
	printf("Enter a sequence of integers to start.\n");
	while (c!='\n')
	{
		if (size == MAX_SIZE)
		{
			printf("Full heap.\n");
			break;
		}
		// in assumption that the integers separated by one char
		scanf("%d%c", &arr[size], &c);
		size++;
	}
	init(maxHeap, minHeap, arr, size);
	printf("choose one of these options to proceed.\n\n");
	printf("1- to insert a new value.\n");
	printf("2- to get the minimum.\n");
	printf("3- to get the maximum.\n");
	printf("4- to delete the minimum.\n");
	printf("5- to delete the maximum.\n");
	printf("6- to quit the program.\n");
	
	do
	{
		printf("your option: ");
		scanf("%d", &n);
		switch (n)
		{
			case 1:
				if (size == MAX_SIZE)
				{
					printf("full heap.\n");
					break;
				}
				printf("enter a new integer to insert: ");
				scanf("%d", &newValue);
				insert(maxHeap, minHeap, newValue, &size);
				printf("the new value successfully inserted.\n");
				break;

			case 2:
				if (size == 0)
				{
					printf("empty heap.\n");
					break;
				}
				printf("the minimum value: %d\n", findMin(minHeap));
				break;

			case 3:
				if (size == 0)
				{
					printf("empty heap.\n");
					break;
				}
				printf("the maximum value: %d\n", findMax(maxHeap));
				break;

			case 4:
				if (size == 0)
				{
					printf("empty heap.\n");
					break;
				}
				delMin(minHeap, maxHeap, &size);
				printf("done.\n");
				break;

			case 5:
				if (size == 0)
				{
					printf("empty heap.\n");
					break;
				}
				delMax(maxHeap, minHeap, &size);
				printf("done.\n");
				break;

			case 6:
				exit(0);

			default:
				printf("invalid option.\n");
				break;
		}

	} while (1);
	return 0;
}

void delMax(heapNode* max, heapNode* min, int* size)
{
	int n = (*size);
	int i = max[0].twinIndex;

	max[0].data = max[n - 1].data;
	max[0].twinIndex = max[n - 1].twinIndex;
	heapifyDownMax(max, min, n, 0);
	min[i].data = min[n - 1].data;
	min[i].twinIndex = min[n - 1].twinIndex;
	(*size)--;
	heapifyDownMin(min, max, n, i);
	// heapifyUpMin(min, max, i);
}

void delMin(heapNode* min, heapNode* max, int* size)
{
	int n = (*size);
	int i = min[0].twinIndex;

	min[0].data = min[n - 1].data;
	min[0].twinIndex = min[n - 1].twinIndex;
	heapifyDownMin(min, max, n, 0);
	max[i].data = max[n - 1].data;
	max[i].twinIndex = max[n - 1].twinIndex;
	(*size)--;
	heapifyDownMax(max, min, n, i);
	// heapifyUpMax(max, min, i);
}

int findMax(heapNode* max)
{
	return max[0].data;
}

int findMin(heapNode* min)
{
	return min[0].data;
}

void init(heapNode* max, heapNode* min, int* array, int size)
{
	for (int i = 0; i < size; i++)
	{
		max[i].data = array[i];
		max[i].twinIndex = i;
		min[i].data = array[i];
		min[i].twinIndex = i;
	}
	buildMaxHeap(max, min, size);
	buildMinHeap(min, max, size);
}

void buildMaxHeap(heapNode* max, heapNode* min, int size)
{
	for (int i = (size / 2) - 1; i >= 0; i--)
	{
		heapifyDownMax(max, min, size, i);
	}
}

void heapifyDownMax(heapNode* max, heapNode* min, int size, int i)
{
	// implement heapify down method on max heap
	int left = 2 * i + 1; //left child index
	int right = 2 * i + 2;  //right child index
	int largest = i;
	
	if (left < size && max[left].data > max[i].data)
	{
		largest = left;
	}
	if (right < size && max[right].data > max[largest].data)
	{
		largest = right;
	}
	if (largest != i)
	{
		min[max[i].twinIndex].twinIndex = largest;
		min[max[largest].twinIndex].twinIndex = i;
		int temp=max[i].twinIndex;
        max[i].twinIndex=max[largest].twinIndex;
        max[largest].twinIndex=temp;
		temp = max[i].data;
		max[i].data = max[largest].data;
		max[largest].data = temp;
		heapifyDownMax(max, min, size, largest);
	}
}

void buildMinHeap(heapNode* min, heapNode* max, int size)
{
	for (int i = (size / 2) - 1; i >= 0; i--)
	{
		heapifyDownMin(min, max, size, i);
	}
}

void heapifyDownMin(heapNode* min, heapNode* max, int size, int i) 
{
	// implement heapify down method on min heap
	int left = 2 * i + 1; // left child index
	int right = 2 * i + 2;  // right child index
	int smallest = i;

	if (left < size && min[left].data < min[i].data)
	{
		smallest = left;
	}
	if (right < size && min[right].data < min[smallest].data)
	{
		smallest = right;
	}
	if (smallest != i)
	{
		max[min[i].twinIndex].twinIndex = smallest;
		max[min[smallest].twinIndex].twinIndex = i;
        int temp=min[i].twinIndex;
        min[i].twinIndex=min[smallest].twinIndex;
        min[smallest].twinIndex=temp;
		temp = min[i].data;
		min[i].data = min[smallest].data;
		min[smallest].data = temp;
		heapifyDownMin(min, max, size, smallest);
	}
}

void insert(heapNode* max, heapNode* min, int data, int* size)
{
	int i = (*size);

	max[(*size)].data = data;
	max[(*size)].twinIndex = (*size);
	heapifyUpMax(max, min, i);
	min[(*size)].data = data;
	heapifyUpMin(min, max, i);
	(*size)++;
}

void heapifyUpMax(heapNode* max, heapNode* min, int index)
{
	// implement heapify up method on max heap
	int parent = (index - 1) / 2;
	
	if (max[parent].data < max[index].data)
	{
		min[max[parent].twinIndex].twinIndex = index;
		min[max[index].twinIndex].twinIndex = parent;
		int temp = max[parent].data;
		max[parent].data = max[index].data;
		max[index].data = temp;
		heapifyUpMax(max, min, parent);
	}
}

void heapifyUpMin(heapNode* min, heapNode* max, int index)
{
	// implement heapify up method on min heap
	int parent = (index - 1) / 2;

	if (min[parent].data > min[index].data)
	{
		max[min[parent].twinIndex].twinIndex = index;
		max[min[index].twinIndex].twinIndex = parent;
		int temp = min[parent].data;
		min[parent].data = min[index].data;
		min[index].data = temp;
		heapifyUpMin(min, max, parent);
	}
}