/*Input: In the input, three numbers are entered. The first number is the one we consider in base 10, and the second number is between 11 and 16.
Output: Your output should be in five lines:
Convert the first number to the base given by the second number in the input and print it.
Then check if there are any letters in the newly obtained number; if letters are found, print them in sequence (if there are no letters, print "NONE").
Remove the letters from the obtained number and print the new number.
Print the sum of the digits of the new number.
Raise the result to the power of the third number entered in the input and print the result.
Example:
Sample Input 1:
99943
11
2
Sample Output 1:
690A8
A
6908
23
529
Explanation of Sample 1:
In the first line, the number 99943 is converted to base 11, and the result is printed.
In the second line, the letters present in the converted number are printed.
In the third line, the letters are removed from the converted number, and the remaining digits are printed.
In the fourth line, the sum of these digits is printed (6 + 9 + 0 + 8 = 23).
In the fifth line, the sum 23 is raised to the power of the third input number 2, and the result is printed.
Sample Input 2:
9573
12
7
Sample Output 2:
5659
NONE
5659
25
6103515625
Explanation of Sample 2:
In the first line, the number 9573 is converted to base 12, and the result is printed.
In the second line, the letters present in the converted number are printed. Since there are no letters in 5659, "NONE" is printed instead.
In the third line, since there were no letters, the number remains 5659, and it is printed.
In the fourth line, the sum of the digits is printed (5 + 6 + 5 + 9 = 25).
In the fifth line, the sum 25 is raised to the power of the third input number 7, and the result is printed.
Sample Input 3:
895
16
3
Sample Output 3:
37F
F
37
10
1000
Explanation of Sample 3:
In the first line, the number 895 is converted to base 16, and the result is printed.
In the second line, the letter F is printed.
In the third line, the letter is removed, and the remaining number 37 is printed.
In the fourth line, the sum of the digits is printed (3 + 7 = 10).
In the fifth line, the sum 10 is raised to the power of the third input number 3, and the result is printed.*/
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;
int array_to_num(int arr[],int n){
    char str[6][3];
    int i;
    char number[13] = {'\n'};

    for(i=0;i<n;i++) sprintf(str[i],"%d",arr[i]);
    for(i=0;i<n;i++)strcat(number,str[i]);

    i = atoi(number);
    return i;
}
char ele_base_11(long long number_convert_to_11base){
    long long result;
    if (number_convert_to_11base >= 0 && number_convert_to_11base <= 9){
        result = (char) (number_convert_to_11base + '0');
    }
    else{
        result = (char) (number_convert_to_11base - 10 + 'A');
    }
    return result;
}
void revers_array(char *string_must_be_reversed){
    int len= strlen(string_must_be_reversed);
    for (int i = 0; i < len/2; i++){
        char temp = string_must_be_reversed[i];
        string_must_be_reversed[i] = string_must_be_reversed[len-i-1];
        string_must_be_reversed[len-i-1] = temp;
    }
}
char* base_conversion(char converted_number[], long long base, long long inputnumber){
    int index =0;
    while (inputnumber > 0){
        converted_number[index++] =ele_base_11(inputnumber % base);
        inputnumber /= base;
    }
    converted_number[index] = '\0';
    revers_array(converted_number);
    return converted_number;
}

void check_alphabet(char check_number_with_alphabet[]){
    int len= strlen(check_number_with_alphabet);

    int q=0;
    for(int i=0;i<len;i++) {
        if (check_number_with_alphabet[i]>64&&check_number_with_alphabet[i]<71) {
            cout<<check_number_with_alphabet[i];
            q++;
        }
    }
    if(q==0){
        cout<<"NONE";
    }

}
char* remove_alphabet(char numbers_with_alphabet[]){
    int j=0;
    for (int i = 0; numbers_with_alphabet[i]; i++){
        if (numbers_with_alphabet[i] >= '0' && numbers_with_alphabet[i] <= '9'){
            numbers_with_alphabet[j] = numbers_with_alphabet[i];
            j++;
        }
    }
    numbers_with_alphabet[j] = '\0';
    return numbers_with_alphabet;
}
int sum_of_digit(long long n){
    if (n == 0)
        return 0;
    return (n % 10 + sum_of_digit(n / 10));
}
long long power_function(long long number_power, long long number_power_function){
    unsigned long long int result;
    result=number_power_function;
    for(int i=1;i<number_power;++i)
        result=result*number_power_function;
    return result;
}
int main(){
    long long number_input;
    cin>>number_input;
    long long  number_base;
    cin>>number_base;
    long number_pow;
    cin>>number_pow;
    char* answer_base;
    char* answer_remove_alphabet;
    basic_string<char> answer_alphabet_check;
    long long answer_sum_of_digit;
    unsigned long long int answer_pow;
    char res[100];
    answer_base= base_conversion(res, number_base, number_input);
    cout<<answer_base<<endl;
    check_alphabet(answer_base);
    cout<<endl;
    answer_remove_alphabet= remove_alphabet(answer_base);
    cout<<answer_remove_alphabet<<endl;
    int len= strlen(answer_remove_alphabet);
    long long int_answer_remove_alphabet;
    int int_char_of_answer_remove[100];
    for(int h=0;h<len;h++){
        int_char_of_answer_remove[h]=int(answer_remove_alphabet[h])-48 ;
    }
    int_answer_remove_alphabet = array_to_num(int_char_of_answer_remove,len);
    answer_sum_of_digit= sum_of_digit(int_answer_remove_alphabet);
    cout<<answer_sum_of_digit<<endl;
    answer_pow=0;
    answer_pow= power_function(number_pow,answer_sum_of_digit);
    cout<<answer_pow<<endl;
    return 0;
}
