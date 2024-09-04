/*You are tasked with finding how many natural numbers less than or equal to a given number n are coprime with n. Two numbers are considered coprime if their greatest common divisor (GCD) is 1. You need to implement a program to calculate this efficiently.
Input
The input consists of a single integer n where
1≤n≤100,000.
Output
Output the count of numbers less than or equal to n that are coprime with n.
Approach
To solve this problem, you will use the Euler's Totient Function phi(n), which gives the count of numbers less than or equal to n that are coprime with n.
Euler's Totient Function
The Euler's Totient function phi(n) is calculated as follows:
Start with result = n.
For each prime factor p of n, update the result by multiplying it by (1 - 1/p), i.e., result = result * (p - 1) / p.
Helper Functions
GCD function: A function to compute the greatest common divisor (GCD) of two numbers using the Euclidean algorithm.
Totient function (phi): A function that implements the calculation of phi(n) based on the prime factorization of n.
Example
Input:
75
Output:
40*/
#include <iostream>
using namespace std;
int gcd(int a, int b) {
    if (a == 0 || b == 0)
        return 0;
    else if (a == b)
        return a;
    else if (a > b)
        return gcd(a-b, b);
    else return gcd(a, b-a);
}
int phi(int x){
    int counter,gccd;
    for (int i=0;i<=x;i++){
        gccd=gcd(x,i);
        if(gccd==1)
            counter++;
    }
    return counter;
}
int main() {
    int nu ;
    cin >> nu ;
    cout << phi(nu);
}