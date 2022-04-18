#include<iostream>
#include<stack>
#include<queue>
#include<unistd.h>

using namespace std;

struct Position {
    int x;
    int y;

    Position (int a = 0, int b = 0) {
        x = a;
        y = b;
    }

    bool operator != (const Position& p) {
        return x != p.x || y != p.y;
    }

    friend ostream& operator << (ostream& os, const Position& p);
};

ostream& operator << (ostream& os, const Position& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

class Graph {
    int N, M;
    vector<vector<char> > matrix;
    Position start;
    int dx[4];
    int dy[4];
    
public:
    
    Graph (int n, int m) {
        N = n;
        M = m;
        matrix = vector<vector<char> > (N, vector<char> (M,'.'));
        dx[0] = -1; dx[1] = 0; dx[2] = 1; dx[3] = 0;
        dy[0] = 0; dy[1] = 1; dy[2] = 0; dy[3] = -1;
    }

    void setMatrix () {
        for (int i = 0; i < N; i++)
		    for (int j = 0; j < M; j++)
                cin >> matrix[i][j];
    }

    void addStartNode (int x, int y) {
        start.x = x;
        start.y = y;
    }

    bool isValid (Position p) {
        return p.x >= 0 && p.y >= 0 && p.x < N && p.y < M && matrix[p.x][p.y] != '#';
    }

    bool isGoal (Position p) {
        return matrix[p.x][p.y] == '$';
    }

    void display () {
        cout << "Maze ->\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++)
                cout << matrix[i][j];
            cout << "\n";
        }

        cout << "\nStart Node: " << start;
    }

    void displayResults (Position start, Position goal, int foundLevel, vector<Position>& order, vector<vector<Position> >& parent) {
        cout << "\n\nStart: " << start;
        cout << "\nOrder: ";
        for (int i = 0; i < order.size(); i++)
            cout << order[i] << " ";
        if (foundLevel != -1) {
            cout << "\nGoal: " << goal;
            cout << "\nGoal found at level " << foundLevel;
            cout << "\nPath: ";
            vector<Position> path;
            for (Position p = goal; p != start; p = parent[p.x][p.y])
                path.push_back(p);
            path.push_back(start);

            for (int i = (int) path.size() - 1; i >= 0; i--)
                cout << path[i] << " ";
        } else {
            cout << "\nGoal not found.";
        }
    }

    int dfs () {
        Position goal;
        stack<Position> open;
        vector<vector<bool> > visited (N, vector<bool> (M, false));
        vector<vector<Position> > parent (N, vector<Position> (M, Position(-1,-1)));
        vector<vector<int> > level (N, vector<int> (M, -1));

        int foundLevel = -1;
        vector<Position> closed;

        open.push(start);
        level[start.x][start.y] = 1;

        while (!open.empty()) {
            Position node = open.top();
            open.pop();

            if(!visited[node.x][node.y]) {
                closed.push_back(node);
                visited[node.x][node.y] = true;
                if (isGoal(node)) {
                    goal = node;
                    foundLevel = level[node.x][node.y];
                    break;
                }
            }

            for (int i = 0; i < 4; i++) {
                Position child(node.x + dx[i], node.y + dy[i]);
                if (isValid(child) && !visited[child.x][child.y]) {
                    if (level[child.x][child.y] == -1) {
                        level[child.x][child.y] = level[node.x][node.y] + 1;
                    }
                    open.push(child);
                    parent[child.x][child.y] = node;
                }
            }
        }

        displayResults(start, goal, foundLevel, closed, parent);
        return foundLevel;
    }

    int bfs () {
        Position goal;
        queue<Position> open;
        vector<vector<bool> > visited (N, vector<bool> (M, false));
        vector<vector<Position> > parent (N, vector<Position> (M, Position(-1,-1)));
        vector<vector<int> > level (N, vector<int> (M, -1));

        int foundLevel = -1;
        vector<Position> closed;

        open.push(start);
        visited[start.x][start.y] =true;

        while (!open.empty()) {
            Position node = open.front();
            open.pop();

            closed.push_back(node);
            
            if (isGoal(node)) {
                goal = node;
                foundLevel = level[node.x][node.y];
                break;
            }

            for (int i = 0; i < 4; i++) {
                Position child(node.x + dx[i], node.y + dy[i]);
                if (isValid(child) && !visited[child.x][child.y]) {
                    visited[child.x][child.y] = true;
                    parent[child.x][child.y] = node;
                    level[child.x][child.y] = level[node.x][node.y] + 1;
                    open.push(child);
                }
            }
        }

        displayResults (start, goal, foundLevel, closed, parent);
        return foundLevel;
    }

    int dls (int limit) {
        Position goal;
        stack<Position> open;
        vector<vector<bool> > visited (N, vector<bool> (M, false));
        vector<vector<Position> > parent (N, vector<Position> (M, Position(-1,-1)));
        vector<vector<int> > level (N, vector<int> (M, -1));

        int foundLevel = -1;
        vector<Position> closed;

        open.push(start);
        level[start.x][start.y] = 1;

        while (!open.empty()) {
            Position node = open.top();
            open.pop();

            if (level[node.x][node.y] > limit)
                break;

            if(!visited[node.x][node.y]) {
                closed.push_back(node);
                visited[node.x][node.y] = true;
                if (isGoal(node)) {
                    goal = node;
                    foundLevel = level[node.x][node.y];
                    break;
                }
            }

            for (int i = 0; i < 4; i++) {
                Position child(node.x + dx[i], node.y + dy[i]);
                if (isValid(child) && !visited[child.x][child.y]) {
                    if (level[child.x][child.y] == -1) {
                        level[child.x][child.y] = level[node.x][node.y] + 1;
                    }
                    open.push(child);
                    parent[child.x][child.y] = node;
                }
            }
        }

        displayResults(start, goal, foundLevel, closed, parent);
        return foundLevel;
    }

    int ids (int max_depth) {
        int foundLevel = -1;
        for (int depth = 1; depth <= max_depth; depth++) {
            cout << "\n\nWith depth limit: " << depth;
            foundLevel = dls(depth);
            if (foundLevel != -1)
                break;
        }
        return foundLevel;
    }

    int bls (int b_limit) {
        Position goal;
        stack<Position> open;
        vector<vector<bool> > visited (N, vector<bool> (M, false));
        vector<vector<Position> > parent (N, vector<Position> (M, Position(-1,-1)));
        vector<vector<int> > level (N, vector<int> (M, -1));

        int foundLevel = -1;
        vector<Position> closed;

        open.push(start);
        level[start.x][start.y] = 1;

        while (!open.empty()) {
            Position node = open.top();
            open.pop();

            if(!visited[node.x][node.y]) {
                closed.push_back(node);
                visited[node.x][node.y] = true;
                if (isGoal(node)) {
                    goal = node;
                    foundLevel = level[node.x][node.y];
                    break;
                }
            }

            for (int i = 0, b_count = 0; i < 4 && b_count < b_limit; i++) {
                Position child(node.x + dx[i], node.y + dy[i]);
                if (isValid(child) && !visited[child.x][child.y]) {
                    if (level[child.x][child.y] == -1) {
                        level[child.x][child.y] = level[node.x][node.y] + 1;
                    }
                    open.push(child);
                    parent[child.x][child.y] = node;
                    b_count++;
                }
            }
        }

        displayResults(start, goal, foundLevel, closed, parent);
        return foundLevel;
    }

    int ibs (int max_blimit) {
        int foundLevel = -1;
        for (int blimit = 1; blimit <= max_blimit; blimit++) {
            cout << "\n\nWith branch limit: " << blimit;
            foundLevel = bls(blimit);
            if (foundLevel != -1)
                break;
        }
        return foundLevel;
    }
};

int main () {
    freopen("mazeIn.txt", "r", stdin);
    freopen("mazeOut.txt", "w", stdout);

    if (isatty(fileno(stdin)))
        cout << "\nEnter no of rows and columns: ";
    int n, m;
    cin >> n >> m;

    Graph g(n, m);

    if (isatty(fileno(stdin)))
        cout << "\nEnter maze (. - path, # - obstacle, $ - goal) -->\n";
    g.setMatrix();

    int startX, startY;
    if (isatty(fileno(stdin)))
        cout << "\nEnter start position (x, y): ";
    cin >> startX >> startY;
    g.addStartNode(startX, startY);

    g.display();

    if (isatty(fileno(stdin)))
        cout << "\n\nChoose search technique -->\n1.DFS 2.BFS 3.DLS 4.IDS 5.BLS 6.IBS\nEnter option: ";
    int op;
    cin >> op;

    int limit = 0;
    if (op > 2 && op < 7) {
        if (isatty(fileno(stdin)))
            cout << "Enter limit: ";
        cin >> limit;
    }

    switch(op) {
        case 1:
        cout << "\n\nDFS -->";
        g.dfs();
        break;

        case 2:
        cout << "\n\nBFS -->";
        g.bfs();
        break;

        case 3:
        cout << "\n\nDLS -->";
        g.dls(limit);
        break;

        case 4:
        cout << "\n\nIDS -->";
        g.ids(limit);
        break;

        case 5:
        cout << "\n\nBLS -->";
        g.bls(limit);
        break;

        case 6:
        cout << "\n\nIBS -->";
        g.ibs(limit);
        break;

        default:
        cout << "\n\nWrong Choice.";
    }

    cout << "\n\n";
    return 0;
}