/*You are asked to write a function that, given the relative path of a .cpp file, counts the number of lines in the file that contain actual code (instructions).
For example, if the .cpp file has the following content:
#include <iostream>

using namespace std;

int main(void){

    int a;

    cin >> a;

    cout << a;

    // cout << 'hello';

}
The function should count 7 lines of code.
Input:
The input is a single line containing the relative path of a .cpp file.
Output:
You need to print the number of lines that contain instructions in the file.
Example Input:
main.cpp
Example Output:
7
Notes:
For simplicity, you can assume that only lines containing comments or empty lines do not count as instructions, and that a line contains either a comment or an instruction, but not both.*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

bool isCodeLine(const string &line) {
    string trimmed = line;
    trimmed.erase(trimmed.begin(), find_if(trimmed.begin(), trimmed.end(), [](int ch) {
        return !isspace(ch);
    }));
    trimmed.erase(find_if(trimmed.rbegin(), trimmed.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), trimmed.end());

    if (trimmed.empty() || trimmed[0] == '/' && trimmed[1] == '/')
        return false;

    return true;
}

void solve(const string &filePath) {
    ifstream file(filePath);
    string line;
    int count = 0;
    while (getline(file, line)) {
        if (isCodeLine(line)) {
            count++;
        }
    }

    file.close();
    cout << count << endl;
}

int main() {
    string filePath;
    cin >> filePath;
    solve(filePath);
    return 0;
}
