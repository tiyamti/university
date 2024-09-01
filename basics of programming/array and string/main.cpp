/*You are given a hexadecimal color code in the input. Your task is to determine whether this color code is valid or not.
Input: The input consists of a single line containing the color code s.
Output: Your program should determine the validity of the color code and output:
If the color code is valid: '<CODE>' is valid.
If the color code is invalid: '<CODE>' isn't valid.
Conditions for a valid hexadecimal color code:
It must start with a #.
It must be followed by exactly 6 hexadecimal characters (0-9, A-F, a-f).
Examples:
Input Example 1:
#CD5C5C
Output Example 1:
'#CD5C5C' is valid.
Input Example 2:
#eaecee
Output Example 2:
'#eaecee' is valid.
Input Example 3:
ku)@
Output Example 3:
'ku)@' isn't valid.*/
//answer:
#include <iostream>
#include <cstring>
using namespace std;
int main(){
    char color[20];
    cin>>color;
    if (strlen(color)==7 && color[0]=='#'){
        if(strchr(color,0)||strchr(color,1)||strchr(color,2)||strchr(color,3)||strchr(color,4)||strchr(color,5)||strchr(color,6)||strchr(color,7)||strchr(color,8)||strchr(color,9||strchr(color,'A')||strchr(color,'B')||strchr(color,'C')||strchr(color,'D')||strchr(color,'E')||strchr(color,'F')||strchr(color,'a')||strchr(color,'b')||strchr(color,'c')||strchr(color,'d')||strchr(color,'e')||strchr(color,'f'))){

            cout << "'" << color << "'" << " " << "is valid.";

        }

    }
    else{
        cout<<"'"<<color<<"'"<<" "<<"isn't valid.";
    }
    return 0;
}