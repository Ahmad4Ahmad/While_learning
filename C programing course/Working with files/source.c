#include "Header.h"

void CreateProducts(FILE* out,Resturant* r) /*creat a products list in the kitchen*/
{
	FILE* in = fopen("Manot.txt", "r");
	if (in == NULL)
	{
		printf("File doesn't exist!");
		exit(1);
	}
	char temp[50];
	int q;
	float p;
	while (fscanf(in, "%s%d%f", temp, &q, &p) != EOF)
	{
		meal* check = r->head;
		while (check)
		{
			if (strcmp(check->name, temp) == 0)
			{
				fprintf(out, "The (%s) is already available in the kitchen!.\n", temp);
				break;
			}
			check = check->next;
		}
		if (p < 0)
		{
			fprintf(out, "Wrong price number, it must be positive!.\n");
			break;
		}
		if (q < 0)
		{
			fprintf(out, "Wrong quantity number, it must be positive!.\n");
			break;
		}
		meal* node = (meal*)malloc(sizeof(meal));
		if (node == NULL)
		{
			DeleteList(r);
			printf("Memory allocation failed!");
			exit(1);
		}
		node->price = p;
		node->quantity = q;
		node->name = (char*)malloc((strlen(temp) + 1) * sizeof(char));
		if (node->name == NULL)
		{
			DeleteList(r);
			printf("Memory allocation failed!");
			exit(1);
		}
		strcpy(node->name, temp);
		node->next = r->head;
		r->head = node;
	}
	fclose(in);
	fprintf(out, "The kitchen was created.\n");
}

void AddItems(FILE* out,Resturant* r,char *p, int q)  /*add items to existing product*/
{
	if (q < 0)
	{
		fprintf(out, "Wrong quantity number, it must be positive!.\n");
		return;
	}
	meal* temp=r->head;
	while (temp)
	{
		if (strcmp(temp->name, p) == 0)
		{
			temp->quantity += q;
			fprintf(out, "%d %s were added to the kitchen.\n", q, p);
			return;
		}
		temp = temp->next;
	}
	fprintf(out, "Wrong product name!\n");
}

void OrderItem(FILE* out,Resturant* r,int t, char *p, int q)  /*order products for given table number*/
{
	if (t < 0)
	{
		fprintf(out, "Wrong table number, it must be positive!.\n");
		return;
	}
	if (q < 0)
	{
		fprintf(out, "Wrong quantity number, it must be positive!.\n");
		return;
	}
	meal* temp = r->head;
	while (temp)
	{
		if (strcmp(temp->name, p) == 0)
		{
			if (temp->quantity > q)
			{
				temp->quantity--;
				float Price = temp->price;
				temp = r->arr[t].head;
				while (temp)
				{
					if (strcmp(temp->name, p) == 0)
					{
						temp->quantity++;
						return;
					}
					temp = temp->next;
				}
				meal* node = (meal*)malloc(sizeof(meal));
				if (node == NULL)
				{
					DeleteList(r);
					printf("Memory allocation failed!");
					exit(1);
				}
				node->name = (char*)malloc((strlen(p) + 1) * sizeof(char));
				strcpy(node->name, p);
				node->price = Price;
				node->quantity = q;
				node->next = NULL;
				if (r->arr[t].head == NULL)
					r->arr[t].head = node;
				else
					r->arr[t].tail->next = node;
				r->arr[t].tail = node;
				return;
			}
			else
			{
				fprintf(out, "We don't have %s, sorry!\n", p);
				return;
			}
		}
		temp = temp->next;
	}
	fprintf(out, "We don't have %s, sorry!\n", p);
}

void RemoveItem(FILE* out, Resturant* r,int t, char *p, int q)  /*cancel an product order for given table number*/
{
	if (t < 0)
	{
		fprintf(out, "Wrong table number, it must be positive!.\n");
		return;
	}
	if (q < 0)
	{
		fprintf(out, "Wrong quantity number, it must be positive!.\n");
		return;
	}
	meal* temp = r->arr[t].head;
	while (temp)
	{
		if (strcmp(temp->name, p) == 0)
		{
			if (q > temp->quantity)
			{
				fprintf(out, "You are asking to remove more than you ordered!\n");
				return;
			}
			else
			{
				temp->quantity--;
				fprintf(out, "%d %s was returned to the kitchen from table %d.\n",q,p,t);
				return;
			}
		}
		temp = temp->next;
	}
	fprintf(out, "This product is not available on this table\n");
}

void RemoveTable(FILE* out,Resturant* r,int t)  /*close table and calculate the final price including tips*/
{
	if (t < 0)
	{
		fprintf(out, "Wrong table number, it must be positive!.\n");
		return;
	}
	meal* temp = r->arr[t].head;
	if (temp == NULL)
	{
		fprintf(out, "The table number %d is not ordered yet.\n", t);
		return;
	}
	else
	{
		while (temp)
		{
			fprintf(out, "%d %s. %.2f nis + %.2f for tips, please!\n", temp->quantity, temp->name, temp->price * temp->quantity, temp->price * temp->quantity * 10 / 100);
			temp = temp->next;
		}
	}
	DeleteList(&r->arr[t]);
}

void DeleteList(Resturant* r)  /*free list memory*/
{
	meal* temp = r->head;
	while (temp)
	{
		r->head = temp->next;
		free(temp->name);
		free(temp);
		temp = r->head;
	}
}
