// Implementing map using adjacency matrix
// #include <bits/stdc++.h>
#include <vector>
#include <iostream>
using namespace std;

void addEdge(vector<vector<int>> &map, int src, int dest){
    map[src][dest] = 1;
    map[dest][src] = 1;
}
int main(){
    int V = 4;

    vector<vector<int>> map(V, vector<int>(V, 0));

    addEdge(map, 0, 1);
    addEdge(map, 0, 2);
    addEdge(map, 2, 3);
    addEdge(map, 1, 2);
    
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}