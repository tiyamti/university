/*Write a program that, given a list of all employees and their details, identifies the employee who has made the highest withdrawal from the financial resources.
Input:
First, the number of employees (n) is provided.
Then, in the next n lines, each line contains the following details about an employee in the order: national ID, first name, last name, age, country of residence, and the amount of withdrawal (m) from the financial resources.
Constraints:
1 ≤ n ≤ 100,000
1 ≤ len(string) ≤ 500
0 ≤ m ≤ 1,000,000,000
Output:
Print the details of the employee who has made the highest withdrawal in the format shown below:
Withdrawal amount
National ID
First Name
Last Name
Age
Country
Example:
Input Example 1:
2
12345678 Kian Majlessi 19 IRAN 100
18592756 Fanta New 70 UK 200
Output Example 1:
200
ID: 18592756
First Name: Fanta
Last Name: New
Age: 70
Country: UK
Explanation:
Employee Fanta New, with a withdrawal of 200 units of currency from the company's financial resources, has the highest withdrawal amount, and their complete details are shown in the output.
Input Example 2:
4
12345678 Kian Majlessi 19 IRAN 100
87654321 Amirali Goli 10 Canada 1000
18592756 Fanta New 70 UK 200
12341231 Avengers Marvel 1 US 23
Output Example 2:
1000
ID: 87654321
First Name: Amirali
Last Name: Goli
Age: 10
Country: Canada
Explanation:
Employee Amirali Goli, with a withdrawal of 1000 units of currency from the company's financial resources, has the highest withdrawal amount, and their complete details are shown in the output.*/
#include <iostream>
#include <string>
using namespace std;
struct people
{
    int ID;
    string Firstname;
    string Lastname;
    int Age;
    string Country;
    int Money;
};
int main()
{
    int fav;
    int maximoney=0;
    int size;
    cin>>size;
    people pep[size];
    for(int i=0;i<size;i++){
        cin>>pep[i].ID;
        cin>>pep[i].Firstname;
        cin>>pep[i].Lastname;
        cin>>pep[i].Age;
        cin>>pep[i].Country;
        cin>>pep[i].Money;
        if(pep[i].Money>=maximoney){
            maximoney=pep[i].Money;
            fav=i;
        }
    }

    cout<<pep[fav].Money<<endl;
    cout<<"ID: "<<pep[fav].ID<<endl;
    cout<<"First Name: "<<pep[fav].Firstname<<endl;
    cout<<"Last Name: "<<pep[fav].Lastname<<endl;
    cout<<"Age: "<<pep[fav].Age<<endl;
    cout<<"Country: "<<pep[fav].Country;
    return 0;
}
