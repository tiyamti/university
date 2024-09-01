/*The program receives a dynamic array of integers and a number y. The program should determine if it is possible to select 4 distinct elements from the array such that their sum equals y. Note that no element should be repeated in the selected combination of 4 elements (i.e., each element can be used only once in the selected set). Additionally, the order of the numbers does not matter (i.e., the combination of 1, 5, 6, and 9 is the same as 1, 9, 6, and 5).
Input:
First, the size of the array is given.
Then, the array elements are given on the next line, followed by the integer y on the last line.
Output:
If it is possible to find a combination of 4 distinct elements whose sum equals y, output Yes.
Otherwise, output No.
Example:
Sample Input 1:
9
9 13 4 6 19 4 4 8 10
26
Sample Output 1:
Yes
Note: The sum of 4, 4, 8, and 10 equals 26.
Sample Input 2:
5
1 8 9 -10 4
11
Sample Output 2:
Yes
Note: The sum of 8, 9, -10, and 4 equals 11.
Sample Input 3:
6
-9 4 3 2 -10 -4
1
Sample Output 3:
No
Note: No combination of 4 elements from the array sums to 1.
Note: You must use a recursive function to solve this problem. Without using recursion, you might receive points in Quera, but the exercise will be manually graded later, and if recursion is not used, you might lose final points.*/
#include <iostream>
using namespace std;

bool findCombination(int* arr, int n, int start, int count, int sum, int target) {
    // Base case: if we selected 4 elements
    if (count == 4) {
        return (sum == target);
    }

    if (start >= n) {
        return false;
    }

    bool include = findCombination(arr, n, start + 1, count + 1, sum + arr[start], target);


    bool exclude = findCombination(arr, n, start + 1, count, sum, target);

    return include || exclude;
}

int main() {
    int n, y;

    cin >> n;

    int* arr = new int[n];


    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }


    cin >> y;


    if (findCombination(arr, n, 0, 0, 0, y)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }


    delete[] arr;

    return 0;
}
