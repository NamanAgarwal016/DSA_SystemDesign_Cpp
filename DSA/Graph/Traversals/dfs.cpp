#include <bits/stdc++.h>
using namespace std;

void dfsUtil(vector<vector<int>> &adj, int node, vector<bool> &visited){
    // visited[node] = true;
    cout << node << " ";

    for(int neigh: adj[node]){
        if(!visited[neigh]){
            visited[neigh] = true;
            dfsUtil(adj, neigh, visited);
        }
    }
}

void dfs(vector<vector<int>> &adj, int src){
    int V = adj.size(); 

    vector<bool> visited(V, false);
    visited[src] = true;
    dfsUtil(adj, src, visited);
}

// exactly like bfs, just q replaced with stack
// ans with recursion & stack will be different due to order in which neigh are explored
void dfsStack(vector<vector<int>> &adj, int src){
    int V = adj.size();

    vector<bool> visited(V, false);
    stack<int> s;

    visited[src] = true;
    s.push(src);

    while(!s.empty()) {
        int node = s.top();
        s.pop();
        cout << node << " ";

        // For prinitng exactly like recursion:
        // for(int i = adj[node].size() - 1; i >= 0; i--){
        //     int neigh = adj[node][i];
        //     if(visited[neigh] == false){
        //         visited[neigh] = true;
        //         s.push(neigh);
        //     }
        // }
        for(int neigh: adj[node]) {
            if(visited[neigh] == false){
                visited[neigh] = true;
                s.push(neigh);
            }
        }
    }
}

int main(){
    vector<vector<int>> adj = { {1, 2}, {2, 0}, {1, 0, 3, 4}, {2}, {2}};
    dfs(adj, 0);
    cout << endl;
    dfsStack(adj, 0);
    return 0;
}


/*
DFS (Depth-First Search) can produce different answers when implemented recursively versus iteratively with an explicit stack due to 
differences in the order of node exploration. Here’s why:

1. Recursion Uses Implicit Stack (Call Stack)
In a recursive DFS, function calls are pushed onto the call stack by the programming language itself.
The recursive calls are typically made in the order they appear in the code (e.g., left to right for adjacency list traversal).
The last recursive call made is the first to be popped (LIFO behavior).

2. Iterative DFS Uses Explicit Stack (Manually Controlled)
When using an explicit stack, the order in which nodes are pushed determines the traversal order.
The last node pushed is the first one popped (LIFO), just like recursion.
However, if you push neighbors in a different order than the recursive function calls, the exploration sequence may diff


Key Takeaways
Order of pushing matters: Recursive DFS processes nodes in the order they appear in the adjacency list, while iterative DFS depends on push order.
Stack behavior is Last-In-First-Out (LIFO): If you push elements in reverse order in iterative DFS, you can match recursive DFS.
Different traversal orders are valid: DFS doesn't have a unique order; multiple valid DFS traversals exist.

If neighbors are pushed right to left (for (i = adj[node].size() - 1; i >= 0; i--)), the output matches recursion
*/
