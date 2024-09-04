/*You are given a string s consisting of digits, and your task is to convert this string into all possible valid IPv4 addresses by inserting dots (.) at appropriate positions. An IPv4 address is in the format X.X.X.X, where each X is an octet, a valid integer between 0 and 255. Additionally, an octet cannot have leading zeros unless it is exactly 0.
Input
A single string s of length between 4 and 12, inclusive, consisting of digits only.
Output
Print all possible valid IPv4 addresses, each on a new line. If no valid address can be formed, print nothing.
Constraints
The length of s is between 4 and 12 (inclusive).
Each octet in the IP address must be a valid integer between 0 and 255.
Octets cannot have leading zeros unless the octet is exactly 0.
Example
Input 1:
7151
Output 1:
7.1.5.1
Input 2:
55011859
Output 2:
5.50.118.59
55.0.118.59
Notes:
IPs like 55.01.18.59 are invalid due to leading zeros, so they should not be considered valid outputs.*/
#include <iostream>
using namespace std;
int main() {
    string array_proxy;
    cin>>array_proxy;
    int l = array_proxy.length();
    string check = array_proxy;
    string ans;
    for (int i = 1; i < l - 2; i++) {
        for (int j = i + 1; j < l - 1; j++) {
            for (int k = j + 1; k < l; k++) {
                check = check.substr(0, k) + "."+ check.substr(k);
                check= check.substr(0, j) + "."+ check.substr(j);
                check= check.substr(0, i) + "."+ check.substr(i);
                check=check+".";
                int i = 0;
                int j = 0;
                int x=0;
                while(i < check.size()){
                    string s = "";
                    while(check[j] != '.'){
                        s = s + check[j];
                        j++;
                    }

                    int num = stoi(s);
                    if(s.size() > 3 || num < 0 || num > 255){
                        x--;
                    }
                    if(s.size() == 3 || num < 0 || num > 255){
                        x--;
                    }
                    if(s.size() > 1 && num == 0) {
                        x--;
                    }

                    if(s.size() > 1 && num != 0 && s[0] == '0') {
                        x--;
                    }
                    else{
                        x++;
                    }
                    i = j + 1;
                    j = i;

                    if(s.size() == 1 && num == 0) {
                        x++;
                        x--;
                    }
                }
                if(l==4){
                    for(int q=0;q<l+3;q++) {
                        cout << check[q];
                    }
                    cout<<endl;
                }
                if(x>=3 && l!=4){
                    for(int q=0;q<l+3;q++) {
                        cout << check[q];
                    }
                    cout<<endl;
                }
                check = array_proxy;
            }
        }
    }

    return 0;
}
