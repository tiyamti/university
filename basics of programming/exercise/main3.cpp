/*Write a program that takes two numbers as input and prints the larger one.
Input
Two numbers are entered on a single line.
Output
Your program should print the larger number.
Example:
Sample Input 1:
1737 -3282
Sample Output 1:
1737
Sample Input 2:
-9283 -8520
Sample Output 2:
-8520*/
#include <iostream>
using namespace std;
int main() {
    int a,b;
    cin>>a>>b;
    if(a<b){
        cout<<b;
    }
    else{
        cout<<a;
    }
}
