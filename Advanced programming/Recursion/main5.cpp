/*Harry has a limited space, so he needs to choose which items to take with him. To help with this, Harry creates a game. The game works like this: if Harry has n items arranged in a circle, each item is numbered from 1 to n. Starting from the second item (item number 2), every alternate item is removed until only one item remains. Your task is to write a recursive function that determines which item will be selected in the end.
Input:
The input consists of a single line containing a natural number n.
1 ≤ n ≤ 5000
Output:
The output should be the number of the last remaining item.
Example:
Input 1:
12
Output 1:
9*/
#include <iostream>
using namespace std;
int select_circle(int array_circle[],int number_of_len){
    int new_array[number_of_len/2];
    int len=sizeof(new_array)/sizeof(new_array[0]);
    for (int i = 0; i <= number_of_len / 2; i++) {
        if(len>1) {
            if (number_of_len % 2 == 0) {
                array_circle[2 * i + 1] = array_circle[2 * i + 2];
                new_array[i] = array_circle[2 * i];
            }
            else{
                array_circle[2 * i ] = array_circle[2 * i + 2];
                new_array[i] = array_circle[2 * i];
            }
        }
        else{
            if(number_of_len%3==0) {
                new_array[i] = array_circle[2 * i + 2];
            }
            else{
                new_array[i] = array_circle[2 * i ];
            }
        }
    }

    if(len==1){
        cout<<new_array[0];
    }
    else{
        select_circle(new_array,len);
    }
}
void array_maker(int number_of_len){
    int array_circle[ number_of_len];
    for(int i=1;i<=number_of_len;i++){
        array_circle[i-1]=i;
    }
    select_circle(array_circle,number_of_len);
}
int main() {
    int n;
    cin>>n;
    array_maker(n);

    return 0;
}
