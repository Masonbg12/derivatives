
// preprocessor directives
#include "Node.h"
#include <string>
#include <math.h>

// default constructor
Node::Node()
{
    innerCo = 0;
    numerator = 0;
    denominator = 1;
    exponent = 0;
    trigFunct = " ";
    next = nullptr;
}

// overloaded constructor
Node::Node(int innerCo, int numerator, int denominator, int exponent, std::string trigFunct, Node* next)
{
    setInnerCo(innerCo);
    setNumerator(numerator);
    setDenominator(denominator);
    setExponent(exponent);
    setTrigFunct(trigFunct);
    setNext(next);
}

// copy constructor sets calling node's members to argument node's members
Node::Node(const Node& copyNode)
{
    setInnerCo(copyNode.getInnerCo());
    setNumerator(copyNode.getNumerator());
    setDenominator(copyNode.getDenominator());
    setExponent(copyNode.getExponent());
    setTrigFunct(copyNode.getTrigFunct());
    setNext(copyNode.getNext());
}

// innerCo accessor
int Node::getInnerCo() const
{
    return innerCo;
}

// innerCo mutator
void Node::setInnerCo(int num)
{
    innerCo = num;
}

// numerator accessor
int Node::getNumerator() const
{
    return numerator;
}

// numerator mutator
void Node::setNumerator(int num)
{
    numerator = num;
}

// denominator accessor
int Node::getDenominator() const
{
    return denominator;
}

// denominator mutator
void Node::setDenominator(int num)
{
    denominator = num;
}

// exponent accessor
int Node::getExponent() const
{
    return exponent;
}

// exponent mutator
void Node::setExponent(int num)
{
    exponent = num;
}

// trigFunct accessor
std::string Node::getTrigFunct() const
{
    return trigFunct;
}

// trigFunct mutator
void Node::setTrigFunct(std::string funct)
{
    trigFunct = funct;
}

// next accessor
Node *Node::getNext() const
{
    return next;
}

// next mutator
void Node::setNext(Node *ptr)
{
    next = ptr;
}

// overloading << function will print out a Node's "term"
ostream& operator <<(ostream& os, Node & n)
{
    if (n.getNumerator() == 0)
        return os;

    // reducing fractions if they can divide into each other
    if (abs(n.getNumerator()) == abs(n.getDenominator()) && n.getNumerator() >= 1)
    {
        if (n.getNumerator() < 1)
            n.setNumerator(-1);
        else
            n.setNumerator(1);

        n.setDenominator(1);
    }
    else if (abs(n.getNumerator()) % abs(n.getDenominator()) == 0)
    {
        n.setNumerator(n.getNumerator() / n.getDenominator());
        n.setDenominator(1);
    }

    // printing out a not trigonometric term with a single x variable
    // comments to right of conditional statement are examples of what is being printed out based on terms
    if (n.getTrigFunct() == " ")
    {
        if (n.getDenominator() != 1 && n.getExponent() != 1)        // print (3/2)x^2
            os << "(" << abs(n.getNumerator()) << "/" << abs(n.getDenominator()) << ")x^" << n.getExponent();
        else if (n.getDenominator() != 1 && n.getExponent() == 1)   // print (3/2)x
            os << "(" << abs(n.getNumerator()) << "/" << abs(n.getDenominator()) << ")x";
        else if (n.getDenominator() != 1 && n.getExponent() == 0)   // print (3/2)
            os << "(" << abs(n.getNumerator()) << "/" << abs(n.getDenominator()) << ")";
        else if (n.getNumerator() != 1 && n.getNumerator() != -1 && n.getExponent() != 1 && n.getExponent() != 0)    // print 3x^2
            os << abs(n.getNumerator()) << "x^" << n.getExponent();
        else if (n.getNumerator() == 1 && n.getExponent() != 0 && n.getExponent() != 1)      // print x^2
            os << "x^"<< n.getExponent();
        else if (n.getNumerator() != 1 && n.getExponent() == 1)      // print 2x
            os << abs(n.getNumerator()) << "x";
        else if ((n.getNumerator() == 1 || n.getNumerator() == -1) && n.getExponent() == 1)     // print x
            os << "x";
        else    // exponent == 0 and there is no fraction, print 2
            os << abs(n.getNumerator());
    }
    else    // printing out trigonometric functions
    {       // comments to right of conditional statement are examples of what is being printed out based on terms
        if (n.getTrigFunct() == "sec" && n.getDenominator() != 1 && n.getInnerCo() != 1)   // print (3/2)sec^2 2x
            os << "(" << abs(n.getNumerator()) << "/" << abs(n.getDenominator()) << ")" << n.getTrigFunct() << "^2 " << n.getInnerCo() << "x";
        else if (n.getTrigFunct() == "sec" && n.getDenominator() != 1)   // print (3/2)sec^2 x
            os << "(" << abs(n.getNumerator()) << "/" << abs(n.getDenominator()) << ")" << n.getTrigFunct() << "^2 " << "x";
        else if (n.getNumerator() != 1 && n.getTrigFunct() == "sec" && n.getInnerCo() != 1)  // print 2sec^2 2x
            os << abs(n.getNumerator()) << n.getTrigFunct() << "^2 " << n.getInnerCo() << "x";
        else if (n.getNumerator() != 1 && n.getTrigFunct() == "sec" && n.getInnerCo() == 1)  // print 2sec^ x
            os << abs(n.getNumerator()) << n.getTrigFunct() << "^2 " << "x";
        else if (n.getTrigFunct() == "sec")  // print sec^2 2x
            os << n.getTrigFunct() << "^2 " << n.getInnerCo() << "x";
        else if (n.getDenominator() != 1 && n.getInnerCo() != 0)          // print (2/3)cos 2x
            os << "(" << abs(n.getNumerator()) << "/" << abs(n.getDenominator()) << ")" << n.getTrigFunct() << " " << n.getInnerCo() << "x";
        else if (n.getDenominator() != 1 && n.getInnerCo() == 1)     // print (2/3)cos x
            os << "(" << abs(n.getNumerator()) << "/" << abs(n.getDenominator()) << ")" << n.getTrigFunct() << " " << "x";
        else if (n.getNumerator() != 1 && n.getNumerator() != -1 && n.getInnerCo() != 1)    // print 2cos 2x
            os << abs(n.getNumerator()) << n.getTrigFunct() << " " << n.getInnerCo() << "x";
        else if (n.getNumerator() != 1 && n.getNumerator() != -1 && n.getInnerCo() == 1)      // print 2cos x
            os << abs(n.getNumerator()) << n.getTrigFunct() << " x";
        else if ((n.getNumerator() == 1 || n.getNumerator() == -1) && n.getInnerCo() != 1)    // cos 2x
            os << n.getTrigFunct() << " " << n.getInnerCo() << "x";
        else // print cos x
            os << n.getTrigFunct() << " x";
    }

    return os;
}
