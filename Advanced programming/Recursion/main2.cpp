/*Harry, after getting accepted to Hogwarts, has a new worry. His father is concerned about the difficulty of his journey and is considering not allowing him to go. To convince his father, Harry decides to find the longest route in a matrix of cities and avoid traveling along it. Each element in the matrix represents the distance between two consecutive cities. The longest path in the given matrix must be increasing, and the difference between any two consecutive elements on that path must be exactly 1. Write a recursive program to find the longest such path and print the number of roads Harry would travel on.
In this matrix, the path should follow these two conditions:
The selected path should be the longest (i.e., contain the largest number of matrix elements).
The difference between each consecutive element in the path must be exactly 1.
Input:
The first line contains an integer n, representing the dimensions of the matrix.
The next n lines contain the elements of the matrix, each element being unique.
Constraints:
1 ≤ n ≤ 30
Output:
The program should print the number of cities (matrix elements) that the longest path passes through.
Example:
Input:
3
30433 14470 17801
13465 14471 14472
13932 6078 4534
Output:
3
In this example, the longest path is formed by elements 14470, 14471, and 14472, which are adjacent and differ by 1.
*/
#include <iostream>
#include <math.h>
using namespace std;
int find_city( int matrix[], int nmatrix,int navalie,int num,int counter) {
    if(matrix[num]-matrix[num-1]==1 | matrix[num]-matrix[num-1]==-1 ){
        counter++;
    }
    else if(matrix[num]-matrix[num+1]==1 | matrix[num]-matrix[num+1]==-1 ){
        counter++;
    }
    else if(matrix[num]-matrix[num+navalie]==1 | matrix[num]-matrix[num+navalie]==-1 ){
        counter++;
    }
    else if(matrix[num]-matrix[num-navalie]==1 | matrix[num]-matrix[num-navalie]==-1 ){
        counter++;
    }
    num++;

    if(num!=nmatrix) {
        find_city(matrix, nmatrix, navalie, num,counter);
    }
    else{
        return counter;
    }
}

//---------------------------
int main() {
    int navalie;
    int start=0;
    int counter=0;
    cin>>navalie;
    int nmatrix=pow(navalie,2);
    int array[nmatrix];
    for(int r=0;r<nmatrix;r++){
        cin>>array[r];
    }
    int answ=0;
    answ=answ+find_city(array,nmatrix,navalie,start,counter);
    if (answ==0){
        cout<<"1";
    }
    else {
        cout << answ;
    }
}
//---------------------------
