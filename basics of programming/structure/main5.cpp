/*In this task, you are required to write a program in C that reads the contents of text files and writes them to corresponding text files in a folder named new with the same format.
Input:
There is no input for this question. Your code should read five files named input1.txt, input2.txt, input3.txt, input4.txt, and input5.txt from the current directory (next to the code) and perform the required operations.
Output:
For each text file, a file with the same name and contents should be created in the folder new.
*/
#include <iostream>
#include <fstream>
#include <sys/stat.h>

using namespace std;


void copyFile(const char* inputFile, const char* outputFile) {
    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

    if (!inFile || !outFile) {
        cout << "Error opening file: " << inputFile << endl;
        return;
    }

    char ch;
    while (inFile.get(ch)) {
        outFile.put(ch);
    }

    inFile.close();
    outFile.close();
}

int main() {
#ifdef _WIN32
    mkdir("new");
#else
    mkdir("new", 0777);
#endif
    const char* inputFiles[5] = {"input1.txt", "input2.txt", "input3.txt", "input4.txt", "input5.txt"};

    for (int i = 0; i < 5; ++i) {

        string outputFile = "new/";
        outputFile += inputFiles[i];

        copyFile(inputFiles[i], outputFile.c_str());
    }

    cout << "Files copied successfully!" << endl;

    return 0;
}

