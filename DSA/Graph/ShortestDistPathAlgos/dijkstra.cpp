/*
Dijkstra's Algorithm
- Works on weighted/unweighted undirected/directed graph
- Can't work for -ve weighted edges (Bellman ford will be used)
- To find shortest distance/path from a given source to all the nodes.
- Differnec b/w BFS and dijkstra: BFS also finds shortest dist, but doesn't take edges' weight in account.

The mistake I always make is:
1. to include visited array, which is not needed & used here.
2. With declaration of array and passing it to func, arr is itself passed as pointer
So, don't put & in func declaration like: int dijkstra(int src, vector<vector<int>> &adj[], int n) : INCORRECT 
3. Size func isonly for vector, not for simple array, so it's necessary to pass no. of nodes.

Time complexity = E*V*log(V)  {logV is the TC for pq.pop() and pq.push()}
*/ 

#include <bits/stdc++.h>
using namespace std;

void dijkstra(int src, vector<vector<int>> adj[], int n) {
    vector<int> minDist(n, INT_MAX);
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;

    vector<int> parent(n, -1);      // for printing shortest path from src to destination

    minDist[src] = 0;
    pq.push({0, src}); // {dist, src}

    while(!pq.empty()){
        int node = pq.top()[1];    // minDist[node] == pq.top()[0]
        pq.pop();

        for(vector<int> edge: adj[node]) {
            int neigh = edge[0];
            int weight = edge[1];
            
            if(minDist[node] + weight < minDist[neigh]) {  
                minDist[neigh] = minDist[node] + weight;
                pq.push({minDist[neigh], neigh});

                parent[neigh] = node;
            }
        }
    }

    // printing shortest path:
    cout << "Shortest path from 0 to n-1 node is: " << endl;
    int i = n-1;
    while(parent[i] != -1) {
        cout << i << " <- ";
        i = parent[i];
    }
    cout << i << endl;

    cout << "Shortest dist from node 0 to n-1 node is: " << minDist[n-1] << endl;
}

int main() {
    // Declare weighted undirected graph
    // adj[src] = {dest, weight}
    vector<vector<int>> adj[] = {
        {{1, 10}, {2, 2}}, 
        {{0, 10}, {3, 20}}, 
        {{0, 2}, {4, 3}},
        {{1, 20}, {4, 1}, {5, 5}},
        {{2, 3}, {3, 1}, {5, 6}},
        {{3, 5}, {4, 6}}
    };

    int src = 0;
    dijkstra(src, adj, 6);
    return 0;
}

