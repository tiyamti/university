/*You need to write a program that reads pairs of fractions, calculates their product, and outputs the result in the simplest form using operator overloading and classes. If the fraction is undefined (i.e., a division by zero occurs), print "INVALID." If the result is a whole number, print the number directly. If the result is a negative fraction, ensure that the negative sign is applied to the numerator.
Input:
The first line contains the number of test cases.
Each test case consists of two lines, where each line contains two integers representing the numerator and the denominator of a fraction. The length of each integer is at most 12 digits.
Output:
For each test case, print the product of the two fractions in the simplest form. If the result is an integer, print the integer. If the fraction is undefined (due to a denominator of zero), print "INVALID."
Example Input 1:
3
2 3
5 6
8 1
5 8
8 0
3 2
Example Output 1:
5 9
5
INVALID*/
#include <iostream>

using namespace std;
#define lli long long int
class Fractions{
public:
    lli numerator;
    lli denominator;
    int gcd(int a, int b)
    {
        if (b == 0) {
            return a;
        }
        else {
            return gcd(b, a % b);
        }
    }
    void operator/(Fractions &num_work);
};
void Fractions::operator/(Fractions &num_work){
    if (this->denominator==0 || num_work.denominator == 0){
        cout << "INVALID" << endl;
        return;
    }
    else if (this-numerator==0 || num_work.numerator == 0){
        cout << "0" << endl;
        return;
    }
    else{
        lli num1,den1,num2,den2;
        num1=((this->numerator) / gcd(this->numerator, this->denominator));
        den1=((this->denominator) / gcd(this->numerator, this->denominator));
        num2=((num_work.numerator) / gcd(num_work.numerator, num_work.denominator));
        den2=((num_work.denominator) / gcd(num_work.numerator, num_work.denominator));
        this->numerator=num1;
        this->denominator=den1;
        num_work.numerator=num2;
        num_work.denominator=den2;
        num1=((this->numerator) / gcd(this->numerator, num_work.denominator));
        den1=((this->denominator) / gcd(num_work.numerator, this->denominator));
        num2=((num_work.numerator) / gcd(num_work.numerator, this->denominator));
        den2=((num_work.denominator) / gcd(this->numerator, num_work.denominator));

        if(this->numerator<0 && this->denominator<0){
            this->numerator=this->numerator*(-1);
            this->denominator=this->denominator*(-1);
        }
        if (den2 < 0 || den1 < 0){
            this->numerator= -(num1 * num2) ;
            this->denominator= -(den2 * den1 );
        }
        else {
            this->numerator= num1 *num2 ;
            this->denominator=den2 * den1;
        }

        cout << this->numerator;
        if (this->denominator!=1)
            cout << " " << this->denominator;
        cout << endl;
    }
}
int main() {
    int number;
    cin >> number;
    Fractions num1{},num2{};
    for (int i=0;i<number;i++){
        cin >> num1.numerator >> num1.denominator;
        cin>>num2.numerator >>num2.denominator;
        num1/num2;
    }
    return 0;
}
