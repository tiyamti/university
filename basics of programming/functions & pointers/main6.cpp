/*Your program first receives one of the following four strings: "double", "float", "char", or "int". Then, it receives two numbers, which are memory addresses corresponding to two hypothetical elements of an array with the data type specified by the string received at the start. Using a function, you need to calculate how many elements of the array are between these two addresses, including the two specified addresses.
Consider the sizes of the data types in bytes as follows:
"double": 8 bytes
"float": 4 bytes
"char": 1 byte
"int": 4 bytes
Input:
The first input is one of the strings "double", "float", "char", or "int".
The second line contains the two memory addresses.
Output:
Print the number of elements of the array between the two memory addresses, including the two given elements.
Example:
Sample Input 1:
int
1234 1594
Sample Output 1:
91
Sample Input 2:
char
9990 59378
Sample Output 2:
49389
Note: You must use a function to solve this problem. Without a function, you might receive points in Quera, but your exercise will be manually graded later, and not following this requirement could result in losing final points.*/
#include <iostream>
using namespace std;
int int_float_thing(int,int);
int char_thing(int,int);
int double_thing(int,int);

int int_float_thing(int number1,int number2){
    int answer=(number1-number2)/4+1;
    return answer;
}
int char_thing(int number1,int number2){
    int answer=(number1-number2)+1;
    return answer;
}
int double_thing(int number1,int number2){
    int answer=(number1-number2)/8+1;
    return answer;
}
int main() {
    string type_word;
    int number1,number2,temp,answer;
    cin>>type_word;
    cin>>number1>>number2;
    if(number2>number1){
        temp=number2;
        number2=number1;
        number1=temp;
    }
    if(type_word=="int"){
        answer= int_float_thing(number1,number2);
    }
    else if(type_word=="float"){
        answer= int_float_thing(number1,number2);
    }
    else if(type_word=="char"){
        answer= char_thing(number1,number2);
    }
    else if(type_word=="double"){
        answer= double_thing(number1,number2);
    }
    cout<<answer;
    return 0;
}
