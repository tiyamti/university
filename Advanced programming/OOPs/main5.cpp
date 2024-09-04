/*You are required to implement a doubly linked list that can store various types of data such as integers, floating-point numbers, characters, or strings. The linked list should support the following operations:
pushF: Adds an element to the front of the list.
pushB: Adds an element to the back of the list.
popF: Removes the element from the front of the list.
popB: Removes the element from the back of the list.
Finish: Marks the end of operations.
After all operations, the program should print the contents of the list from front to back. If the list is empty, the program should output "Empty."
Input:
First, the type of data stored in the list (e.g., int, float, double, char, or string).
Each subsequent line contains an operation (e.g., pushF, pushB, popF, popB), and for pushF and pushB, the corresponding element to be added.
The input ends when the command Finish is encountered.
Output:
Print the contents of the list from front to back. If the list is empty, output Empty.
Example Input 1:
string
pushF
salam
pushB
Sale
pushF
Hi
pushB
No
popF
popB
pushB
No
pushB
Mobarak
popF
Finish
Example Output 1:
Sale
No
Mobarak*/
#include <iostream>
using namespace std;
template<typename T>
class Node{
private:
    T data;
    Node<T> * nextNode;
    Node<T> * previousNode;
public:
    Node(T data){
        this->data=data;
        this->nextNode=NULL;
        this->previousNode=NULL;
    }
    void setData(T data){
        this->data=data;
    }
    void setNextNode(Node<T> * nextNode){
        this->nextNode=nextNode;
    }
    void setPreviousNode(Node<T> * previousNode){
        this->previousNode=previousNode;
    }
    T getData(){
        return this->data;
    }
    Node * getNextNode(){
        return this->nextNode;
    }
    Node * getPreviousNode(){
        return this->previousNode;
    }
};

template<typename T>
class DoublyLinkedList{
private:
    Node<T> * headNode;
    Node<T> * tailNode;
    int size;
public:
    DoublyLinkedList() {
        headNode = 0 ;
        tailNode= nullptr ;
        this -> size = 0 ;
    }

    ~ DoublyLinkedList() {
        Node<T> * tmp = headNode ;
        while ( this->headNode != 0 ) {
            this->headNode= headNode->getNextNode();
            delete tmp;
            tmp = this->headNode ;
        }
    }
    Node<T> * getHeadNode(){
        return headNode;
    }
    Node<T> * getTailNode(){
        return tailNode;
    }
    void pushFront(T data);
    bool popFront();
    void pushBack(T data);
    bool popBack();
    int getSize(){
        return size;
    }
    void print();
};
//--------------------------
template<typename T>
void DoublyLinkedList<T>::pushFront(T data){
    Node<T> * tmp = new Node<T>(data) ;
    tmp-> setData(data);
    tmp->setNextNode(headNode)  ;
    tmp->setPreviousNode(NULL);
    if(this->headNode!= NULL){
        headNode->setPreviousNode(tmp);
    }
    this->headNode= tmp ;
    if ( tailNode ==NULL) {
        this->tailNode = headNode;
    }
    size++;
}
template<typename T>
bool DoublyLinkedList<T>::popFront(){
    if (size ==0) {
        return false;
    }
    else if (headNode!=NULL) {
        Node<T> *tmp = headNode;
        if (size > 1) {
            headNode = headNode->getNextNode();
            headNode->setPreviousNode(NULL);
        } else {
            this->headNode = NULL;
            this->tailNode = NULL;
        }
        delete tmp;
        size--;
        return true;
    }
}
template<typename T>
void DoublyLinkedList<T>:: pushBack(T data){
    if ( headNode == NULL ) {
        pushFront(data) ;
        return ;
    }
    Node<T> * tmp = new Node<T>(data) ;
    tmp->setNextNode(NULL) ;
    tmp->setData(data) ;
    tmp->setPreviousNode(tailNode);
    if (tailNode!=NULL)
        tailNode->setNextNode(tmp);
    this->tailNode=tmp;
    size++ ;
}
template<typename T>
bool DoublyLinkedList<T>:: popBack(){
    if(size==0) {
        return false;
    }
    else if (tailNode!=NULL){
        Node<T> * tmp=tailNode;
        if (size>1){
            tailNode=tailNode->getPreviousNode();
            tailNode->setNextNode(NULL);
        }
        else{
            this->tailNode=NULL;
            this->headNode=NULL;
        }
        delete tmp;
        size--;
        return true;
    }
}
template<typename T>
void DoublyLinkedList<T>:: print(){
    Node<T> * tmp = headNode;
    while ( tmp ) {
        cout << tmp-> getData() << endl ;
        tmp= tmp->getNextNode() ;
    }
    if (headNode==NULL)
        cout << "Empty" << endl;
}
//--------------------------
int main() {
    string orders,type_data;
    cin >> type_data;
    if (type_data=="string"){
        DoublyLinkedList<string> linkedList;
        string data_string;
        cin >> orders;
        while (orders!="Finish"){
            if (orders=="pushF") {
                cin >> data_string;
                linkedList.pushFront(data_string);
            }
            else if (orders=="pushB"){
                cin >> data_string;
                linkedList.pushBack(data_string);
            }
            else if (orders=="popF")
                linkedList.popFront();
            else if (orders=="popB")
                linkedList.popBack();
            cin >> orders;
        }
        linkedList.print();
    }
    else if (type_data=="int"){
        DoublyLinkedList<int> linkedList;
        int data_int;
        cin >> orders;
        while (orders!="Finish"){
            if (orders=="pushF") {
                cin >> data_int;
                linkedList.pushFront(data_int);
            }
            else if (orders=="pushB"){
                cin >> data_int;
                linkedList.pushBack(data_int);
            }
            else if (orders=="popF")
                linkedList.popFront();
            else if (orders=="popB")
                linkedList.popBack();
            cin >> orders;

        }
        linkedList.print();
    }
    else if (type_data=="char"){
        DoublyLinkedList<char> linkedList;
        char data_char;
        cin >> orders;
        while (orders!="Finish"){
            if (orders=="pushF") {
                cin >> data_char;
                linkedList.pushFront(data_char);
            }
            else if (orders=="pushB"){
                cin >> data_char;
                linkedList.pushBack(data_char);
            }
            else if (orders=="popF")
                linkedList.popFront();
            else if (orders=="popB")
                linkedList.popBack();
            cin >> orders;

        }
        linkedList.print();
    }
    else if (type_data=="float"){
        DoublyLinkedList<float> linkedList;
        float data_float;
        cin >> orders;
        while (orders!="Finish"){
            if (orders=="pushF") {
                cin >> data_float;
                linkedList.pushFront(data_float);
            }
            else if (orders=="pushB"){
                cin >> data_float;
                linkedList.pushBack(data_float);
            }
            else if (orders=="popF")
                linkedList.popFront();
            else if (orders=="popB")
                linkedList.popBack();
            cin >> orders;

        }
        linkedList.print();
    }
    else if (type_data=="double"){
        DoublyLinkedList<double> linkedList;
        double data_double;
        cin >> orders;
        while (orders!="Finish"){
            if (orders=="pushF") {
                cin >> data_double;
                linkedList.pushFront(data_double);
            }
            else if (orders=="pushB"){
                cin >> data_double;
                linkedList.pushBack(data_double);
            }
            else if (orders=="popF")
                linkedList.popFront();
            else if (orders=="popB")
                linkedList.popBack();
            cin >> orders;
        }
        linkedList.print();
    }
    return 0;
}

