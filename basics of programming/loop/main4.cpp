/*The input consists of a single line containing an angle x in radians.
Input:
The input contains only one line with the angle x in radians.
Constraints:
−10 ≤ x ≤ 10
Output:
Your program should compute the values of sin(x), cos(x), and tan(x) using the Taylor series expansion up to 20 terms and print each value with 5 decimal places.
Examples:
Sample Input 1:
7
Sample Output 1:
0.65699
0.75390
0.87145
Sample Input 2:
-4
Sample Output 2:
0.75680
-0.65364
-1.15782*/
//answer:
#include <iostream>
#include <cmath>
using namespace std;
double factorial(int);
double taylorSine(double, double);
double taylorCosine(double , double );
int main() {
    double rad ;
    cin >> rad ;
    printf("%.5lf",taylorSine(rad,19));
    cout<<"\n";
    printf("%.5lf", taylorCosine(rad,19));
    cout <<"\n";
    printf("%.5lf",taylorSine(rad,19)/taylorCosine(rad,19));
    return 0 ;

}


double factorial(int num){

    double fact = 1;

    for(int i = 1; i <= num; i++){

        fact = fact * i;

    }

    return fact;

}



double taylorSine(double num, double precision ){

    double value = 0;

    for(int n = 0; n < precision; n++){

        value += pow(-1.0, n) * pow(num, 2*n+1) / factorial(2*n + 1);

    }

    return value;
}


double taylorCosine(double num, double precision ){

    double valuee = 0;

    for(int n = 0; n < precision; n++){

        valuee += pow(-1.0, n) * pow(num, 2*n)/factorial(2*n);

    }

    return valuee;

}