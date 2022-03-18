#include<iostream>
#include<fstream>
#include<map>
#include<list>

using namespace std;

class NonTerminal {
public:
    char value;
    char type;

    NonTerminal (char v, char t = 'o') {
        value = v;
        type = t;
    }  

    bool operator == (const NonTerminal &nt) const {
        return value == nt.value && type == nt.type;
    }

    bool operator < (const NonTerminal &nt) const {
        if (value == nt.value)
            return type < nt.type;
        else
            return value < nt.value;
    }

    operator string() {
        string val(1, value);
        if (type == 'o')
            return val;
        else
            return val + "'";
    }
};

class Parser {
    map<NonTerminal, list<string> > grammar;

    string trim (string s) {
        const string WHITESPACE = " \n\r\t\f\v";
        size_t start = s.find_first_not_of(WHITESPACE);
        s = (start == std::string::npos) ? "" : s.substr(start);
        size_t end = s.find_last_not_of(WHITESPACE);
        s = (end == std::string::npos) ? "" : s.substr(0, end + 1);
        return s;
    }

    void tokenize(string s, int start, NonTerminal nt) {
        int end = s.find("|");
        while (end != -1) {
            grammar[nt].push_back(trim(s.substr(start, end - start)));
            start = end + 1;
            end = s.find("|", start);
        }
        grammar[nt].push_back(trim(s.substr(start, end - start)));
    }

public:

    void display () {
        for (map<NonTerminal, list<string> >::iterator it = grammar.begin(); it != grammar.end(); it++) {
            NonTerminal key = it -> first;
            cout << (string)key << " -> ";
            list<string> l = grammar[key];
            for (list<string>::iterator lit = l.begin(); lit != l.end(); lit++) {
                if (lit == next(l.end(), -1))
                    cout << *lit;
                else
                    cout << *lit << " | ";
            }
            cout << "\b\n";
        }
    }

    void getProduction (string prod) {
        int n = prod.length();
        if (n > 0) {
            int i = 0;
            char key = prod[i];
            if (key > 'A' || key < 'Z') {
                NonTerminal nt(key);
                bool flag = false;
                while (i < n) {
                    if (prod[i+1] == '-' && prod[i+2] == '>') {
                        i = i + 3;
                        break;
                    }
                    i++;
                }
                tokenize(prod, i, nt); 
            }
        }
    }

};

int main(int argc, char* argv[]) {
    char* filename = argv[1];
    ifstream fin(filename);

    if (!fin) {
        cout << "File not founnd.\n";
        exit(0);
    }

    string str;
    Parser p;

    while(getline(fin, str)) {
        p.getProduction(str);
    }

    p.display();

    fin.close();

    return 0;
}