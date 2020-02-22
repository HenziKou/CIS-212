#include <stdio.h>
#include <stdlib.h>

/* Note:
 * - you may not use atoi
 * - you may not use *any* built-in-functions -- strlen, strcpy, etc.
 * - you may assume all integers have <10 digits
 */

/*
Hank's lecture method of strlen to count number of digits in a string:

int my_strlen(char *s)
{
	int count = 0;
	while (*s != '\0')
	{
		s++;
		count++;
	}
	
	return count;
}
*/

int str2int(char *number)
{
	int count = 0;
	int num = 0;
	int negFlag = 1;

	/* If number is negative start at the 1 index to covert string into an integer */
	if (number[0] == '-')
	{
		for (int i = 1; number[i] != '\0'; i++)
		{
			/* Characters must be 0-9 or a '-' flag */
			if (((number[i] < 48) || (number[i] > 57)) && (number[i] != 10))
			{
				printf("ERROR: number has character that is outside 0-9\n");
				exit(EXIT_FAILURE);
			}
			
			count++;
			num = num * 10 + (number[i] - '0');
			negFlag = -1;
		}
		
		/* String length can't be greater than 10 digits */
		if (count > 9)
		{
			printf("ERROR: number has 10 or more digits\n");
			exit(EXIT_FAILURE);
		}
	}
	
	/* Otherwise start index at 0 to convert string into an integer */
	else
	{
		for (int j = 0; number[j] != '\0'; j++)
		{
			if (((number[j] < 48) || (number[j] > 57)) && (number[j] != 10))
			{
				printf("ERROR: number has character that is outside 0-9\n");
				exit(EXIT_FAILURE);
			}
			
			count++;
			num = num * 10 + (number[j] - '0');
			negFlag = 1;
		}
	
		if (count > 10)
		{
			printf("ERROR: number has 10 or more digits\n");
			exit(EXIT_FAILURE);
		}
	}
	
	num *= negFlag;
	return num;
}
		
int main(int argc, char *argv[])
{
	/* Must have at least four arguments when running program */
	if (argc != 4)
	{
		printf("Usage: %s <integer> <+ or -> <integer>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	/* Initialize variables */
	char *number1 = argv[1];
	char *operation = argv[2];
	char *number2 = argv[3];
	char op = *operation;
	int sum = 0;
	int opCount = 0;

	/* Call str2int function to convert string into int values */
	int num1 = str2int(number1);
	int num2 = str2int(number2);

	/* Check if there are more than one operation being passed */
	while (*operation != '\0')
	{
		operation++;
		opCount++;
	}

	if (opCount != 1)
	{
		printf("ERROR: operation may only be + or -\n");
		exit(EXIT_FAILURE);
	}

	/* Operators must only be '+' or '-' */
	if ((op == 43) || (op == 45))
	{
		if (op == '+')
			sum = num1 + num2;
		else
			sum = num1 - num2;
	}
	
	/* Accept only '+' and '-' operators */
	else
	{
		printf("ERROR: operation may only be + or -\n");
		exit(EXIT_FAILURE);
	}

	/* Print result */
	printf("%d\n", sum);
}
