/*You are tasked with writing a program that converts a given sentence into a list of integers stored in an array of type int, where each integer represents a block of four consecutive characters from the input sentence. This is the reverse process of a given C++ code that reads an array of integers as blocks of characters and prints a decoded sentence.
The sentence will be encoded such that:
Each int (32 bits) represents four characters (8 bits per character).
You need to determine how many int elements are required to store the entire sentence, and then convert the sentence into the corresponding integers.
Input
A single line containing the sentence that needs to be converted.
Output
The first line of the output should be the number of integers needed.
The next lines should contain each integer representing a block of four characters from the sentence.
Example
Input 1:
Those who can imagine anything, can create the impossible.
Output 1:
15
1936681044
1752637541
1633886319
1835606126
1852401505
1851859045
1768453241
539780974
544104803
1634038371
1948280180
1763730792
1936683117
1818388851
1862282853*/
#include <iostream>
using namespace std;
int main(){
    char a[50];
    for (int j=0;j<50;j++)
        a[j]=0;
    cin.getline(a,50);
    int array[50];
    for (int j=0;j<50;j++)
        array[j]=0;
    int counter=0;
    int * p = (int *)a ;
    while(*p!=0) {
        array[counter] = *p;
        counter++;
        p++;
    }

    if(!(counter%4==0)){
        cout << counter << endl;
        for (int i=0;i<counter;i++){
            cout << array[i] << endl;
        }
    }
    else{
        cout << counter+1 << endl;
        for (int i=0;i<counter;i++){
            cout << array[i] << endl;
        }
        cout << 0 << endl;
    }
}
