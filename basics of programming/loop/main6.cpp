/*Write a program that, given an input number n, factors it into its prime factors and displays it in the following format:
100 = 2^2 × 5^2
Input:
A single line containing the number n.
Constraints:
1 ≤ n ≤ 10^8
Output:
Print the prime factorization of the number. The prime factors should be listed in ascending order, and exponents should be indicated using the ^ symbol.
Examples:
Sample Input 1:
100
Sample Output 1:
2^2*5^2
Sample Input 2:
13
Sample Output 2:
13
Sample Input 3:
98
Sample Output 3:
2*7^2*/
//answer:

#include <iostream>
#include <math.h>
using namespace std;


void primeFactors(int n) {
    int x;
    int tavan = 0, tedad = 0;

    for (int i = 2; i <= n; i++) {
        tavan = 0;
        while (n % i == 0) {

            n = n / i;
            tavan = tavan + 1;
            tedad = tedad + 1;
        }
        if (tedad > tavan && tavan >= 1) {
            printf("*");
        }
        if (tavan == 1) {
            printf("%d", i);
        }
        if (tavan >= 2) {
            cout<<i<<"^"<<tavan;
        }
    }

}



int main()
{
    int n;
    cin>>n;
    primeFactors(n);
    return 0;
}
