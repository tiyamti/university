/*Write a program that, given an integer n from the input, prints the multiplication table from 1 to n.
Input: The input consists of a single line containing the number n. 1 ≤ n ≤ 100
Output: The output should consist of n lines. Each line should contain the multiplication table for that row up to n.
Example:
Sample Input 1:
5
Sample Output 1:
1 2 3 4 5
2 4 6 8 10
3 6 9 12 15
4 8 12 16 20
5 10 15 20 25
Sample Input 2:
11
Sample Output 2:
1 2 3 4 5 6 7 8 9 10 11
2 4 6 8 10 12 14 16 18 20 22
3 6 9 12 15 18 21 24 27 30 33
4 8 12 16 20 24 28 32 36 40 44
5 10 15 20 25 30 35 40 45 50 55
6 12 18 24 30 36 42 48 54 60 66
7 14 21 28 35 42 49 56 63 70 77
8 16 24 32 40 48 56 64 72 80 88
9 18 27 36 45 54 63 72 81 90 99
10 20 30 40 50 60 70 80 90 100 110
11 22 33 44 55 66 77 88 99 110 121*/
#include <iostream>
#include <cmath>
using namespace std;
int main() {
    int megdar,number1,number2;
    cin>>megdar;
    for(number1=1;number1<=megdar;number1++){
        for(number2=1;number2<=megdar;number2++){
            cout<<number1*number2<<"\t";

        }
        cout<<endl;
    }


    return 0;
}
