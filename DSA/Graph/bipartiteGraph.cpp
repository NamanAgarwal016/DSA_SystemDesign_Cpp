/*
Logic: 
- simply color the node, then color it's neigh with opposite one
- if found any neigh with same color then it's not bipartite
- simple dfs, color arr with -1 can behave as visited only
- color[neigh] = 1-currColor; simple lgic for reversing the color

Hints for ques:
- dividing/grouping a graph into 2 parts, ahving different properties
*/

#include <bits/stdc++.h>
using namespace std;

bool isBipartiteBfs(unordered_map<int, vector<int>> graph, int src, vector<int> &color){
    queue<int> q;

    color[src] = 1;
    q.push(src);

    while(!q.empty()) {
        int node = q.front();
        int currColor = color[node];
        q.pop();

        for(int neigh: graph[node]){
            if(color[neigh] == -1){
                color[neigh] = 1-currColor;
                q.push(neigh);
            } else if(color[neigh] == currColor){
                return false;
            }
        }
    }
    return true;
}

bool isBipartiteDfs(unordered_map<int, vector<int>> graph, int node, int currColor, vector<int> &color){
    color[node] = currColor;

    for(int neigh: graph[node]){
        if(color[neigh] == -1){
            if(!isBipartiteDfs(graph, neigh, 1 - currColor, color))
                return false;
        }
        else if(color[neigh] == currColor)
            return false;
    }
    return true;

}

int main(){
    // unordered_map<int, vector<int>> graph = {
    //     {0, {1,2}},
    //     {1, {0,2}},
    //     {2, {0,1}}
    // };
    // int V = 3;
    unordered_map<int, vector<int>> graph = {
        {0, {1,3}},
        {1, {0,2}},
        {2, {1,3}},
        {3, {0,2}}
    };
    int V = 4;

    bool isBipartiteFlag = true;
    vector<int> color(V, -1); // not visited: -1, red: 1, green: 0

    for(int i = 0; i < V; i++){
        if(color[i] == -1)
            // if(!isBipartiteDfs(graph, i, 1, color)){
            if(!isBipartiteBfs(graph, i, color)){
                isBipartiteFlag = false;
                break;
            }
    }

    if(!isBipartiteFlag)
        cout << "Not bipartite" << endl;
    else 
        cout << "Yes bipartite" << endl; 
    
}