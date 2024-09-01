/*
---

**Mini Project Description:**
In this mini project, you are asked to implement a simple text manipulation machine with a set of basic capabilities. The program begins by receiving an initial string (up to 1000 characters in length) from the input. After this, until the exit command is received, the user can request various operations on the string.

**Input:**
First, the length of the string is given, followed by the string itself. Then, operations will be received. The operations are defined as follows:

**Operation Descriptions and Commands:**

- **SHR N**: Rotates all characters of the string to the right by `N` positions.
- **SHL N**: Rotates all characters of the string to the left by `N` positions.
- **REM N**: Removes `N` characters from the end of the string. If the length of the string is less than `N`, the resulting string will be empty.
- **REV**: Reverses the string.
- **PUT I C**: Replaces the character at position `I` in the string with character `C`. Note that positions start from one, and `I` will always be less than or equal to the length of the string.
- **PRI**: Prints the current string. If the string is empty, print "EMPTY".
- **ReverseByIndex N M**: Reverses the characters between the two given indices `N` and `M`.
- **Delete STR**: Removes all occurrences of the substring `STR` from the main string.
- **Discount N STR[0] ... STR[n-1]**: Checks which of the provided discount codes (substrings) are valid. A discount code is valid if its unique set of characters (alphabet) matches the alphabet of the main string.
- **NewString**: Converts the string to ASCII values, excluding numbers. Then, pairs the ASCII values to form characters to create a new string. If an ASCII value is less than 32, add 32 to it.
- **EXI**: Ends the program.

**Output:**
Your program will only print output for the print operation (`PRI`). For other commands, just perform the specified operation on the string.

**Command Descriptions:**

- **SHR N**: Rotates all characters of the string to the right by `N` positions. For example, if the initial string is "abcde":
  - Input: `SHR 3`
  - Output: `cdeab`

- **SHL N**: Rotates all characters of the string to the left by `N` positions. For example, if the initial string is "abcde":
  - Input: `SHL 2`
  - Output: `cdeab`

- **REM N**: Removes `N` characters from the end of the string. If the string length is less than `N`, the resulting string will be empty. For example, if the initial string is "abcde":
  - Input: `REM 2`
  - Output: `abc`

- **REV**: Reverses the string. For example, if the initial string is "abcde":
  - Input: `REV`
  - Output: `edcba`

- **PUT I C**: Replaces the character at position `I` with character `C`. For example, if the initial string is "abcde":
  - Input: `PUT 2 z`
  - Output: `azcde`

- **PRI**: Prints the current string. For example, if the string is "abcde":
  - Input: `PRI`
  - Output: `abcde`
  - If the string is empty, print "EMPTY".

- **ReverseByIndex N M**: Reverses the characters between the two indices `N` and `M`. For example, if the initial string is "abcdefgh":
  - Input: `ReverseByIndex 3 6`
  - Output: `abcgfedh`

- **Delete STR**: Removes all occurrences of the substring `STR` from the main string. For example, if the initial string is "abcdebcdfbcd":
  - Input: `Delete bcd`
  - Output: `aef`

- **Discount**: Identifies valid discount codes. A discount code is valid if its unique set of characters matches the set of the main string. For example, if the main string is "quera102":
  - Input: `Discount 3 quEra0012 qu0erraa12 sN0Ap12`
  - Output: `quera102qu0erraa12`

- **NewString**: Converts the string to ASCII values, excluding numbers. Then, pairs the ASCII values to form characters for a new string. If an ASCII value is less than 32, add 32. For example, if the string is "ab2cd":
  - Input: `NewString`
  - Output: `ab=[`

**Example:**

**Sample Input 1:**
```
14
initial string
PRI
SHR 3
PRI
PUT 3 o
REV
PRI
REM 2
PRI
EXI
```

**Sample Output 1:**
```
initial string
inginitial str
rts laitinioni
rts laitinio
*/
#include <iostream>
#include <string>

using namespace std;

string rotateRight(const string& str, int n) {
    int len = str.length();
    n = n % len;
    if (n == 0) return str;

    return str.substr(len - n) + str.substr(0, len - n);
}


string rotateLeft(const string& str, int n) {
    int len = str.length();
    n = n % len;
    if (n == 0) return str;

    return str.substr(n) + str.substr(0, n);
}

string reverseString(const string& str) {
    string reversed;
    int len = str.length();
    for (int i = len - 1; i >= 0; --i) {
        reversed += str[i];
    }
    return reversed;
}

string replaceChar(string str, int index, char newChar) {
    if (index >= 1 && index <= str.length()) {
        str[index - 1] = newChar;
    }
    return str;
}

string removeLastNChars(string str, int n) {
    if (n >= str.length()) {
        return "";
    } else {
        return str.substr(0, str.length() - n);
    }
}

void printString(const string& str) {
    if (str.empty()) {
        cout << "EMPTY" << endl;
    } else {
        cout << str << endl;
    }
}

string reverseByIndex(string str, int start, int end) {
    if (start >= 1 && end <= str.length() && start <= end) {
        while (start < end) {
            swap(str[start - 1], str[end - 1]);
            ++start;
            --end;
        }
    }
    return str;
}

string deleteSubstring(string str, const string& toDelete) {
    size_t pos;
    while ((pos = str.find(toDelete)) != string::npos) {
        str.erase(pos, toDelete.length());
    }
    return str;
}

string convertToNewString(const string& str) {
    string result;
    string asciiStr;

    for (char c : str) {
        if (!isdigit(c)) {
            asciiStr += to_string(static_cast<int>(c));
        } else {
            asciiStr += c;
        }
    }

    for (size_t i = 0; i < asciiStr.length(); i += 2) {
        int value = (asciiStr[i] - '0') * 10 + ((i + 1 < asciiStr.length()) ? (asciiStr[i + 1] - '0') : 0);
        if (value < 32) value += 32;
        result += static_cast<char>(value);
    }

    return result;
}

int main() {
    string str;
    int length;

    cin >> length;
    cin.ignore();
    getline(cin, str);

    string command;
    while (cin >> command) {
        if (command == "SHR") {
            int n;
            cin >> n;
            str = rotateRight(str, n);
        } else if (command == "SHL") {
            int n;
            cin >> n;
            str = rotateLeft(str, n);
        } else if (command == "REM") {
            int n;
            cin >> n;
            str = removeLastNChars(str, n);
        } else if (command == "REV") {
            str = reverseString(str);
        } else if (command == "PUT") {
            int i;
            char c;
            cin >> i >> c;
            str = replaceChar(str, i, c);
        } else if (command == "PRI") {
            printString(str);
        } else if (command == "ReverseByIndex") {
            int start, end;
            cin >> start >> end;
            str = reverseByIndex(str, start, end);
        } else if (command == "Delete") {
            string toDelete;
            cin.ignore();
            getline(cin, toDelete);
            str = deleteSubstring(str, toDelete);
        } else if (command == "Discount") {
            int n;
            cin >> n;
            string validDiscounts;

            string mainAlphabet;
            for (char c : str) {
                if (mainAlphabet.find(c) == string::npos) {
                    mainAlphabet += c;
                }
            }

            for (int i = 0; i < n; ++i) {
                string discount;
                cin >> discount;
                string discountAlphabet;
                for (char c : discount) {
                    if (discountAlphabet.find(c) == string::npos) {
                        discountAlphabet += c;
                    }
                }
                if (discountAlphabet == mainAlphabet) {
                    validDiscounts += discount;
                }
            }
            str += validDiscounts;
        } else if (command == "NewString") {
            str = convertToNewString(str);
        } else if (command == "EXI") {
            break;
        }
    }

    return 0;
}
