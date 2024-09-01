/*Write a program that receives an array, then prints every other element of the array starting from the first element. However, you must use pointers for traversing the array instead of indices. Don't worry, it's not too difficult!
Input:
The first line contains the number of elements in the array.
The second line contains the elements of the array.
Output: Print every other element of the array starting from the first element.
Example:
Sample Input 1:
9
1 2 3 4 5 6 7 8 9
Sample Output 1:
1 3 5 7 9
Note:
You must use dynamic arrays to receive the input.
You must use pointers to traverse the array. Even though you might get some points on Quera without doing so, your exercise will be manually graded later, and not following these instructions could result in losing final points.*/
#include <iostream>
using namespace std;
int odd_array(int *array,int len){
    for (int i=0;i<len;i+=2){
        cout<<*(array+i)<<" ";
    }
}
int main(){
    int number;
    cin>>number;
    int *array=new int[number];
    for(int i=0;i<number;i++){
        cin>>*(array+i);
    }
    odd_array(array,number);
    delete[]array;
    return 0;
}