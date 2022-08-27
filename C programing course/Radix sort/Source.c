#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int getMax(int*, int);
void countSort(int*, int, int);
void radixSort(int*, int);

int main()
{
	int* arr;
	int n;

	printf("Enter the number of elements to be sorted: ");
	scanf("%d", &n);
	arr = (int*)malloc(n * sizeof(int));
	if (arr == NULL)
	{
		printf("Memory allocation failed!");
		exit(1);
	}
	printf("Enter %d elements:\n", n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}
	printf("The elements before sorting:\n");
	for (int i = 0; i < n; i++)
	{
		printf("%5d", arr[i]);
	}
	radixSort(arr, n);
	printf("\nThe elements after sorting:\n");
	for (int i = 0; i < n; i++)
	{
		printf("%5d", arr[i]);
	}
	free(arr);
	return 0;
}

void radixSort(int* arr, int n)
{
	int m = getMax(arr, n);

	for (int exp = 1; m / exp > 0; exp *= 10)
		countSort(arr, n, exp);
}

int getMax(int* arr, int n)
{
	int max = arr[0];

	for (int i = 1; i < n; i++)
		if (arr[i] > max)
			max = arr[i];
	return max;
}

void countSort(int* arr, int n, int exp)
{
	int* output;
	int i;
	int count[10] = { 0 };

	output = (int*)calloc(n * sizeof(int));
	if (output == NULL)
	{
		printf("Memory allocation failed!");
		exit(1);
	}
	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;

	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	int c;

	for (i = n - 1; i >= 0; i--)
	{
		c = count[(arr[i] / exp) % 10];
		*(output + (c - 1)) = *(arr + i);
		count[(arr[i] / exp) % 10]--;
	}
	for (i = 0; i < n; i++)
		arr[i] = output[i];
	free(output);
}