
// preprocessor directives
#include "LinkedList.h"
#include "Node.h"
#include <iostream>

using namespace std;

// default constructor
LinkedList::LinkedList()
{
    head = nullptr;
}

// copy constructor sets calling object's members to argument object's members
LinkedList::LinkedList(const LinkedList& listToCopy)
{
    head = new Node(*listToCopy.getHead()); // setting head to head of copy
    Node* origList = head->getNext();       // temporary pointer for calling object
    Node* copyList = head;                  // temporary pointer for copy object
    Node* tempNode;                         // temporary pointer for new node

    // while loops creates a new node using the copy constructor then
    // moves the pointers to link the new list
    while(origList != nullptr)
    {
        tempNode = new Node(*origList);
        copyList->setNext(tempNode);
        copyList = copyList->getNext();
        origList = origList->getNext();
    }
}

// destructor
LinkedList::~LinkedList()
{
    Node* currNode = head;
    Node* nextNode;

    while(currNode != nullptr)
    {
        nextNode = currNode->getNext();
        delete currNode;
        currNode = nextNode;
    }
}

// head accessor
Node* LinkedList::getHead() const
{
    return head;
}

// head mutator
void LinkedList::setHead(Node* ptr)
{
    head = ptr;
}

// sortExponents receives a linked list that is "out of order" based on the exponent values.
// the function then sorts the nodes based on the exponent values from largest to smallest recursively
Node* LinkedList::sortExponents(Node *head)
{
    Node* maxNode = head;       // biggest exponent next in sort
    Node* prevNode = nullptr;   // previous node before current node being sorted
    Node* currNode = head;      // current node being sorted

    // if there is only one node in linked list return head
    if (head == nullptr || head->getNext() == nullptr)
       return head;

    // bubble sort finds the maximum exponent to be placed in line
    while (currNode->getNext() != nullptr)
    {
        if (currNode->getNext()->getExponent() > maxNode->getExponent())
        {
            maxNode = currNode->getNext();
            prevNode = currNode;
        }

        currNode = currNode->getNext();
    }

    // checking that the maxNode is not already in the right place and the term being moved is not a
    // trig function then switching
    if (maxNode != head && maxNode->getTrigFunct() == " ")
    {
        prevNode->setNext(maxNode->getNext());
        maxNode->setNext(head);
        head = maxNode;
    }

    // recursive call to next node
    head->setNext(sortExponents(head->getNext()));

    // return to calling function
    return head;

}

// calling function to sortExponents() and then returns to calling function, also
// correcting the bubble sort's procedure of switching the trigonometric functions
Node* LinkedList::callSort(LinkedList &trig)
{
    // adding reversed trigonometric functions stored in trig LinkedList
    Node* currNode = trig.getHead();

    // looping through trig list to add node to beginning of list in order they were encountered
    while(currNode != nullptr)
    {
        Node* newNode = new Node(*currNode);

        newNode->setNext(head);

        head = newNode;

        currNode = currNode->getNext();
    }

    // setting head pointer by calling recursive bubble sort
    this->setHead(sortExponents(this->getHead()));

    // returning head
    return head;
}

// bracket overloading function for producing a reference to the node indicated by the integer
// in the brackets
Node& LinkedList::operator [](const int &num) const
{
    Node* tempPtr = this->getHead();

    for (int currNode = 0; currNode < num; currNode++)
        tempPtr = tempPtr->getNext();

    return *tempPtr;
}

// overloading << function calls Node class overloading << function and handles positive and negative
// signs for each term
ostream& operator <<(ostream& os, const LinkedList& linked)
{
    // there is no list then print out error message
    if (linked.getHead() == nullptr)
    {
        os << "Empty list.";
        return os;
    }

    // testing if the entire derivative is zero
    Node* currNode = linked.getHead();
    bool derivativeIsZero = true;

    while(currNode != nullptr)
    {
        if (currNode->getNumerator() != 0)
            derivativeIsZero = false;

        currNode = currNode->getNext();
    }

    // printing out the zero derivative
    if (derivativeIsZero)
    {
        os << "0";
        return os;
    }


    // print out head
    if (linked[0].getNumerator() != 0)
    {
        if ((linked[0].getNumerator() * linked[0].getDenominator()) >= 1)
            os << *linked.getHead();
        else
            os << "-" << *linked.getHead();
    }

    if (linked.getHead()->getNext() == nullptr)
        return os;

    // counter for do while
    int i = 0;

    do
    {
        // update counter
        i++;

        // making sure current and previous terms are not 0
        if (linked[i].getNumerator() != 0 && linked[0].getNumerator() != 0)
        {
            // printing out positives
            if ((linked[i].getNumerator() * linked[i].getDenominator()) >= 1)
                os << " + " << linked[i];
            else    // printing out negatives
                os << " - " << linked[i];
        }
        else if (linked[i].getNumerator() != 0)    // if first term being printed then don't have to worry about sign
            os << linked[i];

    } while (linked[i].getNext() != nullptr);

    // return os
    return os;
}

// prefix ++ overloading function for adding a empty node to the beginning of the linked list
LinkedList LinkedList::operator++()
{
    Node* newNode = new Node;

    newNode->setNext(head);

    head = newNode;

    return *this;
}
