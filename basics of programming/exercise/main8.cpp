/* Write a program that receives two numbers n and m, and prints their greatest common divisor (GCD) and least common multiple (LCM).
Input: First, n and then m are given to you.
1 ≤ n, m ≤ 500
Output: First, print the GCD, followed by the LCM, separated by a space.
Example:
Sample Input 1:
8 20
Sample Output 1:
4 40
Sample Input 2:
24 65
Sample Output 2:
1 1560
*/
#include<iostream>
using namespace std;
int main(){
    long int a,b,c,s,r,d;
    cin>>a>>b;
    s=a;
    for(c=b;c>0;c=r){
        r=s%c;
        s=c;
    }

    d=(a*b)/s;
    cout<<s<<" "<<d;

    return 0;
}

