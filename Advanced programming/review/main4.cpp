/*You are tasked with managing a queue of participants in a game, where players are identified by numbers ranging from 1 to 456. The initial queue is given, and you will be asked to perform a series of operations on the queue based on specific commands. The commands are of three types:
Insert a player into the queue at a specified index.
Remove a player from the queue at a specified index.
Reverse the order of the queue.
Your job is to implement a program that performs these operations and outputs the state of the queue after each operation.
Input
The first line contains two integers n (the initial size of the queue) and m (the number of operations).
The second line contains n integers, which are the initial elements of the queue.
The next m lines each describe an operation:
Type 1 operation: "1 index value" — Insert value at position index.
Type 2 operation: "2 index" — Remove the element at position index.
Type 3 operation: "3" — Reverse the queue.
Output
After each operation, output the updated state of the queue.
Constraints
1≤n≤456
1≤m≤100
Example
Input:
4 6
12 61 90 3
1 1 99
1 1 100
2 4
2 0
1 2 11
3
Output:
12 99 61 90 3
12 100 99 61 90 3
12 100 99 61 3
100 99 61 3
100 99 11 61 3
3 61 11 99 100*/
#include <iostream>
using namespace std;
int main() {
    int n_array,temp,b=0;
    int n_command,command,c1=0,nu1=0,c2=0;
    cin>>n_array>>n_command;
    int array[500];
    for(int t=0;t<n_array;t++) {
        cin>>array[t];
    }
    while (b<n_command){
        cin>>command;
        if(command==1) {
            cin >> c1;
            cin >> nu1;
            n_array++;
            int * arr = new int[n_array];
            for (int q = 0; q < n_array; q++) {
                arr[q] = array[q];
            }
            for (int j = n_array; j > c1 - 1; j--) {
                arr[j + 1] = arr[j];
            }
            arr[c1] = nu1;
            for (int p = 0; p < n_array; ++p) {
                cout << arr[p] << " ";
                array[p]=arr[p];
            }
            cout << endl;

        }
        else if(command==2) {
            cin >> c2;
            for (int k = c2; k < n_array; k++) {
                array[k] = array[k + 1];
            }
            n_array--;

            for (int p = 0; p < n_array; ++p) {
                cout << array[p] << " ";
            }
            cout << endl;

        }
        else if(command==3){
            int * arroe = new int[n_array];
            for (int e = 0;e< n_array;e++) {
                arroe[e] = array[e];
            }
            for(int q = 0; q<n_array/2; q++){
                {
                    temp = arroe[ q ];
                    arroe[q ] =arroe[n_array - q - 1];
                    arroe[n_array - q - 1] = temp;
                }
            }
            for( int t=0;t<n_array;t++) {
                cout << arroe[t] << " ";
                array[t]=arroe[t];
            }
            cout << endl;
        }
        b++;
    }

}
