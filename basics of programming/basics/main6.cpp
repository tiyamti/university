/*You have a rectangular cake with dimensions x and y. You can only make cuts that are a units apart (i.e., the distance between consecutive cuts is exactly a units). To avoid wasting cake, you want to make the minimum number of cuts parallel to the sides of the cake. Your task is to calculate the minimum number of pieces the cake can be divided into. The sizes of the pieces do not need to be the same.
Input:
The input consists of a single line containing three natural numbers x, y, and a separated by spaces.
The range for the numbers is:
1 ≤ x, y, a ≤ 10^6
Output:
Print the minimum number of cake pieces in one line.
Examples:
Sample Input 1:
7 16 3
Sample Output 1:
18
Explanation:
The cake is a rectangle with dimensions 7 and 16. To avoid waste, the cake is divided into 10 square pieces with sides of 3 units, 7 rectangular pieces with dimensions 1x3, and 1 square piece with sides of 1 unit, making a total of 18 pieces.
Sample Input 2:
20 30 6
Sample Output 2:
20
Explanation:
The cake is divided into 3 parts of length 6 and 1 part of length 2 along the width, and into 5 parts of length 6 along the length, resulting in a total of 20 pieces.*/
//answer:
#include <iostream>

using namespace std;
int main() {
    int num1,num2,num3,answer1,answer2,answer3,if1,if2;
    cin>>num1>>num2>>num3;
    answer1 = num1/num3;
    answer2 = num2/num3;
    if(num1%num3 != 0 || num2%num3 != 0){
        if (num1%num3 < num3 && num2%num3 == 0){
            if1=answer1+1;
            answer3 = if1 * answer2;
            cout<<answer3;
        }
        if(num2%num3 < num3 && num1%num3 == 0){
            if2=answer2+1;
            answer3 = answer1 * if2;
            cout<<answer3;
        }


    }
    if(num1%num3 < num3 && num2%num3 <num3){
        if1 = answer1+1;
        if2 = answer2+1;
        answer3 = if1 * if2;
        cout<<answer3;
    }
    else{
        answer3 = answer1 * answer2;
        cout<<answer3;
    }


    return 0;
}