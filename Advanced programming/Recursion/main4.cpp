/*Harry, while waiting at the airport for his delayed flight, creates a game to pass the time. In this game, Harry must generate all possible valid combinations of parentheses using n pairs of parentheses.
A valid parentheses string is one where every opening parenthesis ( has a corresponding closing parenthesis ) and they are in the correct order.
Examples of valid strings:
()()
(())()
Examples of invalid strings:
(()
())(
Input:
The input consists of a single integer n representing the number of pairs of parentheses.
1 ≤ n ≤ 100
Output:
The output should be all possible valid combinations of parentheses using n pairs, printed one per line. If no valid combinations can be made (for odd values of n), print INVALID.
Example:
Input 1:
4
Output 1:
(())
()()
Input 2:
3
Output 2:
INVALID*/
#include <iostream>
using namespace std;
void parantez(int nclose,int nopen,int naval,int n){
    static char prantezi[80];
    if(nclose==naval){
        cout<<prantezi<<endl;
        return;
    }
    if (nopen< naval) {
        prantezi[n]= '(';
        parantez(nclose, nopen + 1, naval,n+1);
    }
    if (nopen > nclose) {
        prantezi[n]=')';
        parantez(nclose+1, nopen , naval,n+1);
    }

}

int main() {
    int naval;
    cin>>naval;

    if(naval%2==0){
        parantez(0,0,naval/2,0);
    }
    else{
        cout<<"INVALID";
    }
    return 0;
}
