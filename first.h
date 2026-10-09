// CSC 453
// Team: Jimmi, Laura, Gloria

#include <sstream>
#include <string>

using namespace std;

//******************************************************************************

//epsilon
const char EPSILON = '&';

//******************************************************************************

// Gloria Yao
struct Production {
    //left part of the production
    char left;
    //right side of the production
    string right;
   
};

class first {
    //Gloria Yao
    private:
        // dynamic array
        Production* productions;
        //nonterminal
        char nonterminals[26]; //all upper case
        //terminal
        char terminals[26]; //all lower case

        int capacity; //capacity of the productions array
        int productionCount;
        int nonTerminalCount;
        int terminalCount;

        char startSymbol;
        set<char> setfirst; // The resulting set from First()

    public:
        first();
        ~first();

        set<char> findFirst(char S); // Performs First() on a given production

        void setStartSymbol();

        bool expand(); //expands array when productions become full

        bool read(); //read the grammar
        bool insert(char left, string right); //insert the grammar to array
        void print(); //print the grammar
        void printFirst(char S, set<char> setfirst); 


};