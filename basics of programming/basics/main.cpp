/*Write a program that takes two ASCII codes and determines if both correspond to the same English letter, regardless of case.
Input:
The input consists of two natural numbers, n and m, representing the two ASCII codes.
Note that the order of the given ASCII codes doesn't matter, and there is no difference whether the first code is for a lowercase letter and the second is for an uppercase letter or vice versa.
Output:
If both ASCII codes represent the same English letter (ignoring case), print "YES"; otherwise, print "NO".
Example:
Sample Input 1:
65
97
Sample Output 1:
YES
Explanation: ASCII code 65 corresponds to 'A', and ASCII code 97 corresponds to 'a'.
Sample Input 2:
68
79
Sample Output 2:
NO
Explanation: ASCII code 68 corresponds to 'D', and ASCII code 79 corresponds to 'O'.
Sample Input 3:
70
109
Sample Output 3:
NO
Explanation: ASCII code 70 corresponds to 'F', and ASCII code 109 corresponds to 'm'.*/

//answer:
#include <iostream>
using namespace std;
int main() {
    float char1 , char2;
    cin>>char1>>char2;
    if((char1<= 122 && char1 >=65) && (char2<=122 && char2>=65)){
        if(char1-char2== 32 || char1-char2 == -32 || char1-char2 == 0){
            printf("Yes");
        }
        else{
            printf("No");
        }
    }
    else{
        printf("No");
    }
    return 0;
}
