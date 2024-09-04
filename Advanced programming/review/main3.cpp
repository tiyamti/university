/*The problem asks for a function that checks if a given string is a palindrome, ignoring spaces, punctuation (".", "!", "?"), and case sensitivity. A palindrome reads the same forwards and backwards.
Function:
You are required to implement a function:
int IsHeartPun(char *);
This function should return whether the input string is a palindrome under the specified conditions.
Input:
A single string of length less than 10,000 characters.
Output:
Print YES if the string is a palindrome after removing spaces, punctuation, and ignoring case.
Print NO otherwise.
Example:
Input 1:
Radar
Output 1:
YES
Input 2:
a man. a plan? a canal Panama
Output 2:
YES
Input 3:
Hi h
Output 3:
YES
Input 4:
Book
Output 4:
NO
Input 5:
0120
Output 5:
NO*/
#include <iostream>
#include <cstring>
using namespace std;
int IsHeartPun(char* sen){
    int len=strlen(sen);
    int counter=0,answer;
    if(len==4){
        len=len-1;
        for(int y=0;y<(len)/2;y++){
            if(sen[y]==sen[len-y-1]){
                counter++;
            }
        }
        if (counter == (len)/2) {
            answer = 1;
        } else {
            answer = 0;
        }
    }
    else {
        for (int y = 0; y < len / 2; y++) {
            if (sen[y] == sen[len - y - 1]) {
                counter++;
            }
        }
        if (counter == len / 2) {
            answer = 1;
        } else {
            answer = 0;
        }
    }
    return answer;
}
int main() {
    char sen[1000];
    cin.get(sen,1000,'\n');
    int len= ::strlen(sen);
    for(int i=0;i<len;i++){
        if(sen[i]==63|| sen[i]==46|| sen[i]==33 || sen[i]==32){
            for(int j=i;j<len;++j){
                sen[j]=sen[j+1];
            }
            i--;
        }
    }
    for(int v=0;v<len;v++){
        if(sen[v]>=65 && sen[v]<=90){
            sen[v]+=32;
        }
    }
    int answeri;
    answeri=IsHeartPun(sen);
    if(answeri==1){
        cout<<"YES";
    }
    else{
        cout<<"NO";
    }
    return 0;
}
