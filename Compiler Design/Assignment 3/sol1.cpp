#include<iostream>
#include<stack>
#include<fstream>

using namespace std;

class Bracket {
public:
    char type;
    int lineno;
    int colno;
    
    Bracket(char t, int l, int r) {
        type = t;
        lineno = l;
        colno = r;
    }

    void showError() {
        cout << "Error matching '" << type << "' at (Line: " << lineno << ", Col: " << colno << ")\n";
    }
};

// match opening and closing brackets
bool match (char op, char cl) {
    return ((op == '(' && cl == ')') || (op == '{' && cl == '}') || (op == '[' && cl == ']'));
}

int main(int argc, char* argv[]) {
    char* filename = argv[1];
    ifstream fin(filename);

    if (!fin) {
        cout << "File not founnd.\n";
        exit(0);
    }

    int lineno = 1, colno = 1;
    bool flag = true;
    char ch;

    stack<Bracket> s;

    while (!fin.eof()) {
        fin.get(ch);

        // newline: increment line no, reset column no
        if (ch == '\n') {
            lineno++;
            colno = 0;
        }

        // opening braces: push to stack
        else if (ch == '(' || ch == '{' || ch == '[') {
            s.push(Bracket(ch, lineno, colno));
        }

        // closing braces: pop from stack after match or throw error
        else if (ch == ')' || ch == '}' || ch == ']') {
            Bracket b(ch, lineno, colno);
            if (!s.empty() && match(s.top().type, ch)) {
                s.pop();
            }
            else {
                flag = false;
                b.showError();
            }
        }

        // one character read
        colno++;
    }

    // check for unmatched brackets left
    while (!s.empty()) {
        flag = false;
        s.top().showError();
        s.pop();
    }

    if (flag) {
        cout << "Brackets are balanced.\n";
    }

    fin.close();
    return 0;
}