#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;

struct Position {
    int x, y;

    void set (int a, int b) {
        x = a;
        y = b;
    }

    Position (int a = 0, int b = 0) {
        x = a;
        y = b;
    }
};

class Node {
    int board[3][3];
    Position emppos;

    public:

    void set (int a[3][3]) {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) {
                board[i][j] = a[i][j];
                if (board[i][j] == 0)
                    emppos.set(i, j);
            }
    }

    bool check (Position p) {
        return p.x >= 0 && p.x <= 2 && p.y >= 0 && p.y <= 2;
    }

    bool move (int dx, int dy) {
        Position newpos (emppos.x + dx, emppos.y + dy);
        if (check(newpos)) {
            swap(board[newpos.x][newpos.y], board[emppos.x][emppos.y]);
            emppos = newpos;
            return true;
        }
        else
            return false;
    }

    int h (const Node goal) {
        Position hash[9];
        int sum = 0;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                hash[board[i][j]].set(i, j);
        
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) {
                Position p = hash[goal.board[i][j]];
                sum -= abs(i - p.x) + abs (j - p.y);
            }
        
        return sum;
    }

    void display () {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++)
                cout << board[i][j] << " ";
            cout << "\n";
        }
    }
};

bool hillSearch (int start[3][3], int goal[3][3], string &rule) {
    char dir[4] = {'l', 'r', 'u', 'd'};
    int dirX[4] = {0, 0, -1, 1};
    int dirY[4] = {-1, 1, 0 , 0};

    // char dir[4] = {'u', 'd', 'l', 'r'};
    // int dirX[4] = {-1, 1, 0, 0};
    // int dirY[4] = {0 , 0, -1, 1};

    Node curNode, goalNode;

    curNode.set(start);
    cout << "Start state ->\n";
    curNode.display();

    goalNode.set(goal);
    cout << "\nGoal state ->\n";
    goalNode.display();

    int depth_limit = 11;

    cout << "\nIntermediate steps ->\n";

    while (depth_limit--) {
        int m_heur = INT_MIN;
        int m_i = -1, m_j = -1;
        for (int i = 0; i < 4; i++) {
            Node temp = curNode;
            if (temp.move(dirX[i], dirY[i])) {
                int heur = temp.h(goalNode);
                if (heur > m_heur) {
                    m_heur = heur;
                    m_i = i;
                }
            }
        }
        curNode.move(dirX[m_i], dirY[m_i]);
        rule += dir[m_i];
        cout << "\n" << dir[m_i] << "\n";
        curNode.display();
        if (m_heur == 0)
            return true;
    }
    return false;
}

int main () {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int start[3][3], goal[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cin >> start[i][j];

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cin >> goal[i][j];

    string rule = "";

    if (hillSearch(start, goal, rule))
        cout << "\nGoal found.";
    else
        cout << "\nGoal not reacheable.";

    cout << "\nSequence of rules: " << rule << "\n";

    return 0;
}