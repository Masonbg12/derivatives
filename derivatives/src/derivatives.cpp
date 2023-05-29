// DERIVATIVE CALCULATOR
// Mason Gillespie

// preprocessor directives
#include "LinkedList.h"
#include "Node.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

// function prototypes
void readInEquation(string, LinkedList*, LinkedList*);
void loadTerm(Node*, Node*, string);
void derivative(LinkedList*);

int main()
{
    LinkedList *linked;      // linked list pointer to all terms
    LinkedList *trig;        // linked list holds all trigonometric functions
    ifstream functions;      // input file
    ofstream derive;         // output file
    string equation;         // string to hold new equation from file

    // opening input/output file and validating they were open correctly
    functions.open("functionsExtra_1.txt");
    derive.open("derive.txt");

    if (functions.fail())
        cout << "Input file not found.";
    else if (derive.fail())
        cout << "Output file not found.";
    else
    {
        // while loop iterates until there are no more equations in the
        // input file
        while(getline(functions, equation))
        {
            // creating new linked list object memory allocation
            linked = new LinkedList();
            trig = new LinkedList();

            // calling readInEquation
            readInEquation(equation, linked, trig);

            //cout << *linked << endl << *trig << endl;

            // calling sorting function
            linked->callSort(*trig);

            // calling derivative function
            derivative(linked);

            // printing derivative to output file
            derive << *linked << "\n";

            // deleting linked list allocation
            delete linked;
            delete trig;
         }
    }

    functions.close();
    derive.close();
    return 0;
} // end of main

// readInEquation breaks the string equation into individual terms separated by spaces
void readInEquation(string equation, LinkedList *linked, LinkedList *trig)
{
    string term = " ";  // substring of equation which is a term
    int numOfTerms = 1; // number of terms in equation
    int posOfSpace = 0; // position of the next space in equation

    // removing any "+" from the equation
    while (equation.find("+") != string::npos)
        equation.erase(equation.find("+"), 2);

    // replacing any negative signs in between terms " - " with " -" so the negative
    // will have no space in between the term
    while (equation.find(" - ") != string::npos)
    {
        equation.erase(equation.find(" - "), 1);
        equation.replace(equation.find("- "), 2, (" -"));
    }

    // removing any spaces after cosines
    while (equation.find("s ") != string::npos)
        equation.erase(equation.find("s ") + 1, 1);

    // removing any spaces after tangents
    while (equation.find("n ") != string::npos)
        equation.erase(equation.find("n ") + 1, 1);

    // determining the number of terms based on how many space there are + 1
    for (unsigned int currChar = 0; currChar < equation.length(); currChar++)
        if (equation[currChar] == ' ')
            numOfTerms++;

    // for loop iterates for the total amount of terms
    for (int currTerm = 0; currTerm < numOfTerms; currTerm++)
    {
        posOfSpace = equation.find(" ");              // find the next position of the space
        term = equation.substr(0, posOfSpace);        // substring the next term
        // adding one to either trig LinkedList or exponent (linked) LinkedList
        if (term.find("cos") == string::npos && term.find("sin") == string::npos && term.find("tan") == string::npos)
            ++(*linked);                                  // calling ++ overloaded operator to add empty node to head
        else
            ++(*trig);
        loadTerm(linked->getHead(), trig->getHead(), term);            // calling loadTerm
        equation = equation.substr(posOfSpace + 1);   // removing the term just loading into the linked list
    }
}// end of readInEquations

// loadTerm breaks down the individual terms from readInEquations and loads the members into the linked list
void loadTerm(Node* exponent, Node* trigonometric, string term)
{
    // temporary variables hold various positions of certain terms
    int firstPos = 0;
    int secondPos = 0;

    // loading any members of non-trigonometric terms
    if (term.find("cos") == string::npos && term.find("sin") == string::npos && term.find("tan") == string::npos)
    {
        // checking to see of the term has a fractional coefficient based on indicator "("
        if (term.find("(") != string::npos)
        {
            // string manipulation allows for the numerator and denominator to be extracted from the term
            firstPos = term.find("(");
            secondPos = term.find("/");
            exponent->setNumerator(stoi(term.substr(firstPos + 1, secondPos - firstPos - 1)));      // setting numerator
            firstPos = secondPos;
            secondPos = term.find(")");
            exponent->setDenominator(stoi(term.substr(firstPos + 1, secondPos - firstPos - 1)));    // setting denominator
        }
        // if else statements to extract the coefficient
        else if (term.find("x") == string::npos)                                 // seeing if term is a constant
        {
            exponent->setNumerator(stoi(term));
            return;
        }
        else if (isdigit(term[0]) || (term[0] == '-' && isdigit(term[1])))  // seeing if term has coefficient of not 1
        {
            firstPos = term.find("x");
            exponent->setNumerator(stoi(term.substr(0, firstPos)));
        }
        else if (term[0] == '-' && term[1] == 'x')                          // seeing if term has coefficient of -1
            exponent->setNumerator(-1);
        else                                                                // else, term has numerator of 1
            exponent->setNumerator(1);

        // testing to find out the term's exponent
        if (term.find("^") != string::npos)                                 // exponent of non 0 or 1 exists
        {
            firstPos = term.find("^");
            exponent->setExponent(stoi(term.substr(firstPos + 1)));
        }
        else if (term.find("x") != string::npos)                            // exponent of 1 exists
            exponent->setExponent(1);
    }
    // else, term is a trigonometric function
    else
    {
        // storing the trigonometric function
        if (term.find("cos") != string::npos)
            trigonometric->setTrigFunct("cos");
        else if (term.find("sin") != string::npos)
            trigonometric->setTrigFunct("sin");
        else if (term.find("tan") != string::npos)
            trigonometric->setTrigFunct("tan");

        // temporary string helps with locating other members in term
        string tempFunct = trigonometric->getTrigFunct();

        // checking to see of the term has a fractional coefficient based on indicator "("
        if (term.find("(") != string::npos)
        {
            // string manipulation allows for the numerator and denominator to be extracted from the term
            firstPos = term.find("(");
            secondPos = term.find("/");
            trigonometric->setNumerator(stoi(term.substr(firstPos + 1, secondPos - firstPos - 1)));      // setting numerator
            firstPos = secondPos;
            secondPos = term.find(")");
            trigonometric->setDenominator(stoi(term.substr(firstPos + 1, secondPos - firstPos - 1)));    // setting denominator
        }
        // storing the coefficient
        else if (isdigit(term[0]) || (term[0] == '-' && isdigit(term[1])))       // coefficient is not 1 or -1
        {
            firstPos = term.find(tempFunct);
            trigonometric->setNumerator(stoi(term.substr(0, firstPos)));
        }
        else if (term[0] == '-' && term.find(tempFunct) == 1)               // coefficient is -1
            trigonometric->setNumerator(-1);
        else                                                                // else, coefficient is just 1
            trigonometric->setNumerator(1);

        // storing innerCo
        firstPos = term.find(tempFunct) + 3;

        if (isdigit(term[firstPos]))                                        // inner coefficient is not 1
        {
            secondPos = term.find("x");
            trigonometric->setInnerCo(stoi(term.substr(firstPos, secondPos - firstPos)));
        }
        else                                                                // else inner coefficient is 1
            trigonometric->setInnerCo(1);
    }
}// end of loadTerm

// derivative takes the derivative of each node (term) in the linked list
void derivative(LinkedList *linked)
{
    // temporary pointer to run through the linked list
    Node *currNode = linked->getHead();

    // looping until the end of the linked list is reached
    while (currNode != nullptr)
    {
        // current term is a trigonometric function
        if (currNode->getTrigFunct() != " ")
        {
            // multiplying the numerator by the inner coefficient to get the new numerator
            currNode->setNumerator(currNode->getNumerator() * currNode->getInnerCo());

            // performing trigonometric derivatives based on the trig function
            if (currNode->getTrigFunct() == "cos")
            {
                currNode->setTrigFunct("sin");
                currNode->setNumerator(currNode->getNumerator() * -1);
            }
            else if (currNode->getTrigFunct() == "sin")
                currNode->setTrigFunct("cos");
            else    // trig function is tan
            {
                currNode->setTrigFunct("sec");
                currNode->setExponent(2);
            }
        }
        // current term is non-trigonometric
        else
        {
            if (currNode->getExponent() == 0)           // derivative goes to zero because it is a constant
                currNode->setNumerator(0);
            else if (currNode->getExponent() == 1)      // derivative will become a constant
                currNode->setExponent(0);
            else                                        // taking normal power rule on all other exponent terms
            {
                currNode->setNumerator(currNode->getExponent() * currNode->getNumerator());
                currNode->setExponent(currNode->getExponent() - 1);
            }
        }

        // moving to next node (term) in linked list
        currNode = currNode->getNext();
    }
}// end of derive
