#include <bits/stdc++.h>
using namespace std;

void bfs(vector<vector<int>> &adj, int src){
    int V = adj.size();
    
    vector<bool> visited(V, false);
    queue<int> q;

    visited[src] = true;
    q.push(src);

    while(!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        for(int neigh: adj[node]){
            if(!visited[neigh]){
                visited[neigh] = true;
                q.push(neigh);
            }
        }
    }
}

int main(){
    vector<vector<int>> adj = { {2, 3, 1}, {0}, {0, 4}, {0}, {2}};
    bfs(adj, 0);
    return 0;
}
