/*You are given a list of numbers and need to find the numbers that appear exactly k times in the list, then print them in ascending order.
Input:
The first line contains two integers: n (the number of numbers in the list) and k (the exact number of times a number should appear).
The second line contains n integers, each separated by a space.
Output:
Print the numbers that appear exactly k times in ascending order.
Examples:
Input Example 1:
13 5
497 655 497 748 497 527 527 527 527 367 527 497 497
Output Example 1:
497
527
Input Example 2:
14 4
336 320 320 740 919 320 872 320 988 436 792 503 613 712
Output Example 2:
320*/
//answer:
#include <iostream>
using namespace std;
int main()
{
    int tedad, temp, k;
    cin >> tedad;
    cin >> k;
    int arrey[tedad+1];
    for (int o = 0; o < tedad; o++)
    {
        cin >> arrey[o];
    }
    for (int i = 0; i < tedad; i++)
    {
        for (int j = 0; j < tedad - 1; j++)
        {
            if (arrey[j] > arrey[j + 1])
            {
                temp = arrey[j];
                arrey[j] = arrey[j + 1];
                arrey[j + 1] = temp;
            }
        }
    }
    int counter = 1;
    arrey[tedad]=-1;
    for (int i = 0; i < tedad ; i++)
    {

        if (arrey[i] == arrey[i + 1] )
        {
            counter++;
        }
        else if (counter == k)
        {
            cout << arrey[i] << endl;
            counter = 1;
        }
        else counter=1;
    }
    return 0;
}