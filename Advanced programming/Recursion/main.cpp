/*Turing needs to generate sequences of 0s and 1s such that in no sequence are there three consecutive 0s. Write a recursive program that helps him achieve this.
Input:
The input consists of a single integer n, which represents the length of the sequence Turing needs to generate.
1 ≤ n ≤ 30
Output:
The output should be the number of all possible sequences of length n such that there are no three consecutive 0s.
Example:
Input 1:
5
Output 1:
24
Constraints:
A recursive solution must be used to solve the problem.*/
#include <bits/stdc++.h>
using namespace std;

int binary(int n)
{
    int a = 2, b = 4, c=7,d, i;
    if( n == 0)
        return a;
    for(i = 2; i <= n; i++)
    {
        d = a + b+c;
        a = b;
        b = c;
        c=d;
    }
    return a;

}

int main()
{
    int n ;
    cin>>n;
    cout << binary(n);
    return 0;
}
