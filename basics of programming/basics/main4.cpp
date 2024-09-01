/*Write a program that takes the coefficients of a quadratic equation and prints its solutions.
Equation:
The equation is in the form of:
a*x^2 + b*x + c = 0
Input:
The input consists of a single line containing three numbers a, b, and c separated by spaces.
The range for these numbers is:
−200 ≤ a, b, c ≤ 200
Output:
Print the solutions of the equation on separate lines, formatted to 6 decimal places.
If the equation has a double root (repeated solution), print the root only once.
If the equation does not have real solutions, print "Error!".
Special cases:
If a = 0, the equation is linear.
If both a = 0 and b = 0, the equation is invalid, and you should print "Error!".
Examples:
Sample Input 1:
1 -2 1
Sample Output 1:
1.000000
Explanation:
The equation is of the form:
f(x) = (x - 1)^2 -> x = 1
Sample Input 2:
1 -5 6
Sample Output 2:
3.000000
2.000000
Explanation:
The equation is of the form:
f(x) = (x - 3)(x - 2) -> x = 3, x = 2
Sample Input 3:
1 1 1
Sample Output 3:
Error!
Explanation:
In this case, the discriminant is negative, so there are no real solutions.
Sample Input 4:
0 0 101
Sample Output 4:
Error!
Explanation:
The equation 0 = 101 is invalid.*/
//answer:
#include<iostream>
#include<math.h>

int main() {
    double a, b, c, delta, x1, x2;
    scanf("%lf" "%lf" "%lf", &a, &b, &c);
    delta = pow(b, 2) - 4 * a * c;

    if (delta < 0) {
        printf("Error!");
    }
    if (delta == 0) {
        if (a == 0 && b == 0) {
            printf("Error!");
        } else {
            x1 = -b / (2 * a);
            printf("%f", x1);
        }


    }
    if (delta > 0) {
        if (a == 0 && b != 0) {
            x1 = -c / b;
            printf("%lf", x1);
        } else {
            x1 = (-b + sqrt(delta)) / (2 * a);
            x2 = (-b - sqrt(delta)) / (2 * a);
            printf("%f" "%s" "%f", x1, "\n", x2);
        }
    }


    return 0;
}
