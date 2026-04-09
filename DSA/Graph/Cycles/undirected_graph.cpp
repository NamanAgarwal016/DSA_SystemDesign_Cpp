/*
DFS :
- We can't rely only on visited, as it is undirected
- simply pass a parent variable of the node.
- If neigh is visited, and neigh is not the parent of node, then it is a cycle.

BFS:
- Exactly same concept as dfs 
*/

#include <bits/stdc++.h>
using namespace std;

bool isCyclicDfsUtil(vector<vector<int>> &graph, vector<bool> &visited, int node, int parent) {
    for(int neigh: graph[node]) {
        if(!visited[neigh]) {
            visited[neigh] = true;
            if(isCyclicDfsUtil(graph, visited, neigh, node)) return true;
        } else {
            if(parent != neigh) return true;
        }
    }
    return false;
}

bool isCyclicDfs(vector<vector<int>> &graph) {
    int V = graph.size();

    vector<bool> visited(V, false);

    // For Covering disconnected componets as well
    for(int i = 0; i < V; i++) {
        if(!visited[i]){
            visited[i] = true;
            if(isCyclicDfsUtil(graph, visited, i, -1)) return true;
        }     
    }
    return false;
}

bool isCyclicBfsUtil(vector<vector<int>> &graph, vector<bool> &visited, int node, int parent) {
    queue<pair<int, int>> q;

    q.push({node, parent});

    while(!q.empty()) {
        node = q.front().first;
        parent = q.front().second;
        q.pop();

        for(int neigh: graph[node]) {
            if(!visited[neigh]) {
                visited[neigh] = true;
                q.push({neigh, node});
            } else {
                if(neigh != parent) return true;
            }
        }
    }
    return false;
}


bool isCyclicBfs(vector<vector<int>> &graph) {
    int V = graph.size();

    vector<bool> visited(V, false);

    // For Covering disconnected componets as well
    for(int i = 0; i < V; i++) {
        if(!visited[i]){
            visited[i] = true;
            if(isCyclicBfsUtil(graph, visited, i, -1)) return true;
        }     
    }
    return false;

}

int main(){
    vector<vector<int>> graph = {{1}, {2, 0, 4}, {1, 3}, {2, 4}, {3, 1}};

    cout << isCyclicDfs(graph) << endl;

    cout << isCyclicBfs(graph) << endl;

    return 0;
}