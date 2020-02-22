/*
 * I believe I have completed:
 *  Map based on linked lists: yes
 *  Double hashing: yes
 *  Performance study: yes
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

// Defining a prime number to use for second hash function
#define PRIME 97

typedef struct
{
    char    *symbol;
    char    *name;
    float    lastSale;
    float    marketCap;
    int      IPOyear;
} Company;

/* IMPLEMENT SINGLE LINKED LIST BELOW */
struct Node {
    struct Node *next;
    //char *key;
    Company *companies;
};

struct Node *ll_insert(struct Node *head, Company *c)
{
    /* Implementing a linked list that inserts a new node at the beginning of the list */
    struct Node *n = malloc(sizeof(struct Node));	// Do I need to typecast *rv?

    // Assign all of a company's data into a new node's data field
    n->companies = c;

    // Point the new node to the previous node
    n->next = head;

    // Repoint the head to the new node
    head = n;

    return n;
}

struct Node *ll_fetch(struct Node *head, char *key)
{
    // Linked list is empty
    if (head == NULL)
		return NULL;

    /* special case for head matching v */
    if (strcmp(head->companies->symbol, key) == 0)
		return head->next;

    struct Node *prev = head;
    struct Node *curr = head->next;

    // Iterate through whole linked list till reaching the last node
    while (curr != NULL)
    {
		if (strcmp(curr->companies->symbol, key) == 0)
		{
	    	// Set head node (first node) to point to third node
	    	prev->next = curr->next;
	    	free(curr);
	    	return curr;
		}

		prev = curr;
		curr = curr->next;
    }

    return head; /* nothing removed */
}

void ll_PrintCompany(struct Node *head)
{
    printf("%s:\n", head->companies->name);
    printf("\tSymbol: %s\n", head->companies->symbol);
    /* .2f: only print two digits after the period. */
    printf("\tLast Sale: %.2f\n", head->companies->lastSale);
    printf("\tMarket Capitalization: %.2f\n", head->companies->marketCap);
    printf("\tYear of Initial Public Offering: %d\n", head->companies->IPOyear);
}

void ll_FetchAndPrint(struct Node *head, char *key)
{
    struct Node *curr = ll_fetch(head, key);

    if (curr == NULL) {
		printf("Key %s has no corresponding company\n", key);
    }

    else {
		ll_PrintCompany(curr);
    }
}

/* IMPLEMENT SINGLE LINKED LIST ABOVE */


void PrintCompany(Company *c)
{
    printf("%s:\n", c->name);
    printf("\tSymbol: %s\n", c->symbol);
    /* .2f: only print two digits after the period. */
    printf("\tLast Sale: %.2f\n", c->lastSale);
    printf("\tMarket Capitalization: %.2f\n", c->marketCap);
    printf("\tYear of Initial Public Offering: %d\n", c->IPOyear);
}

void ReadFile(const char *filename, Company **companies_rv, int *numCompanies_rv)
{
    int  i, j;

    if (filename == NULL)
    {
        fprintf(stderr, "No filename specified!\n");
        exit(EXIT_FAILURE);
    }
    FILE *f_in = fopen(filename, "r");
    if (f_in == NULL)
    {
        fprintf(stderr, "Unable to open file \"%s\"\n", filename);
        exit(EXIT_FAILURE);
    }

    fseek(f_in, 0, SEEK_END);
    int numChars = ftell(f_in);
    // printf("The number of characters is %d\n", numChars);
    fseek(f_in, 0, SEEK_SET);

    char *file_contents = malloc(sizeof(char)*numChars);
    fread(file_contents, sizeof(char), numChars, f_in);
    fclose(f_in);
    /* Note: the memory for this array is used to populate
     * the fields of the companies.  If it is freed, then
     * the company structs all become invalid.  For the
     * context of this program, this array should not be 
     * freed. */

    // Find out how many lines there are
    int numLines = 0;
    for (i = 0 ; i < numChars ; i++)
        if (file_contents[i] == '\n')
            numLines++;
    // printf("Number of lines is %d\n", numLines);

    int      numCompanies = numLines-1; // first line is header info 
    Company *companies    = malloc(sizeof(Company)*numCompanies);

    /* strtok will parse the file_contents array.  
     * The first time we call it, it will replace every '"' with '\0'.
     * It will also return the first word before a 
     */
    int numColumns = 9;
    int numberOfQuotesPerColumn = 2;
    strtok(file_contents, "\"");
    for (i = 0 ; i < numberOfQuotesPerColumn*numColumns-1 ; i++)
         strtok(NULL, "\"");
    for (i = 0 ; i < numCompanies ; i++)
    {
         companies[i].symbol = strtok(NULL, "\"");
         strtok(NULL, "\"");
         companies[i].name = strtok(NULL, "\"");
         strtok(NULL, "\"");
         companies[i].lastSale = atof(strtok(NULL, "\""));
         strtok(NULL, "\"");
         companies[i].marketCap = atof(strtok(NULL, "\""));
         strtok(NULL, "\""); 

         /* Skip ADR TSO */
         strtok(NULL, "\"");
         strtok(NULL, "\"");

         companies[i].IPOyear = atoi(strtok(NULL, "\""));
         strtok(NULL, "\"");

         /* Skip Sector, Industry, Summary Quote */
         for (j = 0 ; j < 6 ; j++)
             strtok(NULL, "\"");

         //PrintCompany(companies+i);
    }

    /* Set parameters to have output values */
    *companies_rv    = companies;
    *numCompanies_rv = numCompanies;
}

int hash(char *name, long array_size)
{
    int hashval = 0;
    char *p = name;

    while (*p != '\0')
    {
        hashval = 31*hashval + *p;
        p++;
    }

    return hashval%array_size;
}

/* Second hash function copied from GeeksforGeeks
   https://www.geeksforgeeks.org/double-hashing/ */
int hash2(char *name)
{
    int hashval = 0;
    char *p = name;

    while (*p != '\0')
    {
	hashval = 31*hashval + *p;
	p++;
    }

    return (PRIME - (hashval % PRIME));		// PRIME = 97
}
/* Second hash function */

typedef struct 
{
    int         numElements;
    char      **keys;
    Company    *companies;
} MapBasedOnHashTable;

void InitializeMapBasedOnHashTable(MapBasedOnHashTable *map, int numElements)
{
    map->numElements = numElements;
    map->keys = malloc(sizeof(char *)*numElements);
    map->companies = malloc(sizeof(Company)*numElements);
    for (int i = 0 ; i < numElements ; i++)
        map->keys[i] = NULL;
}

void StoreTo_MapBasedOnHashTable(MapBasedOnHashTable *map, Company *c)
{
    int hashval = hash(c->symbol, map->numElements);

    int hashval2 = hash2(c->symbol);

    // If bucket collision occurs
    if (map->keys[hashval] != NULL)
    {
	for (int i = 0; i < map->numElements; i++)
	{
	    // Get double hash bucket jump
	    int idx = (hashval + i * hashval2) % (map->numElements);

	    // Counter measure for negative indicies
	    if (idx < 0)
		idx += map->numElements;

	    // If no bucket collision occurs store the key 
	    if (map->keys[idx] == NULL)
	    {
		map->keys[idx] = c->symbol;
		map->companies[idx] = *c;
		return;
	    }
	}
    }

    // If no bucket collision occurs
    else {
	map->keys[hashval] = c->symbol;
	map->companies[hashval] = *c;
	return;
    }
}

Company *FetchFrom_MapBasedOnHashTable(MapBasedOnHashTable *map, char *key)
{
    int hashval = hash(key, map->numElements);
    int hashval2 = hash2(key); // implementing a 2nd hash

    // Bucket is not empty so retreive element
    if (map->keys[hashval] != NULL)
    {
	for (int i = 0; i < map->numElements; i++)
	{
	    // Get double hashing bucket jump
	    int idx = (hashval + i * hashval2) % (map->numElements);

	    // Counter measure for negative indicies
            if (idx < 0)
		idx+= map->numElements;

	    // If empty bucket then return
            if (map->keys[idx] == NULL)
		return NULL;

	    // Return company if keys match
            if (strcmp(map->keys[idx], key) == 0)
		return &(map->companies[idx]);
	}
    }

    // Empty bucket
    else {
	printf("Empty bucket\n");
	return NULL;
    }

    // No element exists
    return NULL;
}

void FetchAndPrint(MapBasedOnHashTable *mfht, char *key)
{
    Company *c = FetchFrom_MapBasedOnHashTable(mfht, key);
    if (c == NULL)
    {
        printf("Key %s has no corresponding company\n", key);
    }
    else
    {
        PrintCompany(c);
    }

}

int main(int argc, char *argv[])
{
    Company *companies = NULL;
    int      numCompanies;
    ReadFile(argv[1], &companies, &numCompanies);
    printf("num companies is %d\n", numCompanies);

    /* IMPLEMENTING HASH MAP */
/*
    MapBasedOnHashTable mfht;
    InitializeMapBasedOnHashTable(&mfht, numCompanies*2);

    // Start timer for storing and fetching with double hashing
    printf("Starting timer for double hashing.\n");
    struct timeval startTime;
    gettimeofday(&startTime, 0);

    for (int i = 0 ; i < numCompanies ; i++)
    {
        StoreTo_MapBasedOnHashTable(&mfht, companies+i);
	// Same as:
	// StoreTo_MapBasedOnHashTable(&mfht, &(comapnies[i]));
    }

    FetchAndPrint(&mfht, "ZNWAA");
    FetchAndPrint(&mfht, "Z");
    FetchAndPrint(&mfht, "ZIOP");
    FetchAndPrint(&mfht, "ZIOQ");
    FetchAndPrint(&mfht, "YIOQ");
    FetchAndPrint(&mfht, "QIOQ");
    FetchAndPrint(&mfht, "WIOQ");
    FetchAndPrint(&mfht, "XIOQ");
    FetchAndPrint(&mfht, "TIOQ");
    FetchAndPrint(&mfht, "UIOQ");
    FetchAndPrint(&mfht, "VIOQ");

    // End timer for storing and fetching with double hashing
    struct timeval endTime;
    gettimeofday(&endTime, 0);
    printf("Timer done for double hashing.\n");

    double seconds = ((double)(endTime.tv_sec - startTime.tv_sec) +
		     (double)(endTime.tv_usec - startTime.tv_usec)) / 1000000;
    printf("\tTIME: %f seconds.\n", seconds);
*/
    /* IMPLEMENTING HASH MAP */



    /* IMPLEMENTING LINKED LISTS */

    // Initialize the test cases and function for linked list
    struct Node *head = NULL;

    // Start timer for storing and fetching with linked list
    printf("Starting timer for linked list.\n");
    struct timeval startTime;
    gettimeofday(&startTime, 0);

    for (int j = 0; j < numCompanies; j++)
    {
	head = ll_insert(head, companies+j);
    }

    ll_FetchAndPrint(head, "ZNWAA");
    ll_FetchAndPrint(head, "Z");
    ll_FetchAndPrint(head, "ZIOP");
    ll_FetchAndPrint(head, "ZIOQ");
    ll_FetchAndPrint(head, "YIOQ");
    ll_FetchAndPrint(head, "QIOQ");
    ll_FetchAndPrint(head, "WIOQ");
    ll_FetchAndPrint(head, "XIOQ");
    ll_FetchAndPrint(head, "TIOQ");
    ll_FetchAndPrint(head, "UIOQ");
    ll_FetchAndPrint(head, "VIOQ");

    // End timer for storing and fetching with linked list
    struct timeval endTime;
    gettimeofday(&endTime, 0);
    printf("Timer done for linked list.\n");

    double seconds = ((double)(endTime.tv_sec - startTime.tv_sec) +
		     (double)(endTime.tv_usec - startTime.tv_usec)) / 1000000;
    printf("\tTIME: %f seconds.\n", seconds);

    /* IMPLEMENTING LINKED LISTS */
}

/* YOUR PERFORMANCE STUDY WRITEUP GOES HERE:
 
    The second hash function is inspired by the example on GeeksForGeeks and the first
    hash function provided. It takes the length of the hashval and is modified by an
    arbitrarily large prime number to help prevent clustering.

    DOUBLE HASHING:
	- Time: 0.000523 seconds

    SINGLE LINKED LIST:
	- Time: 0.000851 seconds

    When it comes to storing/inserting information, it is more optimal to use a linked list
    because its time complexity is O(1) whereas double hashing is O(n^2). However this is
    counter balanced when it comes to fetching information. Linked list is slower when it
    comes to fetching a node. Therefore the run times above highlight the overall speed
    when it comes to the operation of storing and fetching.
 */
