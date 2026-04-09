/*
Floyd Warshall 
- Multi Source Shortest Path algo
- finds shortest distance b/w every pair of nodes 
- Works for a edge weighted directed graph (if undirected, make directed)
- can have negative edge weights
- can detect negative weight cycles as well.

-Mostly adj matrix is used here, as it's application for heavyily connected grpahs.

Concept:
- check distance between every pair of nodes(u & v) going via every node
- update dist if found shorter distance.
- like if we can go from u --> v, then try going from u --> node --> v, if shorter update adjmatrix[u][v]
- do till every node is chacked for every pair.

Negative cycle deteciom:
- just check, if diagonal elements of the grid are non-zero
- if yes, then it's a negative cycle
- bcoz for any non-negative weight cycle, dist from node to itelf will be 0 always

TC: O(n^3)

https://youtu.be/DzfmJoFq1pc?list=PLpIkg8OmuX-LZB9jYzbbZchk277H5CbdY
*/


#include <bits/stdc++.h>
using namespace std;

void floydWarshall(int V, vector<vector<int>> adjMat) {

    // go via every node
    for(int node = 0; node < V; node++) {

        for(int u = 0; u < V; u++) {
            for(int v = 0; v < V; v++) {
                if(adjMat[u][node] == INT_MAX || adjMat[node][v] == INT_MAX) continue;

                if(adjMat[u][node] + adjMat[node][v] < adjMat[u][v])
                    adjMat[u][v] = adjMat[u][node] + adjMat[node][v];
            }
        }
    }

    for(int i = 0; i < V; i++){
        if(adjMat[i][i] < 0){
            cout << "Negative cycle detetcted" << endl;
            return;
        }
    }

    cout << "shortest dist matrix" << endl;
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            cout << adjMat[i][j] << " ";
        }
        cout << endl;
    }
}

int main(){
    int V = 4;
    vector<vector<int>> adjMatrix = {
        {0, 3, INT_MAX, 7},
        {8, 0, 2, INT_MAX},
        {5, INT_MAX, 0, 1},
        {2, INT_MAX, INT_MAX, 0}
    };

    floydWarshall(V, adjMatrix);
}