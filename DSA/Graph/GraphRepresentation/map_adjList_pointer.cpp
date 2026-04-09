#include <iostream>
using namespace std;

class AdjNode {
public:
    int data;
    AdjNode* next;
    AdjNode(int data){
        this->data = data;
        next = nullptr;
    }
};

class AdjList {
private:
    int V;
    AdjNode** graph;

public:
    AdjList(int V){
        this->V = V;
        graph = new AdjNode*[V];
        for(int i = 0; i < V; i++)
            graph[i] = nullptr;
    }

    void addEdge(int src, int dest){
        AdjNode* node = new AdjNode(dest);
        node->next = graph[src];
        graph[src] = node;
    }

    void printGraph(){
        for(int i = 0; i < V; i++){
            if(graph[i] == nullptr)
                continue;

            cout << i;
            AdjNode* node = graph[i];
            while(node != nullptr){
                cout << " -> " << node->data;
                node = node->next;
            }
            cout << endl;
        }
    }
};

int main(){
    int V = 6;
    AdjList graph(V);
    graph.addEdge(0, 1);
    graph.addEdge(0, 3);
    graph.addEdge(0, 4);
    graph.addEdge(1, 2);
    graph.addEdge(3, 2);
    graph.addEdge(4, 3);

    graph.printGraph();

    return 0;
}