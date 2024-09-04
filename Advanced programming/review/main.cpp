/*The problem asks for a program that processes multiple test cases, where each test case consists of a sentence. The task is to count the uppercase and lowercase letters in the sentence. If there are more uppercase letters than lowercase ones, the sentence should be converted to all uppercase; otherwise, it should be converted to all lowercase.
Input
First, an integer t is given, representing the number of test cases.
Then, for each test case, a sentence is provided.
Output
For each test case, print the sentence in uppercase if it contains more uppercase letters than lowercase ones. Otherwise, print the sentence in lowercase.
Constraints
1 ≤ t ≤ 10
Example
Input
5
Sos KHErsi!
Hot dog paniri
ALAF aBi
chips?!
ALafe Khers
Output
sos khersi!
hot dog paniri
ALAF ABI
chips?!
alafe khers
*/
#include <iostream>
#include <cstring>
using namespace std;
//-------------------------------------------------------------------
int main()
{
    int n_number;
    int countCB;
    int countCS;
    char name_of_food[1000];
//-------------------------------------------------------------------
    cin>>n_number;
//-------------------------------------------------------------------
    cin.ignore();
    for(int w=0;w<=n_number;w++){
        cin.getline(name_of_food, 1000);
        countCS=0;
        countCB=0;
        int len=strlen(name_of_food);
        for (int u = 0; u <= len; u++) {
            if (name_of_food[u] >= 65 && name_of_food[u] <= 90) {
                countCB++;
            }
            if (name_of_food[u] >= 97 && name_of_food[u] <= 122) {
                countCS++;
            }
        }
        for(int j=0;j<=len;j++) {
            if (countCB > countCS) {
                if (name_of_food[j] >= 97 && name_of_food[j] <= 122) {
                    name_of_food[j] =name_of_food[j]- 32;
                }
            }
            if (countCS > countCB) {
                if (name_of_food[j] >= 65 && name_of_food[j] <= 90) {
                    name_of_food[j] =name_of_food[j]+ 32;
                }
            }
        }
        cout<<name_of_food<<endl;
    }
//-------------------------------------------------------------------

    return 0;
}
