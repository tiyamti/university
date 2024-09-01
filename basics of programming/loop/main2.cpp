/*Write a program that reads a number n and prints the smallest power of two that is greater than n.
Input:
The input consists of a single line containing the number n.
1 ≤ n ≤ 10^9
Output:
Print the smallest power of two greater than n.
Examples:
Sample Input 1:
95
Sample Output 1:
128
Explanation:
2^6 = 64 ≤ 95 < 128 = 2^7
So the answer is 128.
Sample Input 2:
1024
Sample Output 2:
2048
Explanation:
2^10 = 1024 ≤ 1024 < 2048 = 2^11
So the answer is 2048.
Explanation of the sample:
First, read the number n. Then, use a loop where the variable i starts at 1, and in each iteration, double i until it becomes greater than n. The first i that is greater than n is the answer.*/
//answer:
#include<iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int main() {
    int tavan=1;
    int adadvarede;
    cin>>adadvarede;
    while(adadvarede<tavan){
        tavan=tavan*2;
    }
    while(adadvarede>tavan){
        tavan=tavan*2;
    }
    printf("%d" , tavan);
    return 0;
}
