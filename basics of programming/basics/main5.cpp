/*You have three types of movements: Euclidean, Manhattan, and Chebyshev. Write a program that calculates the distance between two points given the type of movement and the coordinates of the start and end points.
Input:
First, a letter representing the type of distance is provided, either E, M, or C. This is followed by two lines of coordinates representing the first and second points.
The range for x and y is:
−1000 ≤ x, y ≤ 1000
Output:
Based on the requested distance type, print the distance between the two points.
The result should be printed with exactly six decimal places.
Examples:
Sample Input 1:
C
-646 -445
-564 918
Sample Output 1:
1363.000000
Explanation:
The Chebyshev distance is calculated as:
|x2 - x1| = 82
|y2 - y1| = 1363
max(|y2 - y1|, |x2 - x1|) = 1363
Sample Input 2:
E
-910 -642
590 100
Sample Output 2:
1673.488572
Explanation:
The Euclidean distance is calculated as:
x2 - x1 = 1500
y2 - y1 = 742
√[(1500)^2 + (742)^2] = 1673.48857181
The answer is rounded to 6 decimal places: 1673.488572.
Sample Input 3:
M
10 -900
302 17
Sample Output 3:
1209.000000
Explanation:
The Manhattan distance is calculated as:
|x2 - x1| = 292
|y2 - y1| = 917
|y2 - y1| + |x2 - x1| = 1209*/
//answer:
#include <iostream>
#include<math.h>


using namespace std;
int main() {
    double x1,y1,x2,y2,answer,c1,c2,e1,e2;
    char typeyouwant;
    cin>>typeyouwant>>x1>>y1>>x2>>y2;

    if(typeyouwant == 'E'){
        e1 = x1-x2;
        e2 = y1-y2;
        answer = sqrt(pow(e1,2)+pow(e2,2));
        printf("%.6lf",answer);

    }
    if(typeyouwant == 'M'){
        answer= (abs(x1-x2))+(abs(y1-y2));
        printf("%.6lf",answer);
    }
    if(typeyouwant == 'C'){
        c1 = abs(x1-x2);
        c2 = abs(y1-y2);
        answer = max(c1,c2);
        printf("%.6lf" ,answer);
    }
    return 0;
}
