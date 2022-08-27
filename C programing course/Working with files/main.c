#include "Header.h"

int main()
{
	Resturant r;
	FILE* in = fopen("Instructions.txt", "r");

	if (in == NULL)
	{
		printf("File doesn't exist!");
		exit(1);
	}
    
	int n = 0;
	fscanf(in, "%d", &n);
	r.arr = (Resturant*)malloc(n * sizeof(Resturant));
	if (r.arr == NULL)
	{
		DeleteList(&r);
		printf("Memory allocation failed!");
		exit(1);
	}
	int i;
	for (i = 0; i < n; i++)
	{
		r.arr[i].head = NULL;
		r.arr[i].tail = NULL;
	}
	r.head = NULL;
	r.tail = NULL;
	FILE* out = fopen("output.txt", "a");
	if (out == NULL)
	{
		printf("File doesn't exist!");
		exit(1);
	}
	int input = 0;
	char product_name[50];
	int Quantity;
	int table_number;
	while (fscanf(in, "%d", &input) != EOF)
	{
		switch (input)
		{
		case 1:
			CreateProducts(out, &r);
			break;
		case 2:
			fscanf(in, "%s%d", product_name,&Quantity);
			AddItems(out, &r, product_name, Quantity);
			break;
		case 3:
			fscanf(in, "%d%s%d", &table_number, product_name, &Quantity);
			if (table_number > n)
			{
				fprintf(out, "This table number is not available in the resturant!.\n");
				break;
			}
			OrderItem(out, &r, table_number, product_name, Quantity);
			break;
		case 4:
			if (table_number > n)
			{
				fprintf(out, "This table number is not available in the resturant!.\n");
				break;
			}
			fscanf(in, "%d%s%d", &table_number, product_name, &Quantity);
			RemoveItem(out, &r, table_number, product_name, Quantity);
			break;
		case 5:
			if (table_number > n)
			{
				fprintf(out, "This table number is not available in the resturant!.\n");
				break;
			}
			fscanf(in, "%d", &table_number);
			RemoveTable(out, &r, table_number);
			break;
		}
	}
	fclose(in);
	fclose(out);
	DeleteList(&r);
	for (i = 0; i < n; i++)
	{
		DeleteList(&r.arr[i]);
	}
	free(r.arr);
	return 0;
}
