#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

const string WHITESPACE = " \n\r\t\f\v";

// trim a string of whitespaces
string ltrim(const string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == string::npos) ? "" : s.substr(start);
}

class Parser {
    unordered_map<char, vector<string> > grammar;
    char startSymbol;

    int recursiveParse(char symbol, int index, string const &s, vector<string> &derivations) const {
        // if end of string is reached
        if (index > s.size())
            return -1;

        // if the encountered symbol does not exist in grammar
        // if symbol matches with character at current input string index, increment input string index by 1
        // else syntax error
        if (grammar.find(symbol) == grammar.end())
            return s[index] == symbol ? index + 1 : -1;

        vector<string> productionList = grammar.at(symbol);

        // for all the productions of the current non-terminal
        for (vector<string>::const_iterator prod = productionList.begin(); prod != productionList.end(); prod++) {
            string production = *prod;
            
            // reset cursor to input string index for a new production
            int cursor = index;
            derivations.push_back(string(1,symbol) + " -> " + production);

            // iterate through the symbols of the current production
            for (string::iterator it = production.begin(); it != production.end(); it++) {
                cursor = recursiveParse(*it, cursor, s, derivations);
                
                // if at some stage, mismatch occurs or cursor goes out of input string
                if (cursor == -1)
                    break;
            }
            
            if (cursor == -1)
                derivations.pop_back();
            else
                return cursor;          // if the current production is valid
        }

        // if no productions are valid
        return -1;
    };

public:
    // get the start symbol and the productions
    // sample input
    // E
    // 3
    // E iF
    // F +iF
    // F
    // i+i+i
    void input() {
        cin >> startSymbol;
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            char symbol;
            cin >> symbol;
            string production;
            getline(cin, production);
            grammar[symbol].push_back(ltrim(production));
        }
    };

    // parse the string
    vector<string> parse(string s) const {
        vector<string> derivations;
        int endIndex = recursiveParse(startSymbol, 0, s, derivations);
        if (s.size() != endIndex) {
            cerr << "Syntax Error\n";
            return vector<string>();
        }
        return derivations;
    };
};

int main() {
    // Non-terminals - uppercase
    // Terminals - lowercase
    // Eplison - ''

    // feed the productions and start symbol into the parser
    Parser parser;
    parser.input();

    // take the test string as input
    string s;
    cin >> s;

    // get the derivations after parsing that lead the start symbol to the string
    vector<string> derivations = parser.parse(s);
    for (int i = 0; i < derivations.size(); i++) {
        cout << derivations[i] << endl;
    }

    return 0;
}