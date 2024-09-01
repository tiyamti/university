/*You are given four two-digit hexadecimal numbers separated by spaces. Each hexadecimal number corresponds to an ASCII character. Your task is to convert these hexadecimal numbers to their respective ASCII characters and print the resulting string without any spaces.
Input:
A single line containing four two-digit hexadecimal numbers separated by spaces.
Output:
The string of ASCII characters corresponding to the given hexadecimal numbers, printed without any spaces.
Examples:
Input Example 1:
42 61 6E 6B
Output Example 1:
Bank
*/
//answer:
#include <iostream>
using namespace std;
int main(){
    int a[4];
    for(int j=0;j<4;j++){
        cin>>hex>>a[j];
    }
    for(int i =0;i<4;i++){
        cout<<char(a[i]);
    }
    cout<<endl;
    return 0;
}
