#ifndef LINKEDLIST_H
#define LINKEDLIST_H

//preprocessor directives
#include "Node.h"

class LinkedList
{
    public:
        // constructors
        LinkedList();
        LinkedList(const LinkedList&);

        // destructor
        ~LinkedList();

        // accessors
        Node* getHead() const;

        // mutators
        void setHead(Node*);

        // function prototypes
        Node* sortExponents(Node*);
        Node* callSort(LinkedList&);
        Node& operator [](const int&) const;
        friend ostream& operator <<(ostream&, const LinkedList&);
        LinkedList operator++();

    private:
        Node* head;     // holds the location of the first node in the linked list
};



#endif // LINKEDLIST_H
