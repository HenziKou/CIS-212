#include <stdio.h>
#include <stdlib.h>

/* Hank's lecture method of strlen to count number of digits in a string:

int my_strlen(char *s) {
    int count = 0;
    while (*s != '\0') {
	s++;
	count++;
    }
	
	return count;
}
*/

/* Maximum number of elements that can be stored */
#define MAX_STACK_SIZE 100

typedef struct
{
    int nums[MAX_STACK_SIZE];
    int top;
} Stack;

void Initialize(Stack *s)
{
    s->top = -1;
}

void Push(Stack *s, int x)
{
    /* Check if stack is full */
    if (s->top == (MAX_STACK_SIZE - 1))
	fprintf(stderr, "Error: stack is full\n");

    s->nums[++s->top] = x;
}

int Pop(Stack *s)
{
    /* Check if stack is empty */
    if (s->top == -1)
	fprintf(stderr, "Error: stack is empyty\n");

    return s->nums[s->top--];
}

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
    /* Cannot have more than MAX_STACK_SIZE defined amount */
    if (argc > MAX_STACK_SIZE)
    {
	printf("Usage: %s <integer> <+ or -> <integer>\n", argv[0]);
	exit(EXIT_FAILURE);
    }
	
    /* Initialize variables */
    Stack s;
    Initialize(&s);
    int i = 1;
    int x, y;

    while (i < argc)
    {
	int arg = *argv[i];

	if (arg == '+') {
	    /* Perform the '+' operation */
	    x = Pop(&s);
	    y = Pop(&s);
	    Push(&s, (x + y));
	}

	else if (arg == '-') {
	    /* Perform the '-' operation */
	    x = Pop(&s);
	    y = Pop(&s);
	    Push(&s, (y - x));
	}

	else if (arg == 'x') {
	    /* Perform the '*' operation */
	    x = Pop(&s);
	    y = Pop(&s);
	    Push(&s, (x * y));
	}

	else {
	    /* Pass string into 'str2int' helper function */
	    int n = str2int(argv[i]);
	    Push(&s, n);
	}

	i++;
    }

    printf("The total is %d\n", Pop(&s));
    return 0;
}
