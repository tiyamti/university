/*You are given a list of words and need to format each word such that the first letter is uppercase and the remaining letters are lowercase. Print the formatted words in the same order as provided.
Input:
The first line contains the number n, which is the number of words.
The following n lines each contain a word to be formatted. Each word is less than 1000 characters long.
The number of words, n, will be between 1 and 300.
Output:
For each word, print the formatted word on a new line with the first letter in uppercase and the rest in lowercase.
Examples:
Input Example 1:
3
rEd riDing HOoD
DraCUla
Bad LiEutenAnt
Output Example 1:
Red Riding Hood
Dracula
Bad Lieutenant
Input Example 2:
2
21 jUMp Street
Mr. SMith GoEs To WashinGTon
Output Example 2:
21 Jump Street
Mr. Smith Goes To Washington*/
//answer:
#include <iostream>
#include <cstring>
using namespace std;
int main() {
    int tea;
    cin >> tea;
    char jomle[1000];
    cin.ignore();
    for(int p = 0; p <= tea; p++) {
        cin.getline(jomle, 1000);


        if (jomle[0] >= 97 &&  jomle[0] <= 122) {
            jomle[0] -= 32;

        }
        if (jomle[1] >= 65 &&  jomle[1] <= 90) {
            jomle[1] += 32;

        }

        for (int i = 1; jomle[i] != 0; i++) {
            if (jomle[i] == 32) {
                if (jomle[i+1] >= 97 && jomle[i + 2] <= 122) {
                    jomle[i+1] -= 32;
                }
            }
            else if (jomle[i+1] >= 65 && jomle[i+1] <= 90) {
                jomle[i + 1] += 32;
            }

        }
        cout<<jomle<<endl;
    }



    return 0;
}

