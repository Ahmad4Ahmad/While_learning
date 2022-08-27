#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct Clock
{
	int hour, minute;
}clock_t;

int main()
{
	int n;
	clock_t clock;
	printf("Enter time and minutes to add:");
	scanf("%d%d%d", &clock.hour, &clock.minute, &n);
	if (clock.hour < 0 || clock.hour>24 || clock.minute<0 || clock.minute>60 || n<0) /*check if the user insert a relevant time*/
	{
		printf("Irrelevant time!");
		exit(0);
	}
	if (clock.hour < 10 && clock.minute < 10)
	{
		printf("The time is: 0%d:0%d\n", clock.hour, clock.minute);
	}
	else
	{
		if (clock.hour > 10 && clock.minute>10)
		{
			printf("The time is: %d:%d\n", clock.hour, clock.minute);
		}
		else
		{
			if (clock.hour < 10)
			{
				printf("The time is: 0%d:%d\n", clock.hour, clock.minute);
			}
			if (clock.minute < 10)
			{
				printf("The time is: %d:0%d\n", clock.hour, clock.minute);
			}
		}
	}
	clock.minute += n;  
	while (clock.minute >= 60) /*calculating the time after adding minutes*/
	{
		clock.minute -= 60;
		clock.hour++;
		while (clock.hour >= 24)
			clock.hour -= 24;
	}
	if (clock.hour < 10 && clock.minute < 10)
	{
		printf("The new time is: 0%d:0%d", clock.hour, clock.minute);
	}
	else
	{
		if (clock.hour > 10 && clock.minute > 10)
		{
			printf("The new time is: %d:%d", clock.hour, clock.minute);
		}
		else
		{
			if (clock.hour < 10)
			{
				printf("The new time is: 0%d:%d", clock.hour, clock.minute);
			}
			if (clock.minute < 10)
			{
				printf("The new time is: %d:0%d", clock.hour, clock.minute);
			}
		}
	}
	return 0;
}
