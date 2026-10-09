//first.cpp

#include <set>
#include <iostream>
#include <sstream>
#include <string>
#include "first.h"

using namespace std;

//******************************************************************************
//Jimmi Antonucci
//constructor
//creates the dynamic array starting with a cap of 5
first::first(){
    capacity = 5; //cap starts at 5
    productionCount = 0; // productions are 0 at time of construction

    productions = new Production[capacity]; //create array for storing productions

    nonTerminalCount = 0;
    terminalCount = 0;
    startSymbol = '\0';
}

//******************************************************************************
//Jimmi Antonucci
//destructor
first::~first(){
    delete[] productions;
}

//******************************************************************************
//Jimmi Antonucci
//expand
bool first::expand(){
    bool rc = false;
    //add to cap
    int newCapacity = capacity + 1;
    //larger array
    Production* newProductions = new Production[newCapacity];
    rc = newProductions != NULL;

    if(rc){
        if(productions){
            //copy
            for(int i = 0; i < productionCount; i++){
                newProductions[i] = productions[i];
            }

            delete[] productions;
        }

        productions = newProductions;
        capacity = newCapacity;
    }
    
    return rc;
}

//******************************************************************************
//Gloria Yao
//insert the one grammar at a time into productions array
bool first::insert(char left, string right){
    //check if the array is full
    bool rc = productionCount < capacity;

    //if the array is full, expand the array
    if (!rc) {
        expand();
        rc = true;
    }

    //if the array is not full, or after expand it, insert the grammar into productions array
    if (rc) {
        productions[productionCount].left = left;
        productions[productionCount].right = right;
        productionCount++;
    }

    return rc;
}

//******************************************************************************
//Gloria Yao
//print the elements in productions array
void first::print() {
    for (int i = 0; i < productionCount; i++) {
        cout << productions[i].left << " -> " << productions[i].right << endl;
    }
}

//******************************************************************************
//Jimmi Antonucci
//takes the first nonterminal as start symbol
void first::setStartSymbol(){
    if(productionCount > 0){
        startSymbol = productions[0].left;
    }
}


//******************************************************************************
//Laura Mendes
// Read the given grammar, store it on the productions array and print the result
bool first::read() {
    // Variables to store the input
    char left;
    string arrow; 
    string right;
    string rightline; // This one stores whole right side before split the stream

    // Executes the statement until we have inputs for the left
    while (cin >> left >> arrow){

        // After storing left and arrow, stores the rest of the line until ';'
        getline(cin, rightline, ';');

        // Creates rightline as a stream
        stringstream ss(rightline);

        // Insert the left and right on the productions with delimitator '|'
        while(getline(ss, right, '|')) {
            insert(left, right);
        }
    }


    // Print the current productions array to confirm it was stored correctly 
    print();

    return true;

}

//******************************************************************************
// Laura Mendes
// Performs First() on the production of a given char and return the resulting set
set<char> first::findFirst(char S) {
    
    // A set of characters resulting from First()
    set<char> setfirst;

    // First of & (epsilon) or a terminal is the set containing itself
    if (S == '&' || (islower(S))) {
        setfirst.insert(S);

    } else {

        // Loops through all of the productions to find the given one
        for (int i = 0; i < productionCount; i++) {
            if (productions[i].left == S) {

                // Checks if the first letter on the right side is lowercase (terminal)
                if (islower(productions[i].right[0])) {

                    // Checks if the letter is not already on the set
                    if(!(setfirst.count(productions[i].right[0]))){
                        // Insert the letter
                        setfirst.insert(productions[i].right[0]);
                    }   
                // Checks if it is an & (epsilon) and inserts it
                } else if (productions[i].right[0] == '&') {
                    setfirst.insert('&');

                // When it finds an uppercase letter (non-terminal)
                } else { 
                    set<char> nonTerminal; 
                    // Recursively calls findFirst with the non-terminal and get its results
                    nonTerminal = findFirst(productions[i].right[0]);
                    // Stores it on the given production resulting set
                    setfirst.insert(nonTerminal.begin(),nonTerminal.end());

                }
                
            }
        }
    }

    // Print the results 
    printFirst(S,setfirst);


    return setfirst;
}

//******************************************************************************
// Laura Mendes
// Prints the set of characters when findFirst is called
void first::printFirst(char S, set<char> setfirst) {

    cout << "First(" << S << ") = {" ;
    // It will print each 
    for (char c : setfirst) {
        cout << c << ","; 
    }
    cout << "}" << endl;

}

//******************************************************************************
// Laura Mendes
int main(int argc, char* argv[]){

    first grammar;
    grammar.read();

    first.findFirst(S);
    first.findFirst()

    return 0;
}

