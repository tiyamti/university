/*Write a program that reads N floating-point numbers as input and prints the maximum, minimum, and average of the received numbers, rounded to three decimal places.
Input: On the first line, you are given the number N, and then N decimal numbers. 1 ≤ N ≤ 10^6
Output: In a single line, print the maximum, minimum, and average of the numbers with a precision of three decimal places.
Example:
Sample Input 1:
1
4.65
Sample Output 1:
Max: 4.650
Min: 4.650
Avg: 4.650
Sample Input 2:
4
1
0.5555
3.4445
2
Sample Output 2:
Max: 3.444
Min: 0.555
Avg: 1.750*/

#include <iostream>
using namespace std;
int main() {
    double min,max=0,adadvarede2,sumdo,avrage;
    int adadvarede,i;

    cin>>adadvarede;
    min=99999999999;
    sumdo=0;
    for(i=0;i<adadvarede;++i)
    {
        cin>>adadvarede2;
        if(adadvarede2>=max){
            max =adadvarede2;
        }
        if(adadvarede2<=min) {
            min = adadvarede2;
        }
        sumdo=sumdo+adadvarede2;
    }
    avrage=sumdo/adadvarede;
    cout<<"Max: ";
    printf("%.3lf",max);
    cout<<"\n";
    cout<<"Min: ";
    printf("%.3lf",min);
    cout<<"\n";
    cout<<"Avg: ";
    printf("%.3lf",avrage);
    return 0;
}
