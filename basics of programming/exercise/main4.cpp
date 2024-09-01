/*Write a program that takes three numbers as input and prints their average.
Input
Three numbers are entered on a single line.
Output
The average of the numbers is printed on one line.
Example:
Sample Input 1:
231 -297 171
Sample Output 1:
35
Sample Input 2:
165 -72 -147
Sample Output 2:
-18*/
#include <iostream>
using namespace std;
int main() {
    double a,b,c,answ;
    cin>>a>>b>>c;
    answ=(a+b+c)/3;
    cout<<answ;
    return 0;
}
