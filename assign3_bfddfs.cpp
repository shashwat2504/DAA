#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;

// Display Graph
void display(vector<list<int>> &adj, vector<string> &name, int n) {
    for (int i = 0; i < n; i++) {
        cout << i << "(" << name[i] << ") -> ";
        for (int v : adj[i]) {
            cout << v << "(" << name[v] << ") ";
        }
        cout << endl;
    }
}

// DFS Recursive
void dfsRecursive(int u, vector<list<int>> &adj, vector<string> &name, vector<bool> &vis) {
    cout << u << "(" << name[u] << ") ";
    vis[u] = true;

    for (int v : adj[u]) {
        if (!vis[v]) {
            dfsRecursive(v, adj, name, vis);
        }
    }
}

// DFS Non-Recursive
void dfsNonRecursive(int start, vector<list<int>> &adj, vector<string> &name, int n) {
    vector<bool> vis(n, false);
    stack<int> st;

    st.push(start);

    while (!st.empty()) {
        int u = st.top();
        st.pop();

        if (!vis[u]) {
            cout << u << "(" << name[u] << ") ";
            vis[u] = true;

            for (int v : adj[u]) {
                if (!vis[v]) {
                    st.push(v);
                }
            }
        }
    }
}

// BFS
void bfs(int start, vector<list<int>> &adj, vector<string> &name, int n) {
    vector<bool> vis(n, false);
    queue<int> q;

    q.push(start);
    vis[start] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        cout << u << "(" << name[u] << ") ";

        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;   // VERY IMPORTANT
                q.push(v);
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter number of users: ";
    cin >> n;

    vector<string> name(n);
    vector<list<int>> adj(n);

    // Input names
    for (int i = 0; i < n; i++) {
        cout << "Enter name for ID " << i << ": ";
        cin >> name[i];
    }

    // Input friendships
    int e;
    cout << "Enter number of friendships: ";
    cin >> e;

    for (int i = 0; i < e; i++) {
        int u, v;
        cout << "Enter friendship (u v): ";
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int choice, start;

    do {
        cout << "\n1.Display\n2.DFS Recursive\n3.DFS Non-Recursive\n4.BFS\n5.Exit\n";
        cin >> choice;

        switch (choice) {
            case 1:
                display(adj, name, n);
                break;

            case 2: {
                vector<bool> vis(n, false);
                cout << "Enter start ID: ";
                cin >> start;
                dfsRecursive(start, adj, name, vis);
                cout << endl;
                break;
            }

            case 3:
                cout << "Enter start ID: ";
                cin >> start;
                dfsNonRecursive(start, adj, name, n);
                cout << endl;
                break;

            case 4:
                cout << "Enter start ID: ";
                cin >> start;
                bfs(start, adj, name, n);
                cout << endl;
                break;

            case 5:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice\n";
        }

    } while (choice != 5);

    return 0;
}