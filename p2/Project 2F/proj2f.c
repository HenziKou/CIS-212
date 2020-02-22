#include <stdio.h>
#include <printf.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	/* Initialize variables */
	FILE *f_in, *f_out;
	int value;

	/* Argument count must have 3 values */
	if (argc != 3)
	{
		printf("Usage: %s <file1> <file2>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	/* Open input and output files */	
	f_in = fopen(argv[1], "r");
	f_out = fopen(argv[2], "w");

	/* Go through the first 5 sub-arrays */
	for (int i = 0; i < 45; i += 10)
	{
		/* Go through the first 5 elements within each sub-array */
		for (int j = 0; j < 5; j++)
		{
			fseek(f_in, i+j, SEEK_SET);
			value = ftell(f_in);
			fprintf(f_out, "%d\n", value);
		}
	}			

	/* Close file streams */
	fclose(f_in);
	fclose(f_out);

	return 0;
}

/*
Zayd's psuedo code for project:

int arr(25);
int *a = arr;

for (int i = 0; i < 25; i++) {
	fread(a, sizeof(int), arr, f_in);
	a++;

	if (i % 5 == 4)
		fseek();
}

Another for loop down below.
*/
