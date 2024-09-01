/*First, create a structure to store time, and then solve the following problem using that structure:
Input:
The input consists of two lines, each containing a time (t1 and t2), where each time is given in the format of hour (h), minute (m), and second (s).
The constraints are as follows:
1 ≤ t1.h ≤ 23
0 ≤ t2.h ≤ t1.h - 1
0 ≤ m, s ≤ 59
Output:
Your program should output a single line showing the difference between the two times in the format h:m:s.
Examples:
Input Example 1:
9 23 49
8 1 1
Output Example 1:
1:22:48
Input Example 2:
2 20 33
1 25 16
Output Example 2:
0:55:17*/
#include <iostream>
#include <cmath>
using namespace std;
struct timed{
    int hour;
    int minutes;
    int second;
};
int main() {
    int houri;
    int minutesi;
    int secondi;
    timed tim[2];
    for (int i=0;i<2;i++){
        cin >> tim[i].hour;
        cin >> tim[i].minutes;
        cin >> tim[i].second;
    }
    houri=abs((tim[0].hour)-(tim[1].hour));
    if ((tim[0].minutes)<(tim[1].minutes)){
        houri=houri-1;
        tim[0].minutes=tim[0].minutes+60;
        minutesi=(tim[0].minutes)-(tim[1].minutes);
    }
    else {
        minutesi=(tim[0].minutes)-(tim[1].minutes);
    }
    if ((tim[0].second)<(tim[1].second)){
        minutesi=minutesi-1;
        tim[0].second=tim[0].second+60;
        secondi=(tim[0].second)-(tim[1].second);}
    else{
        secondi=(tim[0].second)-(tim[1].second);}
    cout << houri << ":" << minutesi << ":" << secondi;
    return 0;
}