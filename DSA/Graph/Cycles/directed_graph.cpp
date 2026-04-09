/*
DFS :
https://youtu.be/9twcmtQj4DU?list=PLgUwDviBIf0oE3gA41TKO2H5bHpPd7fzn

Why using only visited won't work: take ex:  ADJ LIST: {{1,3}, {2}, {}, {2}}
0->1->2 PATH WILL BE COVERED & MARKED VISITED, but when it will come from 0->3->2 path, it will see 2 as visited, and detect cycle, which is incorrect.

BFS logic of parent node will not work here, take this graph ex: (0) --> (1) <-- (2)
for node 2, parent will be -1, and when it's neigh node 1 is seen as visited & node 1 is not parent of node 2, then cycle will be detected, again incorrect

Logic: on the same path(current recusion), node has to be visited again, then we can have a cycle.
recstack: stores the one particular path
if node is found visited and also in recStack it means on same path, it's tried to be visited again, means a cycle

BFS:
https://youtu.be/iTBaI90lpDQ?list=PLgUwDviBIf0oE3gA41TKO2H5bHpPd7fzn
Logic: Toposort will not work on Directed cyclic graph
While doing toposort we will eventually end up, not having any node left which have indegree = 0, hence q will be empty
maintain a counter and compare with #total nodes at the end
*/

#include <bits/stdc++.h>
using namespace std;

bool dfsUtil(vector<vector<int>> &graph, vector<bool> &visited, vector<bool> &recStack, int node){
    visited[node] = true;
    recStack[node] = true;

    for(int neigh: graph[node]){
        if(visited[neigh] == false){
            if(dfsUtil(graph, visited, recStack, neigh))
                return true;
        } else {
            if(recStack[neigh] == true)
                return true;
        }
    }
    recStack[node] = false;
    return false;
}

bool isCyclicDfs(vector<vector<int>> &graph){
    int V = graph.size();

    vector<bool> visited(V, false);
    vector<bool> recStack(V, false);

    for(int node = 0; node < V; node++)
        if(visited[node] == false)
            if(dfsUtil(graph, visited, recStack, node))
                return true;
    return false;
}

bool isCyclicBfs(vector<vector<int>> &graph){
    int V = graph.size();
    int count = 0;

    // Write toposort
    vector<int> indegree(V, 0);
    for(int i = 0; i < V; i++)
        for(int neigh: graph[i])
            indegree[neigh]++;
    queue<int> q;
    for(int i = 0; i < V; i++)
        if(indegree[i] == 0)
            q.push(i);
    while(!q.empty()){
        int node = q.front();
        q.pop();
        count++;
        for(int neigh: graph[node]){
            indegree[neigh]--;
            if(indegree[neigh] == 0)
                q.push(neigh);
        }
    }

    return !(V == count);
}

int main(){
    vector<vector<int>> graph = {{1, 2}, {2}, {0, 3}, {3}};

    cout << isCyclicDfs(graph) << endl;

    cout << isCyclicBfs(graph) << endl;

    return 0;
}