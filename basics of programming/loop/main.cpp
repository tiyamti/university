/*Write a program that receives an integer n and then reads n floating-point numbers. The program should print the maximum, minimum, and average of the numbers with a precision of three decimal places.
Input:
First, input an integer n.
Then, read n floating-point numbers.
Output:
Print the maximum, minimum, and average of the input numbers with exactly three decimal places in the following format:
Max: x.xxx
Min: x.xxx
Avg: x.xxx
Example 1:
Input:
1
4.65
Output:
Max: 4.650
Min: 4.650
Avg: 4.650
Example 2:
Input:
4
1
0.5555
3.4445
2
Output:
Max: 3.444
Min: 0.555
Avg: 1.750
Explanation of the example:
After receiving the number n, the first input number should be set as both the initial min and max. Then, use a loop to read the remaining numbers and:
Compare each number with the current max and update max if necessary.
Compare each number with the current min and update min if necessary.
Add the input number to a variable sum.
Increment a counter variable, initialized to 0, after each number is read. If the counter reaches n, break out of the loop and calculate the average.*/
//answer:

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
