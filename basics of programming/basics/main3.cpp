/*Write a program that converts temperature from one unit (Celsius, Fahrenheit, or Kelvin) to another.
Input:
The input consists of two lines. The first line contains two characters from c (Celsius), f (Fahrenheit), and k (Kelvin). The first character indicates the original unit, and the second character indicates the target unit. The second line contains the temperature to be converted.
Output:
Your program should print the converted temperature with exactly two decimal places.
Examples:
Sample Input 1:
k c
123
Sample Output 1:
-150.15
Explanation:
123 K − 273.15 = -150.15 °C
Sample Input 2:
f k
456
Sample Output 2:
508.70
Explanation:
(456°F − 32) × 5/9 = 235.556°C
235.556°C + 273.15 = 508.706K
Sample Input 3:
c f
789
Sample Output 3:
1452.20
Explanation:
(789°C × 9/5) + 32 = 1452.2°
*/
//answer:
#include <iostream>
using namespace std;

int main() {
    char damadgree1 , damadgree2 ;
    double adaddgree;
    cin>>damadgree1>>damadgree2>>adaddgree;

    if(damadgree1 == 'k' && damadgree2 == 'c'){
        printf("%0.2f" , adaddgree - 273.15);
    }
    if (damadgree1 == 'c' && damadgree2 == 'k'){
        printf("%0.2f" ,adaddgree + 273.15);
    }
    if (damadgree1 == 'f' && damadgree2 == 'k'){
        printf("%0.2f" ,((adaddgree - 32)*5/9)+273.15);
    }
    if (damadgree1 == 'k' && damadgree2 == 'f'){
        printf("%0.2f" ,((adaddgree-273.15)*9/5)+32);
    }
    if (damadgree1 == 'c' && damadgree2 == 'f'){
        printf("%0.2f" ,((adaddgree * 9/5)+32));
    }
    if (damadgree1 == 'f' && damadgree2 == 'c'){
        printf("%0.2f" , (adaddgree - 32)*5/9);
    }
    return 0;
}
