/*Page Structure:
Page Number (integer)
Text (string or character array, maximum length of 100)
Book Structure:
Book Title (string or character array, length 20)
Author Name (string or character array, length 20)
Publisher (string or character array, length 20)
ISBN (string or character array, length 13)
Year of Publication (integer)
Pages (array of page structures)
Author Structure:
Full Name (string or character array, length 20)
National ID (string or character array, length 10)
Books (array of book structures)
Library Structure:
Books (array of book structures)
User Account Structure:
Full Name (string or character array, length 20)
Username (string or character array, length 20)
Password (string or character array, length 20)
List of Borrowed Books (array of book structures)
Required Features and Functions:
Functions for Creating and Editing Structures:
Add a new author
Add and remove books from an author’s list of books
Add and remove books from the library
Edit book and author details
Functions for Searching, Sorting, and Displaying Structure Information:
Display user account information and their borrowed books
Display all books in the library
Filter books by author name, publication year, or publisher
Search and display book information by book title
Search and display author information by author name
Sort books by publication year
Functions for Book Search:
Ability to search for a word or sentence within the pages of a book (if the word or sentence is found, print the page numbers containing it)
Print the text of a specific page by providing the page number
Borrowing Books:
Customers should be able to borrow books. For this, the system should track the number of books currently borrowed, the list of borrowed books, and who borrowed them.
Library Login and Registration:
Login with username and password (if either is incorrect, a warning should be displayed)
Registration with required information (password must contain at least one number, one uppercase letter, and one lowercase letter; otherwise, a warning should be displayed)
Saving to File:
Save all information (including user account information, borrowed books, book, author, and library data) to a file.
Load data from a file at the beginning of the program (so that information from previous program runs, such as login details and books, can be used).
This section is optional for extra credit.

User Interface:
At the start of the program, a menu should be displayed that includes the requested features. Selecting an option should execute the corresponding functionality. The design of the menu is up to you.
The display format for book, author, and account information is also up to you, but all required details should be shown.*/
//it might have some problems
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<string.h>
#include<conio.h>
using namespace std;
struct page{
    int number_page;
    string *text_page;
};
struct book{
    string name_book;
    string author_book;
    string publisher_book;
    string ISBN_book;
    int year_book;
    struct page pages;
};
struct author{
    string name_author;
    int ID_author;
    struct book author_books;
};
struct library{
    struct book book_library;
};
struct account{
    string name_account;
    string nickname_account;
    string password_account;
};
//----------------
void printMessageCenter(const char* message);
void headMessage(const char *message);
void welcomeMessage();
void main_menu();
void check_client();
void check_password();
void client();
void administer();
void view_list();
void searching_list();
void rent();
void add_list();
void edit_list();
void remove_list();
void account_info_list_admin();
void account_info_admin();
void change_password_admin();
void account_info_list_client();
void adding_author();
void showing_author();
void editing_author();
void searching_author();
void adding_author_book();
void showing_author_book();
void removing_author_book();
void searching_author_book();
void adding_book_list();
void showing_book_list();
void editing_book_list();
void removing_book_list();
void searching_book_list_byname();
void searching_book_list_byyear();
void searching_book_list_bypublisher();
void renting();
void rent_list();
void exist_book();
void book_make();
void search_in_book();
//----------------------
void printMessageCenter(const char* message)
{
    int len =0;
    int pos = 0;

    //calculate how many space need to print
    len = (78 - strlen(message))/2;
    printf("\t\t\t");
    for(pos =0 ; pos < len ; pos++)
    {
        //print space
        printf(" ");
    }
    //print message
    printf("%s",message);

}
void headMessage(const char *message)
{
    system("cls");
    printf("\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############             Library management System             ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printMessageCenter(message);
    printf("\n\t\t\t----------------------------------------------------------------------------");

}
void welcomeMessage()
{

    headMessage("titi library");
    printf("\n\n\n\n\n");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t        =                 WELCOME                   =");
    printf("\n\t\t\t        =                   TO                      =");
    printf("\n\t\t\t        =                 LIBRARY                   =");
    printf("\n\t\t\t        =               MANAGEMENT                  =");
    printf("\n\t\t\t        =                 SYSTEM                    =");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\n\n\t\t\t Enter any key to continue.....");
    getch();
}
void main_menu()
{
    int i;
    cout<<"\n\t############ LIBRARY MANAGEMENT SYSTEM ############\n\n\n";
    cout<<"\n\t\t>>Please Choose Any Option To login \n";
    cout<<"\n\t\t1.Client\n\n\t\t2.Administer\n\n\t\t3.Close Application\n";
    cout<<"\n\t\tEnter your choice : ";
    cin>>i;
    if(i==1)
    {
        system("cls");
        check_client();
    }
    else if(i==2)
        check_password();

    else if(i==3)
        exit(0);
    else
    {
        cout<<"\n\t\tPlease enter correct option :(";
        getch();
        system("CLS");
        main_menu();
    }
}
void check_client(){
    cout<<"\n\t\tEnter the details :-\n";
    cout<<"\n\t\tEnter the account name:-\n";
    int check;
    string line;
    string  item;
    cin>>item;
    bool checking = false;
    fstream infile;
    infile.open ("C:\\Users\\Partiran\\CLionProjects\\logiin\\client_info.text",ios:: in);
    if(infile.is_open()) {
        bool checking = false;
        while (!checking) {
            if (!checking){
                while (!infile.eof()) {
                    getline(infile, line);
                    if ((check = line.find(item, 0)) != string::npos) {
                        checking = true;
                        cout<<"correct";
                        break;
                    }
                }
            }
        }
    }
    infile.close();
    cout<<"\n\t\tEnter the account password:-\n";
    string  itemp;
    cin>>itemp;
    bool checking2 = false;
    fstream in2file;
    in2file.open ("C:\\Users\\Partiran\\CLionProjects\\logiin\\client_info.text",ios:: in);
    if(in2file.is_open()) {
        bool checking2 = false;
        while (!checking2) {
            if (!checking2) {
                while (!in2file.eof()) {
                    getline(in2file, line);
                    if ((check = line.find(itemp, 0)) != string::npos) {
                        checking2=true;
                        if(checking2== true){
                            cout<<"correct";
                        }
                        break;
                    }
                }
            }
        }
    }
    in2file.close();
    if(checking== true && checking2== true){
        client();
    }
}
void check_password()
{
    int i=0;
    char ch,st[21],ch1[21]={"learnprogramo"};
    fstream outfile;
    outfile.open ("C:\\Users\\Partiran\\CLionProjects\\logiin\\password.txt",ios:: out);
    outfile << ch1<< endl;
    cout<<"\n\t\tEnter Password : ";
    while(1)
    {
        ch=getch();
        if(ch==13)
        {
            st[i]='\0';
            break;
        }
        else if(ch==8&&i>0)
        {
            i--;
            cout<<"\b \b";
        }
        else
        {
            cout<<"*";
            st[i]=ch;
            i++;
        }
    }
    string tp;
    fstream inf;
    inf.open("C:\\Users\\Partiran\\CLionProjects\\logiin\\password.txt");
    if (inf.is_open()){
        while(getline(inf, tp)){
            cout <<tp << "\n";
        }
        inf.close();
    }
    for(i=0;st[i]==ch1[i]&&st[i]!='\0'&&ch1[i]!='\0';i++);
    if(st[i]=='\0'&&ch1[i]=='\0')
    {
        system("cls");
        administer();
    }
    else
    {
        cout<<"\n\n\t\tWrong Password.\n\n\t\ttry again.....\n";
        getch();
        system("cls");
        main_menu();
    }
}
void client()
{
    int i;
    cout<<"\n\t$$$$$$$$$$$$ WELCOME CLIENT $$$$$$$$$$$$\n";
    cout<<"\n\t\t>>Please Choose One Option:\n";
    cout<<"\n\t\t1.View Lists\n\n\t\t2.Searching\n\n\t\t3.rent\n\n\t\t4.account info\n\n\t\t5.search in book\n\n\t\t6.Go to main menu\n\n\t\t7.Close Application\n";
    cout<<"\n\t\tEnter your choice : ";
    cin>>i;
    if(i==1) {
        view_list();
    }

    else if(i==2){
        searching_list();
    }
    else if(i==3){
        rent();
    }
    else if(i==4){
        account_info_list_client();
    }
    else if(i==5){
        search_in_book();
    }
    else if(i==6)
    {
        system("cls");
        main_menu();
    }
    else if(i==7)
        exit(0);
    else
    {
        cout<<"\n\t\tPlease enter correct option :(";
        getch();
        system("cls");
        client();
    }
}
void administer()
{
    int i;
    cout<<"\n\t$$$$$$$$$$$$ WELCOME ADMINISTER $$$$$$$$$$$$\n";
    cout<<"\n\t\t>>Please Choose One Option:\n";
    cout<<"\n\t\t1.View Lists\n\n\t\t2.Searching\n\n\t\t3.rent\n\n\t\t4.account info\n\n\t\t5.other account info\n\n\t\t6.add lists\n\n\t\t7.edit lists\n\n\t\t8.book make\n\n\t\t9.search in book\n\n\t\t10.remove lists\n\n\t\t11.Go to main menu\n\n\t\t12.Close Application\n";
    cout<<"\n\t\tEnter your choice : ";
    cin>>i;
    switch(i)
    {
        case 1:
            view_list();
            break;
        case 2:
            searching_list();
            break;
        case 3:
            rent();
            break;
        case 4:
            account_info_list_admin();
            break;
        case 5:
            account_info_list_client();
            break;
        case 6:
            add_list();
            break;
        case 7:
            edit_list();
            break;
        case 8:
            book_make();
            break;
        case 9:
            search_in_book();
            break;
        case 10:
            remove_list();
            break;
        case 11:system("cls");
            main_menu();
            break;
        case 12:exit(0);
        default:cout<<"\n\t\tPlease enter correct option :(";
            getch();
            system("cls");
            administer();
    }
}
void view_list(){
    cout<<"\n\t&&&&&&&&&& VIEW LIST &&&&&&&&&&\n";
    cout<<"\n\t\t>>Please Choose One Option:\n";
    cout<<"\n\t\t1.authors\n\n\t\t2.author's books\n\n\t\t3.books\n\n\t\t4.Go to main menu\n\n\t\t5.Close Application\n";
    cout<<"\n\t\tEnter your choice : ";
    int i;
    cin>>i;

    if(i==1){
        showing_author();
    }
    else if(i==2){
        showing_author_book();
    }
    else if(i==3){
        showing_book_list();
    }
    else if(i==4)
    {
        system("cls");
        main_menu();
    }
    else if(i==5)
        exit(0);
    else
    {
        cout<<"\n\t\tPlease enter correct option :(";
        getch();
        system("cls");
        main_menu();
    }
}
void searching_list(){
    cout<<"\n\t&&&&&&&&&& SEARCHING LIST &&&&&&&&&&\n";
    cout<<"\n\t\t>>Please Choose One Option:\n";
    cout<<"\n\t\t1.Searching author\n\n\t\t2.Searching author's book\n\n\t\t3.Searching books by name\n\n\t\t4.Searching books by year\n\n\t\t5.Searching by publisher\n\n\t\t6.Go to main menu\n\n\t\t7.Close Application\n";
    cout<<"\n\t\tEnter your choice : ";
    int i;
    cin>>i;
    if(i==1) {
        searching_author();
    }

    else if(i==2){
        searching_author_book();
    }
    else if(i==3){
        searching_book_list_byname();
    }
    else if(i==4){
        searching_book_list_byyear();
    }
    else if(i==5){
        searching_book_list_bypublisher();
    }
    else if(i==6)
    {
        system("cls");
        main_menu();
    }
    else if(i==7)
        exit(0);
    else
    {
        cout<<"\n\t\tPlease enter correct option :(";
        getch();
        system("cls");
        main_menu();
    }
}
void rent(){
    cout<<"\n\t&&&&&&&&&& RENT &&&&&&&&&&\n";
    cout<<"\n\t\t>>Please Choose One Option:\n";
    cout<<"\n\t\t1.renting\n\n\t\t2.rent list\n\n\t\t3.exist books\n\n\t\t4.Go to main menu\n\n\t\t5.Close Application\n";
    cout<<"\n\t\tEnter your choice : ";
    int i;
    cin>>i;
    if(i==1){
        renting();
    }
    else if(i==2){
        rent_list();
    }
    else if(i==3){
        exist_book();
    }
    else if(i==4)
    {
        system("cls");
        main_menu();
    }
    else if(i==5)
        exit(0);
    else
    {
        cout<<"\n\t\tPlease enter correct option :(";
        getch();
        system("cls");
        main_menu();
    }
}
void add_list(){
    cout<<"\n\t&&&&&&&&&& ADD LIST &&&&&&&&&&\n";
    cout<<"\n\t\t>>Please Choose One Option:\n";
    cout<<"\n\t\t1.add author\n\n\t\t2.add author list book\n\n\t\t3.add book list\n\n\t\t4.Go to main menu\n\n\t\t5.Close Application\n";
    cout<<"\n\t\tEnter your choice : ";
    int i;
    cin>>i;
    if(i==1){
        adding_author();
    }
    else if(i==2){
        adding_author_book();
    }
    else if(i==3){
        adding_book_list();
    }
    else if(i==4)
    {
        system("cls");
        main_menu();
    }
    else if(i==5)
        exit(0);
    else
    {
        cout<<"\n\t\tPlease enter correct option :(";
        getch();
        system("cls");
        main_menu();
    }
}
void edit_list(){
    cout<<"\n\t&&&&&&&&&& EDIT LIST &&&&&&&&&&\n";
    cout<<"\n\t\t>>Please Choose One Option:\n";
    cout<<"\n\t\t1.edit author\n\n\t\t2.edit book list\n\n\t\t3.Go to main menu\n\n\t\t4.Close Application\n";
    cout<<"\n\t\tEnter your choice : ";
    int i;
    cin>>i;
    if(i==1){
        editing_author();
    }
    else if(i==2){
        editing_book_list();
    }
    else if(i==3)
    {
        system("cls");
        main_menu();
    }
    else if(i==4)
        exit(0);
    else
    {
        cout<<"\n\t\tPlease enter correct option :(";
        getch();
        system("cls");
        main_menu();
    }
}


void remove_list(){
    cout<<"\n\t&&&&&&&&&& REMOVE LIST &&&&&&&&&&\n";
    cout<<"\n\t\t>>Please Choose One Option:\n";
    cout<<"\n\t\t1.remove author\n\n\t\t2.remove book list\n\n\t\t3.Go to main menu\n\n\t\t4.Close Application\n";
    cout<<"\n\t\tEnter your choice : ";
    int i;
    cin>>i;
    if(i==1){
        removing_author_book();
    }
    else if(i==2){
        removing_book_list();
    }
    else if(i==3)
    {
        system("cls");
        main_menu();
    }
    else if(i==4)
        exit(0);
    else
    {
        cout<<"\n\t\tPlease enter correct option :(";
        getch();
        system("cls");
        main_menu();
    }
}

void change_password_admin()
{
    int i=0,j=0;
    char ch,st[21],ch1[21]={"learnprogramo"};
    fstream outfile;
    outfile.open ("C:\\Users\\Partiran\\CLionProjects\\logiin\\password.txt",ios:: out);
    outfile << ch1<< endl;
    outfile<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    system("cls");
    cout<<"\n\n\t\tEnter Old Password : ";
    while(1)
    {
        ch=getch();
        if(ch==13)
        {
            st[i]='\0';
            break;
        }
        else if(ch==8&&i>0)
        {
            i--;
            cout<<"\b \b";
        }
        else
        {
            cout<<"*";
            st[i]=ch;
            i++;
        }
    }
    string tp;
    fstream inf;
    inf.open("C:\\Users\\Partiran\\CLionProjects\\logiin\\password.txt");
    if (inf.is_open()){
        while(getline(inf, tp)){
            cout << tp << "\n";
        }
        inf.close();
    }
    for(i=0;st[i]==ch1[i]&&st[i]!='\0'&&ch1[i]!='\0';i++);
    if(st[i]=='\0'&&ch1[i]=='\0')
    {
        system("cls");
        cout<<"\n\t**The Password Should be less than 20 characters & don't use spaces**\n\n";
        cout<<"\n\t\tEnter New Password : ";
        fflush(stdin);
        i=0;
        while(1)
        {
            j++;
            ch=getch();
            if(ch==13)
            {
                for(i=0;st[i]!=' '&&st[i]!='\0';i++);
                if(j>20 || st[i]==' ')
                {
                    cout<<"\n\n\t\tYou did't follow the instruction \n\n\t\tPress any key for try again.....";
                    getch();
                    system("cls");
                    change_password_admin();
                    administer();
                }
                st[i]='\0';
                break;
            }
            else if(ch==8&&i>0)
            {
                i--;
                cout<<"\b \b";
            }
            else
            {
                cout<<"*";
                st[i]=ch;
                i++;
            }
        }
        fstream outf;
        outf.open ("C:\\Users\\Partiran\\CLionProjects\\logiin\\password.txt",ios:: out);
        outf << ch1 << endl;
        outf.close();
        cout<<"\n\n\t\tYour Password has been changed Successfully.";
        cout<<"\n\t\tPress any key to continue......";
        getch();
        system("cls");
        administer();
    }
    else
    {
        cout<<"\n\n\t\tPassword is incorrect.....\n";
        cout<<"\n\t\tEnter 1 for retry or 2 for menu";
        cin>>i;
        if(i==1)
        {
            system("cls");
            change_password_admin();
        }
        else
        {
            system("cls");
            administer();
        }
    }
}
void account_info_list_admin(){
    cout<<"\n\t\t>>Please Choose One Option:\n";
    cout<<"\n\t\t1.Account information\n\n\t\t2.Change admin's password\n\n\t\t3.Go to main menu\n\n\t\t4.Close Application\n";
    cout<<"\n\t\tEnter your choice : ";
    int j;
    cin>>j;
    switch(j) {
        case 1:
            account_info_admin();
            break;
        case 2:
            change_password_admin();
            break;
        case 3:
            system("cls");
            main_menu();
            break;
        case 4:
            exit(0);
        default:
            cout << "\n\t\tPlease enter correct option :(";
            getch();
            system("cls");
            administer();
    }
}
void account_info_admin(){
    cout<<"\n\t\t>>Please Choose One Option:\n";
    cout<<"\n\t\t1.Show info\n\n\t\t2.Edit info\n\n\t\t3.Go to main menu\n\n\t\t4.Close Application\n";
    cout<<"\n\t\tEnter your choice : ";
    int j;
    cin>>j;
    if(j==1) {
        fstream infile;
        infile.open("C:\\Users\\Partiran\\CLionProjects\\logiin\\admin_info.txt", ios::in);
        if (infile.is_open()) {
            string tp;
            while (getline(infile, tp)) {
                cout << tp << "\n";
            }
            infile.close();
        }
    }
    if(j==2) {
        string name;
        string age;
        cout<<"enter new amin's name:-";
        cin>>name;
        cout<<"enter new admin's age:-";
        cin>>age;
        fstream outf;
        outf.open ("C:\\Users\\Partiran\\CLionProjects\\logiin\\admin_info.txt",ios:: out);
        outf <<"admin:"<<name  << endl;
        outf<<"age"<<age<<endl;
        outf.close();
    }
    if(j==3) {
        system("cls");
        main_menu();
    }
    if(j==4) {
        exit(0);
    }
    else{
        cout << "\n\t\tPlease enter correct option :(";
        getch();
        system("cls");
        administer();
    }
}
void account_info_list_client(){
    cout<<"\n\t\t>>Please Choose One Option:\n";
    cout<<"\n\t\t1.Account information\n\n\t\t2.Change account password\n\n\t\t3.Go to main menu\n\n\t\t4.Close Application\n";
    cout<<"\n\t\tEnter your choice : ";
    int j;
    cin>>j;
    switch(j) {
        case 1:
            //account_info_client();
            break;
        case 2:
            //change_password_client(); make it
            break;
        case 3:
            system("cls");
            main_menu();
            break;
        case 4:
            exit(0);
        default:
            cout << "\n\t\tPlease enter correct option :(";
            getch();
            system("cls");
            client();
    }
}
void adding_author(){
    struct author author_info;
    struct book book_author;
    struct page page_book_author;
    cout<<"number:";
    int number;
    cin>>number;
    for(int i=0;i<number;i++) {
        cout << "\n\t\tEnter the details :-\n";
        cout << "\n\t\tEnter Author's Name : ";
        cin >> author_info.name_author;
        cout << "\n\t\tEnter Author's ID : ";
        cin >> author_info.ID_author;
        fstream outfile;
        outfile.open ("C:\\Users\\Partiran\\CLionProjects\\my_code\\author_list_info.txt",ios:: app);
        outfile << author_info.name_author <<":";
        outfile << author_info.ID_author << endl;
        outfile<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        outfile.close();
    }
    administer();
}
void showing_author(){
    struct author author_info;
    fstream infile;
    infile.open("C:\\Users\\Partiran\\CLionProjects\\my_code\\author_list_info.txt",ios::in);
    if (infile.is_open()){
        string tp;
        while(getline(infile, tp)){
            cout << tp << "\n";
        }
        infile.close();
    }
    main_menu();
}
void editing_author(){
    struct author author_info;
    cout<<"\n\t\tEnter the details :-\n";
    cout<<"\n\t\tEnter Author's Name : ";
    string  item;
    cin>>item;
    int checker;
    string liner;
    fstream infile;
    infile.open ("C:\\Users\\Partiran\\CLionProjects\\my_code\\author_list_info.txt",ios:: in);
    if(infile.is_open()) {
        bool checking = false;
        while (!checking) {
            if (!checking) {
                while (!infile.eof()) {
                    getline(infile, liner);
                    if ((checker = liner.find(item, 0)) != string::npos) {
                        cout << "\n\t\tAuthor's Name & ID: ";
                        cout << liner << "\n";
                    }
                }
            }
        }
    }
    infile.close();
    cout<<"\n\t\tEnter the details :-\n";
    cout<<"\n\t\tEnter Author's Name : ";
    string itemi;
    cin>>itemi;
    fstream infiile;
    infiile.open ("C:\\Users\\Partiran\\CLionProjects\\my_code\\author_list_info.txt",ios:: app);
    string line1;
    int check1;
    if (infiile.is_open()) {
        bool checking1=false;
        while (!checking1) {
            if (!checking1) {
                while (!infiile.eof()) {
                    getline(infiile, line1);
                    if ((check1 = line1.find(itemi, 0)) != string::npos) {
                        line1="";
                        check1 = true;
                        break;
                    }
                }

            }
        }
    }
    infiile.close();
    cout << "\n\t\tEnter the details :-\n";
    cout << "\n\t\tEnter Author's Name : ";
    cin >> author_info.name_author;
    cout << "\n\t\tEnter Author's ID : ";
    cin >> author_info.ID_author;
    fstream outfile;
    outfile.open ("C:\\Users\\Partiran\\CLionProjects\\my_code\\author_list_info.txt",ios:: app);
    outfile << author_info.name_author <<":";
    outfile << author_info.ID_author << endl;
    outfile<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    outfile.close();
    administer();
}
void searching_author(){
    struct author author_info;
    int check;
    string line;
    cout<<"\n\t\tEnter the details :-\n";
    cout<<"\n\t\tEnter Author's Name : ";
    string  item;
    cin>>item;
    fstream infile;
    infile.open ("C:\\Users\\Partiran\\CLionProjects\\my_code\\author_list_info.txt",ios:: in);
    if(infile.is_open()) {
        bool checking = false;
        while (!checking) {
            if (!checking) {
                while (!infile.eof()) {
                    getline(infile, line);
                    if ((check = line.find(item, 0)) != string::npos) {
                        cout << "\n\t\tAuthor's Name & ID: ";
                        cout << line << "\n";
                    }
                }
            }
        }
    }
    infile.close();
    main_menu();
}
void adding_author_book(){
    struct author author_info;
    struct book book_author;
    struct page page_book_author;
    int c;
    cout<<"\n\t\t1adding without author\n\n\t\t2.adding with author\n";
    cin>>c;
    if(c==1){
        struct author author_info;
        int check;
        string line;
        cout<<"\n\t\tEnter the details :-\n";
        cout<<"\n\t\tEnter Author's Name : ";
        string  item;
        cin>>item;
        fstream infile;
        infile.open ("C:\\Users\\Partiran\\CLionProjects\\my_code\\author_list_book.txt",ios:: in);
        if(infile.is_open()) {
            bool checking = false;
            while (!checking) {
                if (!checking) {
                    while (!infile.eof()) {
                        getline(infile, line);
                        if ((check = line.find(item, 0)) != string::npos) {
                            cout << "\n\t\tAuthor's Name & ID: ";
                            cout << line << "\n";
                        }
                    }
                }
            }
        }
        infile.close();
        cout << "number:";
        int number;
        cin >> number;
        for (int i = 0; i < number; i++) {
            cout << "\n\t\tEnter the details :-\n";
            cout<<"\n\t\tEnter Author's Name : ";
            cin>>author_info.name_author;
            cout<<"\n\t\tEnter Author's ID : ";
            cin>>author_info.ID_author;
            cout << "\n\t\tEnter Book's Name : ";
            cin >> book_author.name_book;;
            cout << "\n\t\tEnter Publication name : ";
            cin >> book_author.publisher_book;
            cout << "\n\t\tEnter Book's ISBN : ";
            cin >> book_author.ISBN_book;
            cout << "\n\t\tEnter Book's Year : ";
            cin >> book_author.year_book;
            cout << "\n\t\tEnter Book's page : ";
            cin >> page_book_author.number_page;
            fstream outfile;
            outfile.open ("C:\\Users\\Partiran\\CLionProjects\\my_code\\author_list_book.txt",ios:: app);
            outfile << author_info.name_author <<":";
            outfile << author_info.ID_author << ":";
            outfile << book_author.name_book << ":";
            outfile << book_author.publisher_book << ":";
            outfile << book_author.ISBN_book << ":";
            outfile << book_author.year_book << ":";
            outfile << page_book_author.number_page<<endl ;
            outfile<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
            outfile.close();
        }
    }
    if(c==2) {
        cout << "number:";
        int number;
        cin >> number;
        for (int i = 0; i < number; i++) {
            cout << "\n\t\tEnter the details :-\n";
            cout<<"\n\t\tEnter Author's Name : ";
            cin>>author_info.name_author;
            cout<<"\n\t\tEnter Author's ID : ";
            cin>>author_info.ID_author;
            cout << "\n\t\tEnter Book's Name : ";
            cin >> book_author.name_book;;
            cout << "\n\t\tEnter Publication name : ";
            cin >> book_author.publisher_book;
            cout << "\n\t\tEnter Book's ISBN : ";
            cin >> book_author.ISBN_book;
            cout << "\n\t\tEnter Book's Year : ";
            cin >> book_author.year_book;
            cout << "\n\t\tEnter Book's page : ";
            cin >> page_book_author.number_page;
            fstream outfile;
            outfile.open ("C:\\Users\\Partiran\\CLionProjects\\my_code\\author_list_book.txt",ios:: app);
            outfile << author_info.name_author <<":";
            outfile << author_info.ID_author << ":";
            outfile << book_author.name_book << ":";
            outfile << book_author.publisher_book << ":";
            outfile << book_author.ISBN_book << ":";
            outfile << book_author.year_book << ":";
            outfile << page_book_author.number_page<<endl ;
            outfile<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
            outfile.close();
        }
    }
    administer();
}
void showing_author_book(){
    fstream infile;
    infile.open("C:\\Users\\Partiran\\CLionProjects\\my_code\\author_list_book.txt",ios::in);
    if (infile.is_open()){
        string tp;
        while(getline(infile, tp)){
            cout << tp << "\n";
        }
        infile.close();
    }
    main_menu();
}
void removing_author_book(){
    struct author author_info;
    struct book book_author;
    struct page page_book_author;
    cout<<"\n\t\tEnter the details :-\n";
    cout<<"\n\t\tEnter Author's Name : ";
    string  item;
    cin>>item;
    int checker;
    string liner;
    fstream infile;
    infile.open ("C:\\Users\\Partiran\\CLionProjects\\my_code\\author_list_book.txt",ios:: in);
    if(infile.is_open()) {
        bool checking = false;
        while (!checking) {
            if (!checking) {
                while (!infile.eof()) {
                    getline(infile, liner);
                    if ((checker = liner.find(item, 0)) != string::npos) {
                        cout << "\n\t\tAuthor's Name & ID: ";
                        cout << liner << "\n";
                    }
                }
            }
        }
    }
    infile.close();
    cout<<"\n\t\tEnter the details :-\n";
    cout<<"\n\t\tEnter Author's Name : ";
    string itemi;
    cin>>itemi;
    fstream infiile;
    infiile.open ("C:\\Users\\Partiran\\CLionProjects\\my_code\\author_list_book.txt",ios:: app);
    string line1;
    int check1;
    if (infiile.is_open()) {
        bool checking1=false;
        while (!checking1) {
            if (!checking1) {
                while (!infiile.eof()) {
                    getline(infiile, line1);
                    if ((check1 = line1.find(itemi, 0)) != string::npos) {
                        line1="";
                        check1 = true;
                        break;
                    }
                }

            }
        }
    }
    infiile.close();
    administer();
}

void searching_author_book(){
    struct author author_info;
    int check;
    string line;
    cout<<"\n\t\tEnter the details :-\n";
    cout<<"\n\t\tEnter Author's Name : ";
    string  item;
    cin>>item;
    fstream infile;
    infile.open ("C:\\Users\\Partiran\\CLionProjects\\my_code\\author_list_book.txt",ios:: in);
    if(infile.is_open()) {
        bool checking = false;
        while (!checking) {
            if (!checking) {
                while (!infile.eof()) {
                    getline(infile, line);
                    if ((check = line.find(item, 0)) != string::npos) {
                        cout << "\n\t\tAuthor's Name & ID & book: ";
                        cout << line << "\n";
                    }
                }
            }
        }
    }
    infile.close();
    main_menu();
}
void adding_book_list(){
    struct book book_adding;
    struct page page_book;
    cout<<"number:";
    int number;
    cin>>number;
    for(int i=0;i<number;i++) {
        cout << "\n\t\tEnter the details :-\n";
        cout << "\n\t\tEnter Book's Name : ";
        cin >> book_adding.name_book;
        cout << "\n\t\tEnter Author's Name : ";
        cin >> book_adding.author_book;
        cout << "\n\t\tEnter Publication name : ";
        cin >> book_adding.publisher_book;
        cout << "\n\t\tEnter Book's ISBN : ";
        cin >> book_adding.ISBN_book;
        cout << "\n\t\tEnter Book's Year : ";
        cin >> book_adding.year_book;
        cout << "\n\t\tEnter Book's page : ";
        cin >> page_book.number_page;
        fstream outfile;
        outfile.open ("C:\\Users\\Partiran\\CLionProjects\\my_code\\book_list.txt",ios:: app);
        outfile << book_adding.name_book << ":";
        outfile << book_adding.author_book << ":";
        outfile << book_adding.publisher_book <<":" ;
        outfile << book_adding.ISBN_book << ":";
        outfile << book_adding.year_book << ":";
        outfile << page_book.number_page <<endl;
        outfile<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
        outfile.close();
    }
    administer();
}
void showing_book_list(){
    fstream infile;
    infile.open("C:\\Users\\Partiran\\CLionProjects\\my_code\\book_list.txt",ios::in);
    if (infile.is_open()){
        string tp;
        while(getline(infile, tp)){
            cout << tp << "\n";
        }
        infile.close();
    }
    main_menu();
}
void editing_book_list(){
    struct book book_adding;
    struct page page_book;
    cout<<"\n\t\tEnter the details :-\n";
    cout<<"\n\t\tEnter books's Name : ";
    string  item;
    cin>>item;
    int checker;
    string liner;
    fstream infile;
    infile.open ("C:\\Users\\Partiran\\CLionProjects\\my_code\\book_list.txt",ios:: in);
    if(infile.is_open()) {
        bool checking = false;
        while (!checking) {
            if (!checking) {
                while (!infile.eof()) {
                    getline(infile, liner);
                    if ((checker = liner.find(item, 0)) != string::npos) {
                        cout << "\n\t\tbook's information: ";
                        cout << liner << "\n";
                    }
                }
            }
        }
    }
    infile.close();
    cout<<"\n\t\tEnter the details :-\n";
    cout<<"\n\t\tEnter Book's Name : ";
    string itemi;
    cin>>itemi;
    fstream infiile;
    infiile.open ("C:\\Users\\Partiran\\CLionProjects\\my_code\\book_list.txt",ios:: app);
    string line1;
    int check1;
    if (infiile.is_open()) {
        bool checking1=false;
        while (!checking1) {
            if (!checking1) {
                while (!infiile.eof()) {
                    getline(infiile, line1);
                    if ((check1 = line1.find(itemi, 0)) != string::npos) {
                        line1="";
                        check1 = true;
                        break;
                    }
                }

            }
        }
    }
    infiile.close();
    cout << "\n\t\tEnter the details :-\n";
    cout << "\n\t\tEnter Book's Name : ";
    cin >> book_adding.name_book;
    cout << "\n\t\tEnter Author's Name : ";
    cin >> book_adding.author_book;
    cout << "\n\t\tEnter Publication name : ";
    cin >> book_adding.publisher_book;
    cout << "\n\t\tEnter Book's ISBN : ";
    cin >> book_adding.ISBN_book;
    cout << "\n\t\tEnter Book's Year : ";
    cin >> book_adding.year_book;
    cout << "\n\t\tEnter Book's page : ";
    cin >> page_book.number_page;
    fstream outfile;
    outfile.open ("C:\\Users\\Partiran\\CLionProjects\\my_code\\book_list.txt",ios:: app);
    outfile << book_adding.name_book << ":";
    outfile << book_adding.author_book << ":";
    outfile << book_adding.publisher_book <<":" ;
    outfile << book_adding.ISBN_book << ":";
    outfile << book_adding.year_book << ":";
    outfile << page_book.number_page <<endl;
    outfile<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
    outfile.close();
    administer();
}
void removing_book_list(){
    struct book book_list;
    struct page page_book;
    cout<<"\n\t\tEnter the details :-\n";
    cout<<"\n\t\tEnter books's Name : ";
    string  item;
    cin>>item;
    int checker;
    string liner;
    fstream infile;
    infile.open ("C:\\Users\\Partiran\\CLionProjects\\my_code\\book_list.txt",ios:: in);
    if(infile.is_open()) {
        bool checking = false;
        while (!checking) {
            if (!checking) {
                while (!infile.eof()) {
                    getline(infile, liner);
                    if ((checker = liner.find(item, 0)) != string::npos) {
                        cout << "\n\t\tbook's information: ";
                        cout << liner << "\n";
                    }
                }
            }
        }
    }
    infile.close();
    cout<<"\n\t\tEnter the details :-\n";
    cout<<"\n\t\tEnter Book's Name : ";
    string itemi;
    cin>>itemi;
    fstream infiile;
    infiile.open ("C:\\Users\\Partiran\\CLionProjects\\my_code\\book_list.txt",ios:: app);
    string line1;
    int check1;
    if (infiile.is_open()) {
        bool checking1=false;
        while (!checking1) {
            if (!checking1) {
                while (!infiile.eof()) {
                    getline(infiile, line1);
                    if ((check1 = line1.find(itemi, 0)) != string::npos) {
                        line1="";
                        check1 = true;
                        break;
                    }
                }

            }
        }
    }
    administer();
}
void searching_book_list_byname(){
    struct book book_adding;
    struct page page_book;
    cout<<"\n\t\tEnter the details :-\n";
    cout<<"\n\t\tEnter Book's Name : ";
    int check;
    string line;
    string  item;
    cin>>item;
    fstream infile;
    infile.open ("C:\\Users\\Partiran\\CLionProjects\\my_code\\book_list.txt",ios:: in);
    if(infile.is_open()) {
        bool checking = false;
        while (!checking) {
            if (!checking) {
                while (!infile.eof()) {
                    getline(infile, line);
                    if ((check = line.find(item, 0)) != string::npos) {
                        cout << "\n\t\tbook's information: ";
                        cout << line << "\n";
                    }
                }
            }
        }
    }
    infile.close();
    main_menu();
}
void searching_book_list_byyear() {
    struct book book_adding;
    struct page page_book;
    cout << "\n\t\tEnter the details :-\n";
    cout << "\n\t\tEnter Book's Year : ";
    int check;
    string line;
    int  item;
    cin>>item;
    fstream infile;
    infile.open ("C:\\Users\\Partiran\\CLionProjects\\my_code\\book_list.txt",ios:: in);
    if(infile.is_open()) {
        bool checking = false;
        while (!checking) {
            if (!checking) {
                while (!infile.eof()) {
                    getline(infile,line );
                    if ((check = line.find(item, 0)) != string::npos) {
                        cout << "\n\t\tbook's information: ";
                        cout << line << "\n";
                    }
                }
            }
        }
    }
    infile.close();
    main_menu();
}
void searching_book_list_bypublisher(){
    struct book book_adding;
    struct page page_book;
    cout<<"\n\t\tEnter the details :-\n";
    cout<<"\n\t\tEnter Book's publisher : ";
    int check;
    string line;
    string  item;
    cin>>item;
    fstream infile;
    infile.open ("C:\\Users\\Partiran\\CLionProjects\\my_code\\book_list.txt",ios:: in);
    if(infile.is_open()) {
        bool checking = false;
        while (!checking) {
            if (!checking) {
                while (!infile.eof()) {
                    getline(infile, line);
                    if ((check = line.find(item, 0)) != string::npos) {
                        cout << "\n\t\tbook's information: ";
                        cout << line << "\n";
                    }
                }
            }
        }
    }
    infile.close();
    main_menu();
}
void book_make(){
    cout<<"Enter the text";
    string text;
    cin>>text;
    fstream outfile;
    outfile.open ("C:\\Users\\Partiran\\CLionProjects\\my_code\\text_book.txt",ios:: app);
    outfile <<text<< endl;
    outfile.close();
    administer();
}
void search_in_book(){
    cout<<"\n\t&&&&&&&&&& SEARCH IN BOOK &&&&&&&&&&\n";
    cout<<"\n\t\t>>Please Choose One Option:\n";
    cout<<"\n\t\t1.search word in text\n\n\t\t2.search in text by number\n\n\t\t3.Go to main menu\n\n\t\t4.Close Application\n";
    cout<<"\n\t\tEnter your choice : ";
    int i;
    if(i==1){
        cout<<"\n\t\tEnter the details :-";
        int check;
        string line;
        string  item;
        cin>>item;
        fstream infile;
        infile.open ("C:\\Users\\Partiran\\CLionProjects\\my_code\\text_book.txt",ios:: in);
        if(infile.is_open()) {
            bool checking = false;
            while (!checking) {
                if (!checking) {
                    while (!infile.eof()) {
                        getline(infile, line);
                        if ((check = line.find(item, 0)) != string::npos) {
                            cout << "\n\t\ttext: ";
                            cout << line << "\n";
                        }
                    }
                }
            }
        }
        infile.close();
    }
    else if(i==2) {
        cout<<"\n\t\tEnter the details :-";
        int check;
        string line;
        int item;
        cin >> item;
        int ti=item+1;
        fstream infile;
        infile.open("C:\\Users\\Partiran\\CLionProjects\\my_code\\book_list.txt", ios::in);
        if(infile.is_open()) {
            bool checking = false;
            while (!checking) {
                if (!checking) {
                    while (!infile.eof()) {
                        string pri;
                        getline(infile, pri);
                        if ((check = line.find(item, 0)) != string::npos) {
                            cout << "\n\t\ttext: ";
                            cout<<pri;
                            if ((check = line.find(ti, 0)) != string::npos) {

                                infile.close();
                            }
                        }
                    }
                }
            }
        }

        infile.close();
    }
    else if(i==4)
    {
        system("cls");
        main_menu();
    }
    else if(i==5)
        exit(0);
    else
    {
        cout<<"\n\t\tPlease enter correct option :(";
        getch();
        system("cls");
        main_menu();
    }
    main_menu();
}
void renting(){
    struct book book_adding;
    struct page page_book;
    cout<<"\n\t\tEnter the details :-\n";
    cout<<"\n\t\tEnter Book's Name : ";
    int check;
    string line;
    string  item;
    cin>>item;
    fstream infile;
    infile.open ("C:\\Users\\Partiran\\CLionProjects\\my_code\\exist_book.txt",ios:: in);
    if(infile.is_open()) {
        bool checking = false;
        while (!checking) {
            if (!checking) {
                while (!infile.eof()) {
                    getline(infile, line);
                    if ((check = line.find(item, 0)) != string::npos) {
                        cout << "\n\t\tbook's information: ";
                        cout << line << "\n";
                    }
                }
            }
        }
    }
    infile.close();
    cout<<"\n\t\tEnter the details :-\n";
    cout<<"\n\t\tEnter Book's Name : ";
    string itemi;
    cin>>itemi;
    fstream infiile;
    infiile.open ("C:\\Users\\Partiran\\CLionProjects\\my_code\\exist_book.txt",ios:: app);
    string linei;
    int checki;
    if (infiile.is_open()) {
        bool checking=false;
        while (!checking) {
            if (!checking) {
                while (!infiile.eof()) {
                    getline(infiile, linei);
                    if ((checki = linei.find(itemi, 0)) != string::npos) {
                        linei="";
                        checki = true;
                        break;
                    }
                }

            }
        }
    }
    infiile.close();
    cout << "\n\t\tEnter the details :-\n";
    cout << "\n\t\tEnter Book's Name : ";
    cin >> book_adding.name_book;
    cout << "\n\t\tEnter Author's Name : ";
    cin >> book_adding.author_book;
    cout << "\n\t\tEnter Publication name : ";
    cin >> book_adding.publisher_book;
    cout << "\n\t\tEnter Book's ISBN : ";
    cin >> book_adding.ISBN_book;
    cout << "\n\t\tEnter Book's Year : ";
    cin >> book_adding.year_book;
    cout << "\n\t\tEnter Book's page : ";
    cin >> page_book.number_page;
    fstream outfile;
    outfile.open ("C:\\Users\\Partiran\\CLionProjects\\my_code\\rent_list.txt",ios:: app);
    outfile << book_adding.name_book << ":";
    outfile << book_adding.author_book << ":";
    outfile << book_adding.publisher_book <<":" ;
    outfile << book_adding.ISBN_book << ":";
    outfile << book_adding.year_book << ":";
    outfile << page_book.number_page <<endl;
    outfile<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
    outfile.close();
    main_menu();
}
void rent_list(){
    fstream infile;
    infile.open("C:\\Users\\Partiran\\CLionProjects\\my_code\\rent_list.txt",ios::in);
    if (infile.is_open()){
        string tp;
        while(getline(infile, tp)){
            cout << tp << "\n";
        }
        infile.close();
    }
    main_menu();
}
void exist_book(){
    fstream infile;
    infile.open("C:\\Users\\Partiran\\CLionProjects\\my_code\\exist_book.txt",ios::in);
    if (infile.is_open()){
        string tp;
        while(getline(infile, tp)){
            cout << tp << "\n";
        }
        infile.close();
    }
    main_menu();
}
int main () {
    welcomeMessage();
    main_menu();
    return 0;
}
