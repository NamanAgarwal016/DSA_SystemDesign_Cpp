// Implementing map using adjacency list
#include <bits/stdc++.h>
#include <vector>
#include <iostream>
using namespace std;

// void addEdge(vector<vector<int>> &map, int src, int dest) {
// void addEdge(vector<int> map[], int src, int dest) {    // in arrays, it's already pass by reference
void addEdge(unordered_map<int, vector<int>> &graph, int src, int dest) {    // in arrays, it's already pass by reference
    graph[src].push_back(dest);
    graph[dest].push_back(src);
}
int main(){
    int V = 4;

    // vector<vector<int>> map(V, vector<int>());   // correct as well
    // vector<vector<int>> map(V);                  // correct as well
    // vector<int> map[V];                          // correct as well

    unordered_map<int, vector<int>> graph;   // BEST 

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);

    for(int i = 0; i < V; i++){
        cout << i << " -> ";
        for(int j: graph[i])
            cout << j << " ";
        cout << endl;
    }
}