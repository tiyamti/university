/*In this section, we want to simulate a phone book with the following functionalities:

Retrieve a phone number by entering the contact's name.
Retrieve the contact's name by entering the phone number.
Add a new contact.
The program will continue running until the user selects the exit option.

The code for this program is provided below. Try to complete the missing parts based on the functionality described and submit the completed code.

#include <iostream>
#include <cstring>

using namespace std;

struct Contact {
    // complete this part
    char name[50];
    char number[15];
};

void printContact(Contact contact) {
    cout << "name: " << contact.name << "\nnumber: " << contact.number << '\n';
}

int main() {

    struct Contact phoneBook[100];
    int counter = 0;

    while (true) {

        cout << "1. add new contact\n"
             << "2. find number by name\n"
             << "3. find name by number\n"
             << "4. exit\n";

        int n;
        cin >> n;
        cin.ignore();

        if (n == 1) {

            // complete this part
            if (counter >= 100) {
                cout << "Phone book is full!\n";
            } else {
                Contact newContact;
                cout << "Enter name: ";
                cin.getline(newContact.name, 50);
                cout << "Enter number: ";
                cin.getline(newContact.number, 15);
                phoneBook[counter++] = newContact;
                cout << "Contact added successfully!\n";
            }

        } else if (n == 2) {

            // complete this part
            char name[50];
            cout << "Enter name: ";
            cin.getline(name, 50);

            bool found = false;
            for (int i = 0; i < counter; i++) {
                if (strcmp(phoneBook[i].name, name) == 0) {
                    cout << "Number: " << phoneBook[i].number << '\n';
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Contact not found!\n";
            }

        } else if (n == 3) {

            // complete this part
            char number[15];
            cout << "Enter number: ";
            cin.getline(number, 15);

            bool found = false;
            for (int i = 0; i < counter; i++) {
                if (strcmp(phoneBook[i].number, number) == 0) {
                    cout << "Name: " << phoneBook[i].name << '\n';
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Contact not found!\n";
            }

        } else if (n == 4) {
            return 0;

        } else {
            cout << "error!\n";
        }
    }
}*/
#include <iostream>
#include <cstring>

using namespace std;

struct Contact {
    string namepep;
    string numberpep;
};

void printContact(Contact contact) {
    cout << "name: " << contact.namepep << "\nnumber: " << contact.numberpep << '\n';
}

int main() {

    Contact phoneBookpep[100];
    int counter = 0;

    while (true) {

        cout << "1. add new contact\n"
             << "2. find number by name\n"
             << "3. find name by number\n"
             << "4. exit\n";

        int n;
        cin >> n;
        cin.ignore();

        if (n == 1) {
            cin >> phoneBookpep[counter].namepep;
            cin >> phoneBookpep[counter].numberpep;
            counter++;

        } else if (n == 2) {
            string namef;
            cin >> namef;
            for(int i=0;i<counter;i++){
                if(phoneBookpep[i].namepep==namef)
                    printContact(phoneBookpep[i]);
            }

        } else if (n == 3) {
            string numf;
            cin >> numf;
            for(int j=0;j<counter;j++){
                if(phoneBookpep[j].numberpep==numf)
                    printContact(phoneBookpep[j]);
            }

        } else if (n == 4)
            return 0;

        else
            cout << "error!\n";
    }
}