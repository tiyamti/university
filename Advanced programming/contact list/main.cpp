/*Contact Management System
You are tasked with completing the functions and classes in the provided main.cpp file to create a contact management system as a console application. The project has several requirements for class methods and functionalities.

Requirements:
The main function must be able to use all methods of the ContactsList class (in a console-based application).

ContactNode Class:
The ContactNode class should have the following properties:

A constructor to initialize the contact node.
Setter and getter methods for the contact details (name, email, phone number).
ContactsList Class:
The ContactsList class must include the following features:

Constructor: Creates an empty contact list.
Copy Constructor: For creating a copy of the contact list.
Destructor: Frees up the memory used for the list of contacts.
Operator Overloading: Overload operators to perform common operations on the contact list, such as replacement, deletion, and comparison.
Insert Method: A method to insert a new contact while keeping the list sorted alphabetically by name.
Delete Method: A method to delete a contact by their name.
Search Methods: Methods to return contact information based on name, email, or phone number.
Print Method: A method to display the list of contacts in a readable format.
Edit Method: A method to edit a contact's details.
Implementation:
The ContactsList class will use a separate class called ContactNode to store contact information in a linked list format.
Each ContactNode object will store the contact's name, email, phone number, and a pointer to the next ContactNode in the linked list.
The list will be maintained in alphabetical order based on the contact name.
In summary, the project involves building a simple contact management system using object-oriented principles, focusing on linked lists, memory management, and operator overloading for contact management operations.*/
#include <iostream>
#include <string>
using namespace std;

class ContactNode {
private:
    string name;
    string email;
    string phone;
    ContactNode* next;

public:
    ContactNode(string name, string email, string phone) {
        this->name = name;
        this->email = email;
        this->phone = phone;
        this->next = nullptr;
    }

    void setName(string name) { this->name = name; }
    void setEmail(string email) { this->email = email; }
    void setPhone(string phone) { this->phone = phone; }
    void setNext(ContactNode* next) { this->next = next; }

    string getName() { return name; }
    string getEmail() { return email; }
    string getPhone() { return phone; }
    ContactNode* getNext() { return next; }

    friend class ContactsList;
};

class ContactsList {
private:
    ContactNode* head;

public:
    ContactsList() {
        head = nullptr;
    }

    ~ContactsList() {
        ContactNode* current = head;
        while (current != nullptr) {
            ContactNode* next = current->getNext();
            delete current;
            current = next;
        }
    }

    void insertContact(string name, string email, string phone) {
        ContactNode* newContact = new ContactNode(name, email, phone);

        if (head == nullptr || head->getName() > name) {
            newContact->setNext(head);
            head = newContact;
        } else {
            ContactNode* current = head;
            while (current->getNext() != nullptr && current->getNext()->getName() < name) {
                current = current->getNext();
            }
            newContact->setNext(current->getNext());
            current->setNext(newContact);
        }
        cout << "Contact added successfully!\n";
    }

    void deleteContact(string name) {
        if (head == nullptr) {
            cout << "Contact list is empty.\n";
            return;
        }

        if (head->getName() == name) {
            ContactNode* toDelete = head;
            head = head->getNext();
            delete toDelete;
            cout << "Contact deleted successfully!\n";
            return;
        }

        ContactNode* current = head;
        while (current->getNext() != nullptr && current->getNext()->getName() != name) {
            current = current->getNext();
        }

        if (current->getNext() == nullptr) {
            cout << "Contact not found.\n";
        } else {
            ContactNode* toDelete = current->getNext();
            current->setNext(toDelete->getNext());
            delete toDelete;
            cout << "Contact deleted successfully!\n";
        }
    }

    void searchContact(string name) {
        ContactNode* current = head;
        while (current != nullptr) {
            if (current->getName() == name) {
                cout << "Contact Found:\n";
                cout << "Name: " << current->getName() << "\nEmail: " << current->getEmail() << "\nPhone: " << current->getPhone() << endl;
                return;
            }
            current = current->getNext();
        }
        cout << "Contact not found.\n";
    }

    void editContact(string name) {
        ContactNode* current = head;
        while (current != nullptr) {
            if (current->getName() == name) {
                string newName, newEmail, newPhone;
                cout << "Enter new name: ";
                cin >> newName;
                cout << "Enter new email: ";
                cin >> newEmail;
                cout << "Enter new phone: ";
                cin >> newPhone;

                current->setName(newName);
                current->setEmail(newEmail);
                current->setPhone(newPhone);
                cout << "Contact updated successfully!\n";
                return;
            }
            current = current->getNext();
        }
        cout << "Contact not found.\n";
    }

    void printContacts() {
        if (head == nullptr) {
            cout << "Contact list is empty.\n";
            return;
        }

        ContactNode* current = head;
        cout << "Contacts List:\n";
        while (current != nullptr) {
            cout << "Name: " << current->getName() << "\nEmail: " << current->getEmail() << "\nPhone: " << current->getPhone() << endl;
            current = current->getNext();
        }
    }
};

int main() {
    ContactsList contacts;
    int choice;
    string name, email, phone;

    do {
        cout << "\n--- Contact Management System ---\n";
        cout << "1. Add Contact\n";
        cout << "2. Delete Contact\n";
        cout << "3. Search Contact\n";
        cout << "4. Edit Contact\n";
        cout << "5. View All Contacts\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter email: ";
                cin >> email;
                cout << "Enter phone: ";
                cin >> phone;
                contacts.insertContact(name, email, phone);
                break;
            case 2:
                cout << "Enter name to delete: ";
                cin >> name;
                contacts.deleteContact(name);
                break;
            case 3:
                cout << "Enter name to search: ";
                cin >> name;
                contacts.searchContact(name);
                break;
            case 4:
                cout << "Enter name to edit: ";
                cin >> name;
                contacts.editContact(name);
                break;
            case 5:
                contacts.printContacts();
                break;
            case 0:
                cout << "Exiting the system.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
