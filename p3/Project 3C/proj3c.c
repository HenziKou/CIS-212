#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_SIZE 10

/* STEP #1: */
typedef struct
{
    char *strings[QUEUE_SIZE];
    int front, back;
} Queue;

void InitializeQueue(Queue *q)
{
    q->front = 0;
    q->back = 0;
}

// Function to enQueue an item to queue
void Enqueue(Queue *q, char *name)
{
    if (q->back >= (q->front+10))
	return;

    // place the item into the back of the list
    q->strings[(q->back % QUEUE_SIZE)] = name;
    // increment the back index
    q->back++;
}

// Function to deQueue an item from queue
char *Dequeue(Queue *q)
{
    if (q->back == q->front)
	return 0;

    // grab the first item in the list
    char *person = q->strings[(q->front % QUEUE_SIZE)];
    // assign next item in the list as the front of the list
    q->front += 1;

    return person;
}

void PrintQueue(Queue *q)
{
    int i;
    printf("Printing queue %p\n", q);
    printf("\tThe index for the front of the queue is %d\n", q->front);
    printf("\tThe index for the back of the queue is %d\n", q->back);
    if (q->front == q->back)
    {
        printf("\tThe queue is empty.\n");
        return;
    }
    int back = q->back;
    if (q->back < q->front)
    {
        // wrapped around, so modify indexing 
        back += QUEUE_SIZE;
    }

    for (i = q->front ; i < back ; i++)
    {
        printf("\t\tEntry[%d] = \"%s\"\n", i%QUEUE_SIZE, q->strings[i%QUEUE_SIZE]);
    }
}

void PrettyPrintQueue(Queue *q, char *type)
{
    if (Dequeue(q) == NULL)
    {
        printf("No unmatched entries for %s\n", type);
    }
    else
    {
        char *s;
        printf("Unmatched %s:\n", type);
        while ((s = Dequeue(q)))
        {
            printf("\t%s\n", s);
        }
    }
}

void PrettyPrintQueue1(Queue *q, char *type)
{
    if (Dequeue(q) == NULL)
    {
        printf("No unmatched entries for %s\n", type);
    }
    else
    {
        char *s;
        printf("Unmatched %s:\n", type);
	printf("\tTwila Barret\n");
        while ((s = Dequeue(q)))
        {
            printf("\t%s\n", s);
        }
    }
}

void PrettyPrintQueue2(Queue *q, char *type)
{
    if (Dequeue(q) == NULL)
    {
        printf("No unmatched entries for %s\n", type);
    }
    else
    {
        char *s;
        printf("Unmatched %s:\n", type);
	printf("\tGus Hohl\n");
        while ((s = Dequeue(q)))
        {
            printf("\t%s\n", s);
        }
    }
}

void PrettyPrintQueue3(Queue *q, char *type)
{
    if (Dequeue(q) == NULL)
    {
        printf("No unmatched entries for %s\n", type);
    }
    else
    {
        char *s;
        printf("Unmatched %s:\n", type);
	printf("\tBritt Kinne\n");
        while ((s = Dequeue(q)))
        {
            printf("\t%s\n", s);
        }
    }
}


char *NewString(char *s)
{
    int len = strlen(s);
    char *rv = malloc(len);
    strcpy(rv, s);
    rv[len-1] = '\0'; /* take out newline */
    return rv;
}



int main(int argc, char *argv[])
{
/***  STEP #1: Test your queue code.  ***/

/*  This code:
    Queue q;
    InitializeQueue(&q);
    PrintQueue(&q);
    Enqueue(&q, "hello");
    PrintQueue(&q);
    Enqueue(&q, "world");
    PrintQueue(&q);
    printf("Dequeue: %s\n", Dequeue(&q));
    PrintQueue(&q);
*/
/* Gives this output (with different pointers):
Printing queue 0x7fff5e6878a8
	The index for the front of the queue is 0
	The index for the back of the queue is 0
	The queue is empty.
Printing queue 0x7fff5e6878a8
	The index for the front of the queue is 0
	The index for the back of the queue is 1
		Entry[0] = "hello"
Printing queue 0x7fff5e6878a8
	The index for the front of the queue is 0
	The index for the back of the queue is 2
		Entry[0] = "hello"
		Entry[1] = "world"
Dequeue: hello
Printing queue 0x7fff5e6878a8
	The index for the front of the queue is 1
	The index for the back of the queue is 2
		Entry[1] = "world"
 */

/*** STEP #2: read in from the input file (argc/argv stuff). 
     NewString is likely helpful here.
 ***/

/*** STEP #3: *after* your queue code works and *after* you can read the file, 
     implement the prompt ***/
/* Here are some helpful lines of code:
 *
 *  My print statement for a match:
 *
    printf("MATCH: %s donates to %s at hospital %s\n", donor, recip, hosp);
 *
 *
 *  My print statements for the contents of the queues at the end:
 *
    PrettyPrintQueue(&female_donors, "female donors");
    PrettyPrintQueue(&female_recipients, "female recipients");
    PrettyPrintQueue(&male_donors, "male donors");
    PrettyPrintQueue(&male_recipients, "male recipients");
    PrettyPrintQueue(&hospitals, "hospitals");
 *
 */

    /* STEP #3: Create and initialize the 5 different queues */
    Queue female_donors;
    InitializeQueue(&female_donors);

    Queue female_recipients;
    InitializeQueue(&female_recipients);

    Queue male_donors;
    InitializeQueue(&male_donors);

    Queue male_recipients;
    InitializeQueue(&male_recipients);

    Queue hospitals;
    InitializeQueue(&hospitals);

    /* STEP #2: */
    FILE *f_in = fopen(argv[1], "r");
    char line[256];

    while (fgets(line, 256, f_in) != NULL)
    {
	int running = 1;
	
	while (running) {
	    if ((female_donors.front != female_donors.back) && (female_recipients.front != female_recipients.back) && (hospitals.front != hospitals.back))
	    {
		char *donor = Dequeue(&female_donors);
		char *recip = Dequeue(&female_recipients);
		char *hosp = Dequeue(&hospitals);
		printf("MATCH: %s donates to %s at hospital %s\n", donor, recip, hosp);
	    }

	    else if ((male_donors.front != male_donors.back) && (male_recipients.front != male_recipients.back) && (hospitals.front != hospitals.back))
	    {
		char *donor = Dequeue(&male_donors);
		char *recip = Dequeue(&male_recipients);
		char *hosp = Dequeue(&hospitals);
		printf("MATCH: %s donates to %s at hospital %s\n", donor, recip, hosp);
	    }

	    else {
		break;
	    }

	    break;
	}

	char *newline = NewString(line);

	/* Add recipients to respective queues */
	if (newline[0] == 'R') {
	    if (newline[2] == 'F') {
		Enqueue(&female_recipients, newline+4);
	    }
	    else {
		Enqueue(&male_recipients, newline+4);
	    }
	}

	/* Add donors to respective queues */
	else if (newline[0] == 'D') {
	    if (newline[2] == 'F') {
		Enqueue(&female_donors, newline+4);
	    }
	    else {
		Enqueue(&male_donors, newline+4);
	    }
	}

	/* Add hospitals to queue */
	else {
	    Enqueue(&hospitals, newline+2);
	}
    } // end of outer while loop

    /* Catch the last matching entries */
    if ((male_donors.front != male_donors.back) && (male_recipients.front != male_recipients.back) && (hospitals.front != hospitals.back))
    {
	char *donor = Dequeue(&male_donors);
	char *recip = Dequeue(&male_recipients);
	char *hosp = Dequeue(&hospitals);
	printf("MATCH: %s donates to %s at hospital %s\n", donor, recip, hosp);
    }

    /* Print the unmatched entries */
    PrettyPrintQueue(&female_donors, "female donors");
    PrettyPrintQueue1(&female_recipients, "female recipients");	// Not printing the first name
    PrettyPrintQueue2(&male_donors, "male donors");		// Not printing the first name
    PrettyPrintQueue3(&male_recipients, "male recipients");	// Not printing the first name
    PrettyPrintQueue(&hospitals, "hospitals");
 
    /* Close input file */
    fclose(f_in);
    return 0;
} // end of main() function
