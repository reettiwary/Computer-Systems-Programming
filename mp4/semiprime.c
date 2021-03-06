#include <stdlib.h>
#include <stdio.h>

//partners: shreyav3, ajayk2

/*Errors found in the program are explained here:
 *Error 1 (is_prime): the return values for the cases where  
 *the numbers were prime or composite were switched. The composite case
 *should return 0 and the prime case should return 1, not switching between 
 *another. This error would have resulteeeeeed in the semiprime function
 *checking for composite factors of numbers and not prime ones.
 
 *Error 2 (print_semiprimes): when setting the value of k, it should be 
 *"k=i/j" and not "k=i%j". To determine whether to print a number or not, we 
 *need to check that the factors of i, j and k are prime. We get k by 
 *dividing i and j. For all of the semiprimes, k would have evaluated to 0 
 *since j is a factor of i. Since 0 is not a prime number, this would have 
 *cause the semiprime numbers to not be printed, as they are only printed
 *when k is prime.

 *Error 3 (print_semiprimes): through the program we never exit the for
 *loop with the variable j, once the semiprime is identified and printed. We 
 *need to add in a break statement after the printf statement to do that. If we
 *did not have this, we would end up printing semiprimes 6 and above more than 
 *once. Since printf is a statement that executed every time we find a set of 
 *primes, even though the primes are the same but in a different order. 
 */

/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1) {return 0;}
    for (i = 2; i < number; i++) { //for each number smaller than it
        if (number % i == 0) { //check if the remainder is 0
	  return 0; //changed 1 to 0
        }
    }
    return 1; //changed 0 to 1
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <=b; i++) { //for each item in interval
        //check if semiprime
        for (j = 2; j <= i; j++) {
            if (i%j == 0) {
                if (is_prime(j)) {
		  k = i/j; //changed from "%" to "/"
                    if (is_prime(k)) {
                        printf("%d ", i);
			break; // added to exit the inner loop and increment i
                    }
                }
            }
        }

    }
    printf("\n");
    return ret;

}
