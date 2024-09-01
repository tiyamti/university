/*In this problem, you need to draw diamonds with the upper part consisting of a triangular number pattern and the lower part consisting of mirrored letters of the English alphabet. For better understanding, refer to the provided examples.
Input:
The input consists of a single line containing rows, which is the number of rows for the upper half of the diamond.
Constraints:
1 ≤ rows ≤ 20
Output:
Your program should print a diamond shape as follows:

Examples:

Sample Input 1:
6
Sample Output 1:

                    1
                1   2   1
            1   2   3   2   1
        1   2   3   4   3   2   1
    1   2   3   4   5   4   3   2   1
1   2   3   4   5   6   5   4   3   2   1
A   B   C   D   E   F   E   D   C   B   A
    A   B   C   D   E   D   C   B   A
        A   B   C   D   C   B   A
            A   B   C   B   A
                A   B   A
                    A
Sample Input 2:
10
Sample Output 2:

                                    1
                                1   2   1
                            1   2   3   2   1
                        1   2   3   4   3   2   1
                    1   2   3   4   5   4   3   2   1
                1   2   3   4   5   6   5   4   3   2   1
            1   2   3   4   5   6   7   6   5   4   3   2   1
        1   2   3   4   5   6   7   8   7   6   5   4   3   2   1
    1   2   3   4   5   6   7   8   9   8   7   6   5   4   3   2   1
1   2   3   4   5   6   7   8   9   10   9   8   7   6   5   4   3   2   1
A   B   C   D   E   F   G   H   I   J   I   H   G   F   E   D   C   B   A
    A   B   C   D   E   F   G   H   I   H   G   F   E   D   C   B   A
        A   B   C   D   E   F   G   H   G   F   E   D   C   B   A
            A   B   C   D   E   F   G   F   E   D   C   B   A
                A   B   C   D   E   F   E   D   C   B   A
                    A   B   C   D   E   D   C   B   A
                        A   B   C   D   C   B   A
                            A   B   C   B   A
                                A   B   A
                                    A
                                    */
//answer:
#include <iostream>

using namespace std;

int main()
{
    int adadvared , fasele  , a , b;
    cin >> adadvared ;
    fasele = adadvared ;
    a = adadvared ;
    b = adadvared ;
    for(int j =1 ; j <= adadvared ; j++){
        for(int i =1 ; i < fasele ; i++){
            cout << "    " ;
        }
        for(int k=1 ; k <= j ; k++){
            cout << k << "   "   ;
        }
        for(int c=(j-1) ; c>0 ; c--){
            cout << c << "   "   ;
        }
        fasele -= 1 ;
        cout << endl ;
    }
    for(int j = a ; j > 0 ; j--){
        for(int i = j ; i < b ; i++ ){
            cout << "    " ;
        }

        for(char k =65 ; k <= (j + 64) ; k++){
            cout << k << "   "   ;
        }
        for(char c =(j+64 -1) ; c>=65 ; c--){
            cout << c << "   "   ;
        }
        cout << endl ;
    }
    return 0;
}