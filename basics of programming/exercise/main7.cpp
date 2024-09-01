/*Write a program that, by taking a number n as input, computes the nth Fibonacci number.
The Fibonacci function is a well-known function defined recursively, where each term is calculated based on the two previous terms:
fib(1) = fib(2) = 1
fib(n) = fib(n − 1) + fib(n − 2)
The table below provides examples of input and output for this function:
Input	Output
11	89
16	987
Input: The input consists of a single line containing a natural number n.
1 ≤ n ≤ 300
Output: Your program should print the nth Fibonacci number fib(n).
Example:
Sample Input:
16
Sample Output:
987
*/
#include <bits/stdc++.h>
using namespace std;

int fib(int n)
{
    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}
int main()
{
    int n;
    cin>>n;
    cout << fib(n);
    getchar();
    return 0;
}
