/*You need to create a class that represents complex numbers and performs the four basic arithmetic operations (addition, subtraction, multiplication, and division) using operator overloading. The input will contain multiple test cases, and for each test case, you will be given two complex numbers and a specified operation to perform on them.
Input:
The first line contains the number of test cases.
For each test case, two strings represent complex numbers (in the form a+ib or a-ib).
The next line contains one of the operations: div, mul, min, or plus.
Output:
For each test case, print the result of the operation on the given complex numbers. If division by zero occurs, print INVALID.
Example Input 1:
3
1+i2
3+i4
min
4-i6
-3+i1
mul
6.1-i4.2
0.1+i2
plus
Example Output 1:
-2-i2
-6+i22
6.2-i2.2
Example Input 2:
2
1+i6
0+i0
mul
5+i7
0+i0
div
Example Output 2:
0+i0
INVALID*/
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
class Complex_number{
private:
    double real;
    double imaginary;
public:
    Complex_number(){
        real=0;
        imaginary=0;
    }
    Complex_number(double x,double y){
        real=x;
        imaginary=y;
    }
    Complex_number(Complex_number &obj){
        real=obj.real;
        imaginary=obj.imaginary;
    }
    void print(void);

    Complex_number operator+(const Complex_number& complexNumber);
    Complex_number operator-(const Complex_number& complexNumber);
    Complex_number operator*(const Complex_number& complexNumber);
    Complex_number operator/(const Complex_number& complexNumber);

    double get_real(){
        return real;
    }
    double get_imaginary(){
        return imaginary;
    }
    double set_real(double re){
        real=re;
    }
    double set_imaginary(double im){
        imaginary=im;
    }
};
//-------------------------------------OPERATORS
Complex_number Complex_number::operator+(const Complex_number& complexNumber){
    Complex_number plus;
    plus.real=real+complexNumber.real;
    plus.imaginary=imaginary+complexNumber.imaginary;
    if (plus.imaginary > 0) {
        cout <<  plus.real << "+i" << plus.imaginary<< endl;
    } else if (plus.imaginary < 0) {
        cout <<  plus.real << "-i" << -plus.imaginary<< endl;
    }
    else if (plus.imaginary== 0) {
        cout <<  plus.real << "+i" << plus.imaginary<< endl;
    }
}
Complex_number Complex_number::operator-(const Complex_number& complexNumber){
    Complex_number sub;
    sub.real=real-complexNumber.real;
    sub.imaginary=imaginary-complexNumber.imaginary;
    if (sub.imaginary > 0) {
        cout << sub.real << "+i" << sub.imaginary<< endl;
    } else if (sub.imaginary < 0) {
        cout <<  sub.real << "-i" << -sub.imaginary<< endl;
    }
    else if (sub.imaginary== 0) {
        cout << sub.real << "+i" << sub.imaginary<< endl;
    }
}
Complex_number Complex_number::operator*(const Complex_number& complexNumber){
    Complex_number mult;
    mult.real =(( this->real)*(complexNumber.real ))-((this->imaginary)*(complexNumber.imaginary));
    mult.imaginary = ((this->real)*(complexNumber.imaginary ))+((complexNumber.real)*(this->imaginary));
    if (mult.imaginary > 0) {
        cout << mult.real << "+i" <<mult.imaginary<< endl;
    } else if (mult.imaginary < 0) {
        cout <<  mult.real << "-i" << -mult.imaginary<< endl;
    }
    else if (mult.imaginary== 0) {
        cout <<  mult.real << "+i" << mult.imaginary<< endl;
    }
}
Complex_number Complex_number::operator/(const Complex_number& complexNumber){
    Complex_number div;
    double Denominator;
    Denominator= ((complexNumber.real) * (complexNumber.real)) + ((complexNumber.imaginary) * (complexNumber.imaginary));
    if (Denominator == 0){
        cout << "INVALID" << endl;
    }
    else {
        div.real = ((real * complexNumber.real )+ (imaginary * complexNumber.imaginary))/(complexNumber.real * complexNumber.real + complexNumber.imaginary * complexNumber.imaginary);
        div.imaginary = ((imaginary * complexNumber.real)- ( real * complexNumber.imaginary)) /(complexNumber.real * complexNumber.real + complexNumber.imaginary * complexNumber.imaginary);
        return div;
    }
}
int main() {
    double orders_number;
    double real1, imag1, real2, imag2;
    string order, num1,num2;
    Complex_number answer;
    cin >> orders_number;
    int counter = 0;
    while (counter != orders_number) {
        cin >> num1;
        for (int i = 0; i < num1.size(); i++) {
            if (num1[i] == 'i') {
                if(i>=2){
                    if (num1[0] == '-') {
                        string convert1(num1, 1, i - 1);
                        real1 = stod(convert1) ;
                        real1=real1*(-1);
                    }
                    else {
                        string convert1(num1, 0, i - 1);
                        real1 = stod(convert1);
                    }
                }
                string convert2(num1, i + 1, (num1.size() - 1));
                if (num1[i - 1] == '-'){
                    imag1 = stod(convert2) ;
                    imag1=(imag1*(-1));
                }
                else {
                    imag1 = stod(convert2);
                }
                break;
            }
        }

//-------------------------------------------------
        cin >> num2;
        for (int i = 0; i < num2.size(); i++) {
            if (num2[i] == 'i') {
                if(i>=2){
                    if (num2[0] == '-') {
                        string convert1(num2, 1, i - 1);
                        real2 = stod(convert1) ;
                        real2=real2*(-1);
                    }
                    else {
                        string convert1(num2, 0, i - 1);
                        real2 = stod(convert1);
                    }
                }
                string convert2(num2, i + 1, (num2.size() - 1));
                if (num2[i - 1] == '-'){
                    imag2 = stod(convert2) ;
                    imag2=(imag2*(-1));
                }
                else {
                    imag2 = stod(convert2);
                }
                break;
            }
        }

        Complex_number obj1(real1, imag1);
        Complex_number obj2(real2, imag2);
        cin >> order;
        if (order == "plus") {
            answer = obj1 + obj2;

        }
        if (order == "min") {
            answer = obj1 - obj2;

        }
        if (order == "mul") {
            answer = obj1 * obj2;

        }
        if (order == "div") {
            answer = obj1 / obj2;
            if (answer.get_imaginary() > 0) {
                cout << answer.get_real() << "+i" << answer.get_imaginary() << endl;
            } else if (answer.get_imaginary() < 0) {
                cout << answer.get_real() << "-i" << -answer.get_imaginary() << endl;
            }
            else if (answer.get_imaginary()==0 &&answer.get_real() !=0 ) {
                cout <<  answer.get_real() << "+i" << answer.get_imaginary() << endl;
            }
        }
        counter++;
    }

    return 0;
}
