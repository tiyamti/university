/*Write a program that takes a number as input and determines if the number is prime or composite.
Input
In the only input line, there is an integer n where:
2 ≤ n ≤ 10^4
Output
If the number is prime, print Prime. If the number is composite, print NotPrime.
Example:
Sample Input 1:
101
Sample Output 1:
Prime
Sample Input 2:
1200
Sample Output 2:
NotPrime
*/
#include <iostream>

using namespace std;
int main() {

    int adadvarede, i, natije = 0;
    cin>>adadvarede;
    if (adadvarede == 0 || adadvarede == 1)
        natije= 1;

    for (i = 2; i <= adadvarede / 2; ++i) {


        if (adadvarede % i == 0) {
            natije = 1;
            break;
        }
    }


    if (natije == 0)
        printf("Prime");
    else
        printf("NotPrime");

    return 0;
}