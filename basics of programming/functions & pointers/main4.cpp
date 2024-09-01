/*Important Note: You must use pointers to swap the elements of the array. A key point is that you cannot use a third variable to swap the two elements. You need to find a way to swap the values of two variables directly using pointers. For reference, here's how to use pointers:
int arr[] = {1, 2, 3, 4, 5, 6};
int *p1 = &arr[0];
int *p2 = &arr[1];
Input: The input consists of two lines:
The first line contains a natural number n (where n <= 1000).
The second line contains an array of length n.
Output: Output the reversed array in one line.
Example:
Sample Input 1:
5
1 2 3 4 5
Sample Output 1:
5 4 3 2 1
Sample Input 2:
10
7 7 7 9 8 5 1 1 1 1
Sample Output 2:
1 1 1 1 5 8 9 7 7 7*/
#include <iostream>
using namespace std;
void revers_array(int string_must_be_reversed[],int number){
    for (int i = 0; i < number/2; i++){
        char temp = string_must_be_reversed[i];
        string_must_be_reversed[i] = string_must_be_reversed[number-i-1];
        string_must_be_reversed[number-i-1] = temp;
    }
}
int main()
{
    int number ;
    cin >> number ;
    int array[number];
    for(int i=0 ; i<number ; i++)
        cin >> array[i];


    revers_array(array,number);
    for(int i=0 ; i<number ; i++)
        cout << array[i] <<" ";

    return 0;
}
