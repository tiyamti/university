/*Write a program that calculates and prints the factorial of a given natural number.
Input: The input consists of a single line containing a natural number n.
1 ≤ n ≤ 20
Output: Print the factorial of n in a single line.
Example:
Sample Input 1:
7
Sample Output 1:
5040
Sample Input 2:
5
Sample Output 2:
120*/
#include<iostream>

using namespace std;
int main(){
    int x,fact=1,n;
    cin>>n;
    for(x=1;x<=n;x++) {
        fact = fact * x;
    }
    cout<<fact;
    return 0;
}