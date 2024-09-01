/*Write a program that receives three numbers as input and determines whether the sum of any two of them equals the third number.
Input:
The input consists of a single line containing three natural numbers a, b, and c separated by spaces.
1 ≤ a, b, c ≤ 10^4
Output:
Your program should print "yes" if the sum of any two numbers equals the third; otherwise, it should print "no".
Example:
Sample Input 1:

10 45 35
Sample Output 1:
yes
Sample Input 2:
101 1500 100
Sample Output 2:
no
*/
//answer:
#include <iostream>

int main() {
    int number1 , number2 , number3 ;
    scanf("%d" "%d" "%d", &number1 , &number2 , &number3);
    if (number1+number2==number3 or number2+number3==number1 or number1+number3==number2){
        printf("yes");
    }
    else{
        printf("no");
    }
    return 0;
}
