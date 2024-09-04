/*You need to implement a class z_string that can store and compare two character arrays (representing strings) without using the C++ string library. The class should include the following functionalities:
A constructor that takes a character array and its size, initializing the string.
A method getSize() that returns the size of the string.
A method compareTo(z_string str) that compares the current string with another z_string based on alphabetical order (lexicographical comparison).
A method print() that prints the string.
Input:
The first integer represents the size of the first string.
The second input is the first string.
The third integer represents the size of the second string.
The fourth input is the second string.
Output:
If the first string is greater (lexicographically), print Yek>Do.
If the second string is greater, print Do>Yek.
If the two strings are equal, print Yek==Do.
Example Input 1:
7 student 7 student
Example Output 1:
Yek==Do
Example Input 2:
3 gry 3 sly
Example Output 2:
Do>Yek
Example Input 3:
9 slytherin 10 gryffindor
Example Output 3:
Yek>Do*/
#include <iostream>
#include <cstring>
using namespace std;
class z_string
{
private:
    char * str;
    int size;
public:
    z_string(char * s,int size){
        str=s;
        this->size=size;
    }
    int getSize(){
        return size;
    }
    int compareTo(z_string str){
        int answer;
        answer = strcmp(this->str, str.str);
        if (answer > 0) {
            return 1;
        } else if (answer < 0) {
            return -1;
        } else if (answer == 0) {
            return 0;
        }
    }
    void print(){
        for (int i=0;i<size;i++)
            cout << *(str+i);
    }
};
/*int z_string::compareTo(z_string str) {
    int answer;
    answer = strcmp(this->str, str.str);
    if (answer > 0) {
        return 1;
    } else if (answer < 0) {
        return -1;
    } else if (answer == 0) {
       return 0;
    }

}
void z_string::print() {
    for (int i=0;i<size;i++) {
        cout << *(str + i);
    }
}*/
int main() {
    int number1=0,number2=0, answer;
    char* string1= nullptr;
    char* string2=nullptr;
    cin >> number1 ;
    char array1[number1];
    for (int i=0;i<number1;i++) {
        cin >> array1[i];
    }
    cin >> number2;
    char array2[number2];
    for (int j=0;j<number2;j++) {
        cin >> array2[j];
    }
    string1= array1;
    string2= array2;
    z_string str1(string1,number1);
    z_string str2(string2,number2);
    answer= str1.compareTo(str2);
    if (answer==-1)
        cout << "Yek<Do";
    else if (answer==1)
        cout << "Yek>Do";
    else if (answer==0)
        cout << "Yek==Do";
    return 0;
}
