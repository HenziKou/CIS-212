#include <stdio.h>
#include <stdbool.h>

bool primeChecker(int n) {	
	/* Loop through all possible multiples of n besides 1 and itself */
	for (int i = 2; i <= n / 2; i++) {
		/* Is it prime? */
		if (n % i == 0)
			return false;
	}
	
	return true;
}

int main() {
	/* Iterate primeChecker function from 5 to 100 to check for primes */
	for (int j = 5; j < 101; j++) {
		if (primeChecker(j) == true)
			printf("%d is a prime number\n", j);
	}
}


/* Zayd's answer:
#include <stdio.h>
#include <stdbool.h>

int main() {
	for (int i = 5; i < 101; i++) {
		bool is_prime = true;
		for (int j = 2; j < i; j++) {
			if (i % k == 0)
				is_prime = false;
		}
		if (is_prime)
			printf("%d is a prime number\n", i);
	}
	return 0;
}
*/
