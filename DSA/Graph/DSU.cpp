/*
- in CPP union is a keyword, don't use union as func name :)
- Check in this order: find -> unionSet > findOptimized ->unionSetsOptimized
- example application: find cycle in undirected graph
*/

#include <bits/stdc++.h>
using namespace std;

// Optimized using Path compression
int findOptimized(int node, vector<int> &parent){
    if(parent[node] == node)
        return node;

    return parent[node] = findOptimized(parent[node], parent);
}

// For saving height of tree, we're using rank system
void unionSetsOptimized(int node1, int node2, vector<int> &parent, vector<int> rank){
    int parent1 = findOptimized(node1, parent);
    int parent2 = findOptimized(node2, parent);

    if(parent1 == parent2)
        return;

    // Deciding policy acc to rank system
    if(rank[parent1] > rank[parent2]){
        parent[parent2] = parent1;
    } else if(rank[parent1] < rank[parent2]){
        parent[parent1] = parent2;
    } else {
        rank[parent1]++;
        parent[parent2] = parent1;
    }
}

// finds representative of the given node
int find(int node, vector<int> &parent){
    if(parent[node] == node)
        return node;
    
    return find(parent[node], parent); 
}

// combing the two nodes in one set;
void unionSets(int node1, int node2, vector<int> &parent){
    int parent1 = find(node1, parent);
    int parent2 = find(node2, parent);

    if(parent1 == parent2)  // This is very imp, if both in same set, don't do anything
        return;

    // Assumed Policy: bring node2 under node1
    parent[parent2] = parent1;
}

int main(){
    
    unordered_map<int, vector<int>> graph = {
        {0, {1,2}},
        {1, {0,2}},
        {2, {0,1}}
    };
    int V = 3;

    vector<int> parent(V);
    for(int i = 0; i<V; i++)
        parent[i] = i;
    vector<int> rank(V, 0);

    // Application Ex: Detect cycle in this un-directed graph using DSU
    // simple loigic: process each edge, if parent are same, then it's a cycle; if not, then union them

    for(int node = 0; node < V; node++){
        int parent1 = findOptimized(node, parent); 

        for(int neigh: graph[node]){
            if(node < neigh){                 // this is imp, once (node -> neigh) edge is checked, don't check (neigh -> node) edge
            
                int parent2 = findOptimized(neigh, parent);
                if(parent1  == parent2){
                    cout << "Cycle Detected" << endl;
                    return 0;
                }
                unionSetsOptimized(node, neigh, parent, rank);
            }
        }
    }

    return 0;
}