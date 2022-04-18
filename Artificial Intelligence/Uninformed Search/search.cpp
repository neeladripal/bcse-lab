#include<iostream>
#include<stack>
#include<queue>
#include<unistd.h>

using namespace std;

class Graph {
    int N;
    vector<vector<int> > list;
    int start;
    vector<bool> isGoal;

    void printLevel(vector<int> level) {
        cout << "\nLevel: ";
        for (int i = 1; i <= N; i++)
            cout << level[i] << " ";
    }
    
public:
    
    Graph (int n) {
        N = n;
        list = vector<vector<int> > (N+1, vector<int>());
        start = 1;
        isGoal = vector<bool> (N+1, false);
    }

    void addEdge (int u, int v) {
        list[u].push_back(v);
    }

    void addStartNode (int start) {
        this->start = start;
    }

    void addGoalNode (int goalNode) {
        isGoal[goalNode] = true;
    }

    void display () {
        cout << "Adjacency List ->";
        for (int i = 1; i <= N; i++) {
            cout << "\n" << i << ": ";
            for (int j = 0; j < list[i].size(); j++)
                cout << list[i][j] << " ";
        }

        cout << "\n\nStart Node: " << start;
        cout << "\nGoal Nodes: [ ";
        for (int i = 0; i < isGoal.size(); i++)
            if (isGoal[i])
                cout << i << " ";
        cout << "]";
    }

    void displayResults (int start, int goal, int foundLevel, vector<int>& order, vector<int>& parent) {
        cout << "\n\nStart: " << start;
        cout << "\nOrder: ";
        for (int i = 0; i < order.size(); i++)
            cout << order[i] << " ";
        if (foundLevel != -1) {
            cout << "\nGoal: " << goal;
            cout << "\nGoal found at level " << foundLevel;
            cout << "\nPath: ";
            vector<int> path;
            for (int i = goal; i != start; i = parent[i])
                path.push_back(i);
            path.push_back(start);

            for (int i = (int) path.size() - 1; i >= 0; i--)
                cout << path[i] << " ";
        } else {
            cout << "\nGoal not found.";
        }
    }

    int dfs () {
        int goal = -1;
        stack<int> open;
        vector<bool> visited (N+1, false);
        vector<int> parent (N+1, -1);
        vector<int> level (N+1, -1);

        int foundLevel = -1;
        vector<int> closed;

        open.push(start);
        level[start] = 1;

        while (!open.empty()) {
            int node = open.top();
            open.pop();

            if(!visited[node]) {
                closed.push_back(node);
                visited[node] = true;
                if (isGoal[node]) {
                    goal = node;
                    foundLevel = level[node];
                    break;
                }
            }

            for (int i = 0; i < list[node].size(); i++) {
                int child = list[node][i];
                if (!visited[child]) {
                    if (level[child] == -1) {
                        level[child] = level[node] + 1;
                    }
                    open.push(child);
                    parent[child] = node;
                }
            }
        }

        displayResults(start, goal, foundLevel, closed, parent);
        return foundLevel;
    }

    int bfs () {
        int goal = -1;
        queue<int> open;
        vector<bool> visited (N+1, false);
        vector<int> parent (N+1, -1);
        vector<int> level (N+1, -1);

        int foundLevel = -1;
        vector<int> closed;

        open.push(start);
        visited[start] =true;

        while (!open.empty()) {
            int node = open.front();
            closed.push_back(node);
            if (isGoal[node]) {
                goal = node;
                foundLevel = level[node];
                break;
            }
            open.pop();

            for (int i = 0; i < list[node].size(); i++) {
                int child = list[node][i];
                if (!visited[child]) {
                    visited[child] = true;
                    parent[child] = node;
                    level[child] = level[node] + 1;
                    open.push(child);
                }
            }
        }

        displayResults (start, goal, foundLevel, closed, parent);
        return foundLevel;
    }

    int dls (int limit) {
        int goal = -1;
        stack<int> open;
        vector<bool> visited (N+1, false);
        vector<int> parent (N+1, -1);
        vector<int> level (N+1, -1);

        int foundLevel = -1;
        vector<int> closed;

        open.push(start);
        level[start] = 1;

        while (!open.empty()) {
            int node = open.top();
            open.pop();

            if (level[node] > limit)
                continue;

            if(!visited[node]) {
                closed.push_back(node);
                visited[node] = true;
                if (isGoal[node]) {
                    goal = node;
                    foundLevel = level[node];
                    break;
                }
            }

            for (int i = 0; i < list[node].size(); i++) {
                int child = list[node][i];
                if (!visited[child]) {
                    if (level[child] == -1) {
                        level[child] = level[node] + 1;
                    }
                    open.push(child);
                    parent[child] = node;
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
        int goal = -1;
        stack<int> open;
        vector<bool> visited (N+1, false);
        vector<int> parent (N+1, -1);
        vector<int> level (N+1, -1);

        int foundLevel = -1;
        vector<int> closed;

        open.push(start);
        level[start] = 1;

        while (!open.empty()) {
            int node = open.top();
            open.pop();

            if(!visited[node]) {
                closed.push_back(node);
                visited[node] = true;
                if (isGoal[node]) {
                    goal = node;
                    foundLevel = level[node];
                    break;
                }
            }

            for (int i = 0, b_count = 0; i < list[node].size() && b_count < b_limit; i++) {
                int child = list[node][i];
                if (!visited[child]) {
                    if (level[child] == -1) {
                        level[child] = level[node] + 1;
                    }
                    open.push(child);
                    parent[child] = node;
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
    freopen("searchIn.txt", "r", stdin);
    freopen("searchOut.txt", "w", stdout);

    if (isatty(fileno(stdin)))
        cout << "\nEnter no of nodes and edges: ";
    int nodeCount, edgeCount;
    cin >> nodeCount >> edgeCount;

    Graph g(nodeCount);

    if (isatty(fileno(stdin)))
        cout << "\nEnter edges -->\n";
    while (edgeCount--) {
        int a, b;
        cin >> a >> b;
        g.addEdge(a, b);
        g.addEdge(b, a);
    }

    int start, goalNodeCount;
    if (isatty(fileno(stdin)))
        cout << "\nEnter start node: ";
    cin >> start;
    g.addStartNode(start);
    if (isatty(fileno(stdin)))
        cout << "\nEnter no of goal nodes: ";
    cin >> goalNodeCount;

    vector<int> goalNodes (goalNodeCount);
    if (isatty(fileno(stdin)))
        cout << "Enter goal nodes: ";
    for (int i = 0; i < goalNodeCount; i++) {
        int goalNode;
        cin >> goalNode;
        g.addGoalNode(goalNode);
    }

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

    // cout << "\n\nDFS -->";
    // g.dfs();
    // cout << "\n\nBFS -->";
    // g.bfs();
    // cout << "\n\nDLS -->";
    // g.dls(limit);
    // cout << "\n\nIDS -->";
    // g.ids(limit);
    // cout << "\n\nBLS -->";
    // g.bls(limit);
    // cout << "\n\nIBS -->";
    // g.ibs(limit);

    cout << "\n\n";
    return 0;
}