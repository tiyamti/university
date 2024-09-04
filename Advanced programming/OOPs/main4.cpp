/*You are required to implement a train management system where each train consists of multiple wagons, and each wagon stores the number of reserved tickets. You will implement two classes: Wagon and Train.
The Wagon class stores the number of booked tickets and a pointer to the next wagon.
The Train class manages a linked list of Wagon objects.
Tasks:
Class Wagon:
Attributes:
bookedTickets: An integer that stores the number of tickets reserved in the wagon.
nextWagon: A pointer to the next Wagon object.
Methods:
setBookedTickets(int bookedTickets): Sets the number of reserved tickets for the current wagon.
getBookedTickets(): Returns the number of reserved tickets for the current wagon.
setNextWagon(Wagon* nextWagon): Sets the pointer to the next wagon.
getNextWagon(): Returns the pointer to the next wagon.
Class Train:
Attributes:
headWagon: A pointer to the first wagon (head of the list).
size: An integer that stores the number of wagons in the train.
Methods:
pushFront(int bookedTickets): Adds a wagon at the front of the train.
printWagons(): Prints the number of reserved tickets for each wagon from the front to the end of the train.
getSize(): Returns the total number of wagons in the train.
Input:
Each input line contains the number of tickets reserved for a wagon. The input ends when the number -1 is entered, which signifies the end of input.
Output:
For each wagon, print the number of reserved tickets starting from the first wagon to the last one (based on the order they were added).
Example Input:
10
4
6
23
100
6
-1
Example Output:
6
100
23
6
4
10*/
#include <iostream>
using namespace std;
class Wagon
{
private:
    int bookedTickets;
    Wagon * nextWagon;
public:
    void setBookedTickets(int bookedTickets){
        this->bookedTickets=bookedTickets;
    }
    int getBookedTickets(){
        return bookedTickets;
    }
    void setNextWagon(Wagon *nextWagon){
        this->nextWagon=nextWagon;
    }
    Wagon * getNextWagon(){
        return nextWagon;
    }
};
class Train
{
private:
    Wagon * headWagon= nullptr;
    int size=0;
public:
    void pushFront(int bookedTickets);
    void printWagons();
    int getSize(){
        return size;
    }
};
void Train::pushFront(int bookedTickets){
    Wagon * tmp= new Wagon;
    tmp->setBookedTickets(bookedTickets);
    tmp->setNextWagon(this->headWagon);
    this->headWagon=tmp;
    size++;

}
void Train::printWagons() {
    Wagon* tmp = this->headWagon;
    do{
        cout << tmp->getBookedTickets() << endl;
        tmp=tmp->getNextWagon();
        size--;
    } while (size!=0);
}
int main() {
    int number_list;
    Train wagon;
    while (true) {
        cin >> number_list;
        if (number_list == -1)
            break;
        else
            wagon.pushFront(number_list);
    }
    wagon.printWagons();
}
