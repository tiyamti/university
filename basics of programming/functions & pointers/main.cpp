/*First, write a function called sum that takes two input arguments and returns the sum of two numbers.
Then, write a function called mul (multiplication) that also takes two input arguments and calculates the product of the two numbers using the sum function implemented above. You are not allowed to multiply the numbers directly! (Instead of direct multiplication, use a loop to add the first number to itself as many times as the second number, using the sum function.)
Input:
The input consists of two integers n and m given on two lines:
−10≤n,m≤10
Output:
Print the product of n and m.
Example 1:
Input:
2 4
Output:
8
Example 2:
Input:
-9 1
Output:
-9*/
#include <iostream>

using namespace std;
int sum(int number1_sum,int number2_sum){
    int sum;
    sum=number1_sum+number2_sum;
    return sum;
}
int mul(int number1_mul,int number2_mul){
    int answer,number1_mul2;
    if (number1_mul>0)
        number1_mul2=number1_mul*-1;
    for (int i=0;i<number1_mul;i++){
        answer+=(sum(number2_mul,number2_mul))/2;
    }
    if (number1_mul<0)
        answer=answer*-1;
    return answer;
}
int main() {
    int number1,number2;
    cin>>number1>>number2;
    int answer;
    answer=mul(number1,number2);
    cout<<answer;
    return 0;
}
