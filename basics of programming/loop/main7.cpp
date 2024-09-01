/*You are given two numbers in the input: a on the first line and b on the second line. The number a represents the perimeter of the outer square, and the number b represents the perimeter of the inner square.
Input:
The first line contains the number a, representing the perimeter of the outer square.
The second line contains the number b, representing the perimeter of the inner square.
If the side length of the inner square is greater than or equal to the side length of the outer square, print Wrong order!. If the difference between a and b is not even, print Wrong difference!. Otherwise, draw the corresponding hollow square.
Output:
Draw the hollow square as described.
Note that there should be a space between the stars (*) in the output, not an empty character.
Examples:
Sample Input 1:
7
3
Sample Output 1:
* * * * * * *
* * * * * * *
* *       * *
* *       * *
* *       * *
* * * * * * *
* * * * * * *
Sample Input 2:
16
24
Sample Output 2:
Wrong order!
Sample Input 3:
12
6
Sample Output 3:
* * * * * * * * * * * *
* * * * * * * * * * * *
* * *             * * *
* * *             * * *
* * *             * * *
* * * * * * * * * * * *
* * * * * * * * * * * *
 */
//answer:
#include <iostream>
using namespace std;

int main() {
    int a, b;

    cin >> a >> b;

    int outerSide = a / 4;
    int innerSide = b / 4;

    if (innerSide >= outerSide) {
        cout << "Wrong order!" << endl;
        return 0;
    }

    if ((a - b) % 2 != 0) {
        cout << "Wrong difference!" << endl;
        return 0;
    }

    for (int i = 0; i < outerSide; ++i) {
        for (int j = 0; j < outerSide; ++j) {
            if (i == 0 || i == outerSide - 1 || j == 0 || j == outerSide - 1) {
                cout << "* ";
            } else if (i >= outerSide - innerSide && i < outerSide && j >= outerSide - innerSide && j < outerSide) {
                if (i == outerSide - innerSide || i == outerSide - 1 || j == outerSide - innerSide || j == outerSide - 1) {
                    cout << "* ";
                } else {
                    cout << "  ";
                }
            } else {
                cout << "  ";
            }
        }
        cout << endl;
    }

    return 0;
}
