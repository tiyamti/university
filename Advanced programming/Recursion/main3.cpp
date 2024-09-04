/*Harry's father has allowed him to go to Hogwarts, and now Harry wants to buy exactly 4 suitcases. The weight of his luggage must match the total weight of the 4 suitcases he selects from a shop. Given an array of available suitcase weights, you need to check if it's possible to select exactly 4 suitcases such that their total weight equals the total weight of Harry's luggage. Write a recursive function to solve this problem.
Input:
The first line contains an integer n, representing the number of available suitcases.
The second line contains n integers, representing the weights of the available suitcases.
The third line contains an integer, the total weight of Harry's luggage.
Constraints:
|Weight of each suitcase|, |Total weight of luggage| ≤ 100,000
Number of available suitcases n ≤ 100,000
Output:
Print Yes if it is possible to select 4 suitcases such that their total weight equals the total weight of Harry's luggage. Otherwise, print No.
Example:
Input 1:
8
4 7 4 0 9 5 1 3
22
Output 1:
Yes
(Explanation: Suitcases with weights 7 + 9 + 5 + 1 = 22)
Input 2:
5
15 -8 4 7 -2
19
Output 2:
No*/
#include <iostream>
using namespace std;
int four(int A[], int n, int X,int i)
{
    string ansi;
    int co=2;
    for (int j = i + 1; j < n - 2; j++)
    {
        for (int k = j + 1; k < n - 1; k++)
        {
            for (int l = k + 1; l < n; l++)
                if (A[i] + A[j] + A[k] + A[l] == X)
                    co=1;
        }
    }
    if(co==1){
        cout<<"Yes";
        return 0;
    }
    else{
        if(i==4){
            cout<<"No";
            return 0;
        }
        four(A, n, X,i+1);
    }
}

int main()
{
    int n;
    cin>>n;
    int array[n];
    int harry;
    int i=0;
    for(int y=0;y<n;y++){
        cin>>array[y];
    }
    cin>>harry;
    four(array, n, harry,i);
    return 0;
}