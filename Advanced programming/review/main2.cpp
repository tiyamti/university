/*The problem asks for a program that checks if any of three given three-letter substrings are present in a given main string. If any of the substrings are found, the program should concatenate the found substrings in reverse order of appearance and print the result. If none of the substrings are found, the program should print "Not found."
Input:
The first line contains three three-letter substrings separated by spaces.
The second line contains an integer n (the length of the main string).
The third line contains the main string of length n.
Output:
If any of the three substrings are found in the main string, print them in reverse order of their appearance.
If none of the substrings are found, print "Not found."
Constraints:
n ≤ 100
Example:
Input 1:
sat noh ras
25
mlfdnohkdngfknksatldrasmd
Output 1:
rassatnoh
Explanation:
The substrings "noh," "sat," and "ras" are found in the main string.
The reverse order of their appearance is "ras," "sat," and "noh," so the output is "rassatnoh."
Input 2:
zir fan iii
18
dsfklsfgjfdsvsdsdf
Output 2:
Not found*/
#include <iostream>

bool strstr(const char *str, const char *str1);

using namespace std;
int main() {
    string str1;
    string str2;
    string str3;
    int n_number, co1 = 0, co2 = 0, co3 = 0, tem1=0, tem2=0, tem3=0;
    string massage;
    cin >> str1 >> str2 >> str3;
    cin >> n_number;
    cin >> massage;
    //--------------------

    for (int i = 0; i < n_number; ++i) {
        if (massage[i] == str1[0]) {
            co1++;
            tem1 = i;
            if (co1 == 1)
                break;
        }
    }

    if(massage.find(str1) != string::npos)
    {
        co1 = co1 + 2;
        tem1 = tem1 + 2;
    }
    //--------------------
    for (int j = 0; j < n_number; ++j) {
        if (massage[j] == str2[0]) {
            co2++;
            tem2 = j;
            if (co2 == 1)
                break;
        }
    }
    if(massage.find(str2) != string::npos)
    {
        co2 = co2 + 2;
        tem2 = tem2 + 2;
    }
    //--------------------
    for (int k = 0; k < n_number; ++k) {
        if (massage[k] == str3[0]) {
            co3++;
            tem3 = k;
            if (co3 == 1)
                break;
        }
    }
    if(massage.find(str3) != string::npos)
    {
        co3 = co3 + 2;
        tem3 = tem3 + 2;
    }
    //--------------------
    if (co1 == 3 && co2 == 3 && co3 == 3) {
        if (tem1 > tem2 && tem3 < tem1) {
            if (tem2 > tem3)
                cout << str1 + str2 + str3;
            else {
                cout << str1 + str3 + str2;
            }
        }

        if (tem2 > tem1 && tem3 < tem2) {
            if (tem1 > tem3) {
                cout << str2 + str1 + str3;
            } else {
                cout << str2 + str3 + str1;
            }
        }
        if (tem3 > tem2 && tem1 < tem3) {
            if (tem2 > tem1) {
                cout << str3 + str2 + str1;
            } else {
                cout << str3 + str1 + str2;
            }
        }
    }
        //-----------------------
    else if(co1==3&& co2 != 3 && co3 != 3){
        cout<<str1;
    }
    else if(co2==3&& co1 != 3 && co3 != 3){
        cout<<str2;
    }else if(co3==3 && co1 != 3 && co2 != 3){
        cout<<str3;
    }
        //-------------------------------
    else if(co1==3&& co2 == 3 && co3 != 3){
        if(tem1>tem2){
            cout<<str1+str2;
        }
        else{
            cout<<str2+str1;
        }
    }
    else if(co2==3&& co1 != 3 && co3 == 3){
        if(tem2>tem3){
            cout<<str2+str3;
        }
        else{
            cout<<str3+str2;
        }
    }
    else if(co3==3 && co1 == 3 && co2 != 3){
        if(tem1>tem3){
            cout<<str1+str3;
        }
        else{
            cout<<str3+str1;
        }
    }
//----------------------

    else if (co1 != 3 && co2 != 3 && co3 != 3) {
        cout << "Not found";
    }

    return 0;
}



