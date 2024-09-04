/*You are given an n x n matrix consisting of 0s and 1s. Your task is to generate a new matrix where each element represents the count of 1s adjacent to that position in the input matrix. The adjacent cells include the ones directly above, below, to the left, right, and diagonally around the current cell (8 possible neighbors).
Input
The first line contains an integer n, where
1≤n≤10, the size of the matrix.
The next n lines each contain n integers (either 0 or 1), representing the matrix.
Output
Output an n x n matrix where each element is replaced with the number of adjacent cells containing 1s from the original matrix.
Example
Input:
4
1 0 1 1
1 0 0 1
0 0 1 1
1 1 0 1
Output:
1 3 2 2
1 4 5 4
3 4 4 3
1 2 4 2*/
#include <iostream>
using namespace std;
int main() {
    int n, co=0;
    cin>>n;
    int matrix[n][n];
    for(int a=0;a<n;++a){
        for(int b=0;b<n;++b){
            cin>>matrix[a][b];
        }
    }
    //---------------------
    for(int i=0;i<n;i++) {
        for (int j = 0; j < n; j++) {
            if ((j + 1) < n  ) {
                if (matrix[i][j + 1] == 1){
                    co++;
                }
            }
            if ((j - 1) >= 0) {
                if (matrix[i][j - 1] == 1) {
                    co++;
                }
            }
            if ((i + 1) < n) {
                if (matrix[i + 1][j] == 1){
                    co++;
                }
                if ((j + 1) < n) {
                    if (matrix[i + 1][j + 1] == 1)
                        co++;
                }
                if ((j - 1) >= 0) {
                    if (matrix[i + 1][j - 1] == 1) {
                        co++;
                    }
                }
            }
            if ((i - 1) >= 0) {
                if (matrix[i - 1][j] == 1) {
                    co++;
                }
                if (j + 1 < n) {
                    if (matrix[i - 1][j + 1] == 1) {
                        co++;
                    }
                }
                if ((j - 1) >= 0) {
                    if (matrix[i - 1][j - 1] == 1) {
                        co++;
                    }
                }
            }
            cout << co ;
            if (j<n)
                cout << " ";
            co=0;
        }
        if (i<n)
            cout << endl;
    }
    return 0;
}
