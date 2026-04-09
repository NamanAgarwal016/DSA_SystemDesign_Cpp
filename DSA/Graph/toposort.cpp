/*
Topological sorting
using DFS : https://youtu.be/5lZ0iJMrUMk?si=_Oq2sB_5hk7_tHUt
 - simply putting node in stack once all its neighs are visited.
 - so that when poped out from stack it gives correct toposort order.
 - exactly same as DFS code, just use stack at the end
 - other way round, first put all child in stack then the parent once

using BFS: 
 - Kahn's algo: https://youtu.be/uVl4ftleTes?list=PLpIkg8OmuX-LZB9jYzbbZchk277H5CbdY
 - form indegree, always a node will be there which have indegree = 0, if not then cyclic
 - put node in queue, start with that.
 - simpley trvaerse it's neigh and decrese indegree of neighs.
 - if indgree of neigh becomes 0, simply push in your queue.
*/

#include <bits/stdc++.h>
using namespace std;

void dfsUtilToposort(vector<vector<int>> &graph, vector<bool> &visited, stack<int> &s, int node){
    visited[node] = true;

    for(int neigh: graph[node]){
        if(!visited[neigh])
            dfsUtilToposort(graph, visited, s, neigh);
    }
    s.push(node);
}

bool dfsUtilCyclic(vector<vector<int>> &graph, vector<bool> &visited, vector<bool> &recStack, int node){
    visited[node] = true;
    recStack[node] = true;

    for(int neigh: graph[node]){
        if(!visited[neigh])
            if(dfsUtilCyclic(graph, visited, recStack, neigh))
                return true;
        else
            if(recStack[neigh])
                return true;
    }
    recStack[node] = false;
    return false;
}

bool isCyclic(vector<vector<int>> &graph){
    int V = graph.size();
    vector<bool> visited(V, false);
    vector<bool> recStack(V, false);

    for(int i = 0; i < V; i++){
        if(!visited[i])
            if(dfsUtilCyclic(graph, visited, recStack, i))
                return true;
    }
    return false;
}

void toposort(vector<vector<int>> &graph){
    
    //first check if it has cycle or not
    if(isCyclic(graph)){
        cout << "Not possible" << endl;
        return;
    } else cout << "Topological sort possible" << endl;

    int V = graph.size();
    vector<bool> visited(V, false);
    stack<int> s;

    for(int i = 0; i < V; i++){
        if(!visited[i])
            dfsUtilToposort(graph, visited, s, i);
    }

    while(!s.empty()){
        cout << s.top() << " ";
        s.pop();
    }
}

void toposortBfs(vector<vector<int>> &graph){
    int V = graph.size();

    // first find and store in-degree of all nodes
    vector<int> indegree(V, 0);
    for(int i = 0; i < V; i++){
        for(int neigh: graph[i]){
            indegree[neigh]++;
        }
    }

    queue<int> q;
    // push nodes with indegree = 0
    for(int i = 0; i < V; i++){
        if(indegree[i] == 0)
            q.push(i);
    }

    while(!q.empty()){
        int node = q.front();
        q.pop();
        cout << node << " ";
        
        for(int neigh: graph[node]){
            indegree[neigh]--;
            if(indegree[neigh] == 0)
                q.push(neigh);
        }
    }
}

int main(){
    vector<vector<int>> graph = {{1}, {2}, {}, {1, 2}};
    toposort(graph);
    cout << endl;
    toposortBfs(graph);
    return 0;
} 