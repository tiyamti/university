/*Problem 1:
A Perfect Number is a number whose divisors (excluding itself) sum up to the number itself. The original program is meant to check if given numbers are perfect or not. However, due to data loss, the function IsPerfect has been erased. You need to rewrite this function.

Additionally, the program never terminates. You need to fix this issue to ensure the program can end gracefully. Some parts of the code were written in an old C language style. Convert those parts into C++ for better understanding by new students.

Problem 2:
Ali, your colleague, has learned Python basics but needs to write a program in C++ that checks if a given matrix is symmetric. Ali has written part of the code, but the function IsSymmetric needs to be corrected and fully implemented due to two issues.

Ali's matrix initialization technique makes him very proud, so you must preserve that part of the code. However, after running the program multiple times, Ali notices the program grows larger and larger in memory. The issue is caused by a memory leak. Find the cause and fix the problem.

Problem 3:
Your two-year-old cousin, who is excellent at reading and writing texts in both Persian and English, struggles with math (and is likely to choose biology in high school). He knows all numbers but cannot keep them in the correct order. Your uncle has sent you a partially implemented program that you need to complete.

Implement the Sort function to sort numbers in both ascending and descending order. Also, implement the Print function to display the contents of the arrays.

Problem 4:
Karim wrote a program for one of his advanced programming assignments, but due to laziness, he skipped making the code secure and clean. A large company later buys out his university and uses his code in its products, eventually discovering that the program has several issues.

The code is supposed to print a range of lowercase English letters (e.g., from the 4th letter to the 20th). Karim's code has multiple issues:

Syntax and logic errors need to be corrected.
Since C++ doesn't perform boundary checking, hackers can exploit this vulnerability to access confidential company data. You need to fix the logic and add a security patch to prevent such exploits.
Tasks:
Problem 1: Rewrite the IsPerfect function and ensure the program terminates properly. Convert any C-style code to C++.
Problem 2: Correct the IsSymmetric function and fix the memory leak issue without altering the array initialization code.
Problem 3: Implement the Sort function (for both ascending and descending) and the Print function.
Problem 4: Fix the code to handle boundary checking, correct any logic errors, and improve security by preventing buffer overflow or out-of-bound access.*/
//problem 1

#include <iostream>
using namespace std;

bool IsPerfect(int num ) ;

int main(void)
{
    int num ;
    while(true)
    {
        cin >> num ;

        if (IsPerfect(num)){
            cout<<num<<" Is Perfect\n";
            break;
        }
        else{
            cout<<num<<" Is NOT Perfect\n";
            break;
        }
    }
}

bool IsPerfect(int number){
    int perfect;
    for(int i=1;i<number;i++){
        if(number%i==0){
            perfect=perfect+i;
        }
    }
    if(number==perfect){
        return true;
    }
    else{
        return false;
    }
}
//----------------------------
//problem 2
#include <iostream>
using namespace std ;

// Declarations :

void GetInput(int** Mat , int n ) ;
bool IsSymetric(int ** Mat , int n) ;


int main (void)
{
    while(true)
    {
        int n ;

        cin>>n;

        if(n == 0)
            break ;

        // Make a 2d Array named mat
        int ** mat = new int * [n] ;
        for (int i = 0 ; i < n ; i++ )
            mat[i] = new int[n] ;

        GetInput(mat,n) ;

        if ( IsSymetric(mat , n) )
            cout << "This matrix is Symetric\n" ;
        else
            cout << "This matrix is NOT Symetric\n" ;
    }
}

void GetInput(int** Mat , int n )
{
    for(int i = 0 ; i < n ; i++)
        for(int j = 0 ; j < n ; j++)
            cin >> Mat[i][j] ;
}

bool IsSymetric(int ** Mat , int n)
{
    for(int i = 0 ; i < n ; i++)
        for(int j = 0 ; j < n ; j++)
            if( Mat[i][j]!= Mat[j][i])
                return false ;
}
//--------------------------------
//problem 3
#include <iostream>
using namespace std;

void GetInput(int* arr , int n) ;
void Sort(int* arr , int n , char Type) ;
void Print(int* arr, int n) ;

int main(void)
{
    int n ;

    cin >> n ;

    int arr1[n] , arr2[n] ;

    GetInput(arr1,n);
    GetInput(arr2,n);
    Sort(arr1,n,'A') ;
    Sort(arr2,n,'D') ;

    Print(arr1, n ) ;
    Print(arr2, n ) ;

}

void GetInput(int* arr , int n)
{
    for(int i = 0 ; i < n ; i++)
        cin >> arr[i] ;
}

void Sort(int* arr , int n , char Type)
{
    int min, temp;
    if(Type == 'A'){
        for(int a=0;a<n;++a){
            min = a;
            for(int b=a+1;b<n;b++){
                if (arr[b] < arr[min])
                    min = b;
                temp = arr[a];
                arr[a] = arr[min];
                arr[min] = temp;
            }
        }
    }
    if(Type == 'D'){
        for (int i = 0; i < n - 1; i++) {
            int mini = i;
            for (int j = i + 1; j < n; j++) {
                if (arr[j] > arr[mini]) {
                    mini = j;
                }
            }
            int tempi = arr[i];
            arr[i] = arr[mini];
            arr[mini] = tempi;
        }
    }
}

void Print(int* arr, int n)
{
    for(int i = 0 ; i < n ; i++)
        cout<<arr[i] <<" ";
    cout<<endl;
}
//--------------------------------
//problem 4
#include <iostream>
using namespace std;

int main(void)
{
    char * Alphabet   = "abcdefghijklmnopqrstuvwxyz" ;

    int a , b , i  ;

    cin >> a>> b ;
    if(a>0 && a<29 && b>0 && b<29 && b>a) {
        for (i = a - 1; i < b; i++)
            cout << (char(*Alphabet + i));

        cout << endl;
    }
    else{
        cout<<"boundary error";
    }
}

