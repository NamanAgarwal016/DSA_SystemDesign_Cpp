/*
Spanning Tree:
- Given a Graph G(V, E), it's subgraph will be called a Spanning tree if these 3 condition follows:
    - It's connected (every node can be reached from every node)
    - that subragph also has all V no. of nodes.
    - No. of edges in that subgraph = V-1
- This will automatically never have a cycle.

Minimum Spanning Tree:
- it's actually minimum WEIGHT spanning tree
- always related with weighted edge.
- MST will be spanning tree of a graph which has least total edge weight.

For finding MST of a given graph, 2 Algos are used:

Prim's Algo
- https://youtu.be/V9gXzD7g8fw?list=PLpIkg8OmuX-LZB9jYzbbZchk277H5CbdY
- Goal: edge we choose should be of min weight, picking greedily (can go greedily as we have to cover all V vertices ultimately)
- for every node we need this info: {weight, node, parent}, and we want min weight to get selected
- Data structure: Min heap
- whjat to put insisde: {weight, node, parent}
- also, once node is processed then we have to mark it has been added in MST, so we will need inMST[]
- no need for an extra visited[]
- This is actually similar to bfs, just with priority queue

Krushkal's Algo:
- https://youtu.be/3tgekNXWXsY?list=PLpIkg8OmuX-LZB9jYzbbZchk277H5CbdY
- VERY SIMPLE
- Logic: we will pick the smallest weight edges first try to join all vertices.
- Step1: Sort edges by weight in ascending order
- Step2: Use DSU to find if two nodes are connected or not
    - if not connected, add in weightSum, and union both nodes
    - if connected, DO NOTHING
*/

#include <bits/stdc++.h>
using namespace std;

typedef vector<int> R;      // aise hi, just to flex

void primsAlgo(int V, unordered_map<int, vector<R>> graph) {
    vector<bool> inMST(V, false);  
    vector<int> parent(V, -1); // only needed if MST needs to be printed

    priority_queue<R, vector<R>, greater<R>> pq;

    pq.push({0, 0, -1});  // {weight, node, parent}

    int sum = 0;

    while(!pq.empty()){
        int node = pq.top()[1];
        int currWeight = pq.top()[0];
        int currParent = pq.top()[2];
        pq.pop();

        if(inMST[node]) continue;       // very imp

        sum += currWeight;
        inMST[node] = true;
        parent[node] = currParent;

        for(auto edge: graph[node]){
            int neigh = edge[0];
            int weight = edge[1];

            if(!inMST[neigh])
                pq.push({weight, neigh, node});
        }
    }

    cout << sum << endl;

    cout << "parent info:" << endl;
    for(int i = 0; i < V; i++){
        cout << i << ": " << parent[i] << endl;
    }
}

int find(int node, vector<int> &parent){
    if(parent[node] == node)
        return node;
    return parent[node] = find(parent[node], parent);
}

void unionSet(int node1, int node2, vector<int> &parent){
    int p1 =  find(node1, parent);
    int p2 = find(node2, parent);

    if(p1 == p2) return;

    parent[p2] = p1;
}

void krushkalsAlgo(int V, unordered_map<int, vector<R>> graph) {
    int sum = 0;

    // from adjList form edgeList first: {Wi, Ui, Vi}
    // TC: O(V+E)
    vector<R> edgeList;
    for(auto itr: graph){               
        int u = itr.first;
        for(auto edge: itr.second){
            int v = edge[0];
            int w = edge[1];
            if(u < v)               // added to remove duplicacy in unidreted graph, remove if directed graph
                edgeList.push_back({w, u, v});
        }
    }

    // TC: O(ElogE)
    sort(edgeList.begin(), edgeList.end());

    // custom sorting, just for revising
    // auto comparator=[](R v1, R v2){
    //     return v1[0] < v2[0];
    // }; 
    // sort(edgeList.begin(), edgeList.end(), comparator);
    

    // Simple DSU
    R parent(V);
    for(int i =0; i < V; i++)
        parent[i] = i;

    // TC: O(E * (4*alpha))   {DSU TC: 4*alpha}
    for(auto edge: edgeList){
        int w = edge[0], u = edge[1], v = edge[2];

        int p1 = find(u, parent);
        int p2 = find(v, parent);

        if(p1 != p2) {
            sum += w;
            unionSet(u, v, parent);
        }
    }

    cout << sum << endl;
}

int main() {
    unordered_map<int, vector<R>> graph = {
        {0, {{1, 50}, {2, 10}}},
        {1, {{0, 50}, {2, 30}}},
        {2, {{0, 10}, {1, 30}}},
    };
    int V = 3;
    // primsAlgo(V, graph);

    krushkalsAlgo(V, graph);
}