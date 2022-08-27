#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct fraction
{
	int a;
	int b;
}fraction;

int gcd(int s, int t);

int main()
{
	int i = 1;
	fraction* f = (fraction*)malloc(sizeof(fraction));
	if (!f)
	{
		printf("Memory allocation failed!");
		exit(0);
	}
	printf("Enter fractions by pairs of integers (0 0 to finish):\n");
	printf("%d (mone mehane):", (i));
	scanf("%d%d", &f[0].a, &f[0].b);
	if (f[0].a == 0 && f[0].b == 0)
	{
		printf("Error!");
		exit(0);
	}
	if (f[0].b == 0)
	{
		printf("Division Error!, please enter a new pair of integers:\n");
		printf("%d (mone mehane):", (i));
		scanf("%d%d", &f[0].a, &f[0].b);
	}
	while (1)
	{
		printf("%d (mone mehane):", (i + 1));
		f = (fraction*)realloc(f, (sizeof(f) + 1) * sizeof(fraction));
		if (!f)
		{
			printf("Memory allocation failed!");
			exit(0);
		}
		scanf("%d%d", &f[i].a, &f[i].b);
		if (f[i].a == 0 && f[i].b == 0)
			break;
		if (f[i].b == 0)
		{
			printf("Division Error!, please enter a new pair of integers:\n");
			printf("%d (mone mehane):", (i + 1));
			scanf("%d%d", &f[i].a, &f[i].b);
		}
		i++;
	}
	int size = i;
	int x, y, temp, old_y;
	if (f[1].a == 0 && f[1].b == 0) /*in case we got just one fraction*/
	{
		if (f[0].a == 0 && f[0].b != 0)
		{
			printf("%d/%d = 0", f[0].a, f[0].b);
		}
		else
		{
			temp = gcd(f[0].a, f[0].b);
			if (f[0].a < f[0].b)
			{
				printf("%d/%d = %d/%d", f[0].a, f[0].b, (f[0].a / temp), (f[0].b / temp));
			}
			else
			{
				if (f[0].a % f[0].b == 0)
				{
					printf("%d/%d = %d", f[0].a, f[0].b, (f[0].a / f[0].b));
				}
				else
				{
					printf("%d/%d = %d and %d/%d", f[0].a, f[0].b, (f[0].a / f[0].b), (f[0].a / temp) % (f[0].b / temp), (f[0].b / temp));
				}
			}
		}
	}
	else /*more than one fraction*/
	{
		temp = gcd(f[0].b, f[1].b);
		y = (f[0].b * f[1].b) / temp;
		x = (y / f[0].b) * f[0].a + (y / f[1].b) * f[1].a;
		for (i = 2; i < size; i++)
		{
			temp = gcd(y, f[i].b);
			old_y = y;
			y = (y * f[i].b) / temp;
			x = (y / old_y) * x + (y / f[i].b) * f[i].a;
		}
		temp = gcd(x, y);
		for (i = 0; i < size - 1; i++)
		{
			printf("%d/%d + ", f[i].a, f[i].b);
		}
		if (temp == 0)
		{
			printf("%d/%d = 0", f[size - 1].a, f[size - 1].b);
		}
		else
		{
			x = x / temp;
			y = y / temp;
			if (x % y == 0)
			{
				printf("%d/%d = %d", f[size - 1].a, f[size - 1].b, (x / y));
			}
			else
			{
				printf("%d/%d = %d/%d = %d and %d/%d", f[size - 1].a, f[size - 1].b, x, y, (x / y), (x % y), y);
			}
		}
	}
	free(f);
	return 0;
}

int gcd(int s, int t) /*calculate the gcd of two integers*/
{
	int i, gcd = 0;
	for (i = 1; i <= s && i <= t; i++)
	{
		if (s % i == 0 && t % i == 0)
			gcd = i;
	}
	return gcd;
}
