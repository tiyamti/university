/*Input: The input consists of a single line containing a natural number n.
1 ≤ n ≤ 1000
Output: The output should be the sum of the digits of n, using a recursive function, until the result becomes a single-digit number.
Example:
Sample Input 1:
99
Sample Output 1:
9
Step 1:
9 + 9 = 18
Step 2:
1 + 8 = 9
Sample Input 2:
551
Sample Output 2:
2
Step 1:
5 + 5 + 1 = 11
Step 2:
1 + 1 = 2
Note: If you do not use a recursive function, you will not receive any points for this problem.*/
#include <iostream>
using namespace std;
int sumofdigit(int n)
{
    if (n == 0)
        return 0;
    return (n % 10 + sumofdigit(n / 10));
}

int main()
{
    int num ;
    cin>>num;
    int result;
    result= sumofdigit(num);
    while (!(result>=0 && result<=9)){
        result= sumofdigit(result);
    }
    cout<<result;
    return 0;
}
