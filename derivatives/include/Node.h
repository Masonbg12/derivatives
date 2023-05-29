#ifndef NODE_H
#define NODE_H

// preprocessor directives
#include <string>
#include <iostream>

using namespace std;

class Node
{
    public:
        // constructors
        Node();
        Node(int, int, int, int, std::string, Node*);
        Node(const Node&);

        // accessors
        int getInnerCo() const;
        int getNumerator() const;
        int getDenominator() const;
        int getExponent() const;
        std::string getTrigFunct() const;
        Node* getNext() const;

        // mutators
        void setInnerCo(int);
        void setNumerator(int);
        void setDenominator(int);
        void setExponent(int);
        void setTrigFunct(std::string);
        void setNext(Node*);

        // function prototypes
        friend ostream& operator <<(ostream&, Node&);

    private:
        int innerCo;            // holds coefficient inside trig functions
        int numerator;          // holds numerator value
        int denominator;        // holds denominator value
        int exponent;           // holds exponent value
        std::string trigFunct;  // holds trigonometric function
        Node* next;             // holds pointer to next node in linked list
};

#endif // NODE_H
