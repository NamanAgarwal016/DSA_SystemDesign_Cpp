/*
Bellman Ford Algo:
- Designed for working on Directed graph (for undirected, convert in directed and use, also wieght of undirected edge shouldn't be -ve)
- Edge weight can be -ve as well <-- main application over dijkstra
- Can detect -ve weight cycle
- No priority Q, no visisted array nothing is used here.
- only edge list is used here.

Concept:
- simply relax the edges V-1 times.
- Relax meaning: updating the node's minDist with the same codn of dijkstra -> if(minDist[node] + weight < minDist[neigh])

Why exactly V-1 times??
- if we're relaxing more than V-1 times, there's no difference in minDist[], it will not change. 
- it has already reahced to min distances, the optimal answer.
- https://youtu.be/5yTkgeTqKK0?list=PLpIkg8OmuX-LZB9jYzbbZchk277H5CbdY

Detecting Negative cycle
- Now, using above fact only:
    if after relaxing for V-1 times, if we go for one more relaxation, and the minDist[] updates, 
    THEN IT MEANS WE HAVE A NEGATIVE CYCLE !!

TC: Simply O(E*V)
*/

#include <bits/stdc++.h>
using namespace std;

void bellmanFord(int src, int dest, int V, vector<vector<int>> edgeList) {
    vector<int> minDist(V, INT_MAX);
    vector<int> parent(V, -1);

    minDist[src] = 0;

    // relaxing all edges V-1 times
    for(int i = 1; i <= V-1; i++) {
        for(auto edge: edgeList) {
            int node = edge[0];
            int neigh = edge[1];
            int weight = edge[2];

            // check if node is reachable or not from src
            if(minDist[node] == INT_MAX) continue;

            if(minDist[node] + weight < minDist[neigh]){
                minDist[neigh] = minDist[node] + weight;
                parent[neigh] = node;
            }
        }
    }

    // Detect -ve cycle, relax onemore time:
    for(auto edge: edgeList) {
        int node = edge[0];
        int neigh = edge[1];
        int weight = edge[2];

        // check if node is reachable or not from src
        if(minDist[node] == INT_MAX) continue;

        if(minDist[node] + weight < minDist[neigh]){        // if any edges turns out to be relaxed, means -ve cycle
            cout << "Negative Cycle detected" << endl;
            return;
        }
    }

    cout << "shortest dist to reach to dest node from src: " << minDist[dest] << endl;

    cout << "shortest path is: " << endl;

    int i = dest;
    while(parent[i] != -1){
        cout << i << " <- ";
        i = parent[i];
    }
    cout << i << endl;
}

int main() {
    unordered_map<int, vector<pair<int, int>>> graph = {        // node1 -> {{neigh1, weigth1}, {neigh2, weight2}}
        {0, {{1, 5}}},
        {1, {{2, -3}, {5, -2}}},
        {2, {{4, 4}}},
        {3, {{2, 7}, {4, -3}}},
        {4, {}},
        {5, {{3, 2}}}
    };
    int V = 6;

    vector<vector<int>> edgeList = {
        {3, 2, 7},
        {5, 3, 2},
        {0, 1, 5},
        {1, 5, -2},
        {1, 2, -3},
        {3, 4, -3},
        {2, 4, 4}
    };

    int src = 0;
    int dest = 4;
    bellmanFord(src, dest, V, edgeList);

    return 0;
}