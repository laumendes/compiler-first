//first.cpp

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
int main(int argc, char* argv[]){

    first();

    first grammar;

    grammar.read();

    return 0;
}

