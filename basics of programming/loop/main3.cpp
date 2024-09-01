/*In this problem, you need to print a sequence based on a number n that you provide as input. The sequence should be printed as follows: first 1, then 1 + 2, then 1 + 2 + 3, and finally 1 + 2 + 3 + ... + n.
Input:
Read the number n and print the sequence and the total sum of the series.
Constraints:
1 ≤ n ≤ 1000
Output:
This program should output n + 1 lines:
The first n lines should show the sums of each segment of the sequence.
The final line should show the total sum of all the series.
Examples:
Sample Input 1:
5
Sample Output 1:
1 = 1
1+2 = 3
1+2+3 = 6
1+2+3+4 = 10
1+2+3+4+5 = 15
Total sum of series is: 35
Sample Input 2:
1
Sample Output 2:
1 = 1
Total sum of series is: 1
Explanation of the sample:
Inside a loop that iterates from i = 1 to n, define a variable each_sum and set it to i. Use another inner loop where j goes from 1 to i, adding j to each_sum and printing j along with the + character. After the inner loop, print each_sum and i, and add each_sum to a variable sum. Finally, print the total sum of the series.*/
//answer:
#include<iostream>
#include <cmath>
using namespace std;
int main() {
    int i,dori,sumdo;
    cin>>dori;
    int sumdoit=0;
    for(int i=1;i<=dori;i++){
        sumdoit=sumdoit+i;
        for(int j=1;j<=i;j++){
            if(j==i) cout<<j;
            else cout<<j<<"+";
        }
        sumdo=sumdo+sumdoit;
        cout<<" = "<<sumdoit<<endl;
    }
    cout<<"Total sum of series is: "<<sumdo<<endl;
    return 0;
}
