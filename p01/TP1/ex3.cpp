#include "../data_structures/Graph.h"
#include "stack"
using namespace std;

// Helper function to reverse the edges of a directed graph
template <typename T>
void aux_reverseGraphEdges(Graph<T>* g) {
    std::unordered_map<T, vector<T>> reversedAdjList;

    for (const auto& entry : g->adjList) {
        T vertex = entry.first;
        const vector<T>& neighbors = entry.second;

        for (const T& n : neighbors) {
            reversedAdjList[n].push_back(vertex);
        }
    }

    g->adjList = reversedAdjList;
}

// Kosaraju-Sharir algorithm to find strongly connected components
template <typename T>
vector<vector<T>> SCCkosaraju(Graph<T>* g)  {
    vector<vector<T>> sccs;
    //TODO
    return sccs;
}

// First depth-first search in Kosaraju-Sharir algorithm
template <typename T>
void firstDFSKosarajuSharir(Vertex<T> *v, stack<Vertex <T> *> *vertexStack)  {
    v->setVisited(true);
    for (Edge<T> e : v->getAdj()) {
        auto a = e.getDest();
        if(!a->isVisited()) {
            firstDFSKosarajuSharir(a, vertexStack);
        }
    }
    vertexStack->push(v);
}

// Second depth-first search in Kosaraju-Sharir algorithm
template <typename T>
void secondDFSKosarajuSharir(Vertex<T> *v, std::vector<int> & res)  {
    v->setVisited(true);
    res.push_back(v->getInfo());
    for (Edge<T>& e : v->getAdj()) {
        auto a = e.getDest();
        if(!a->isVisited()) {
            secondDFSKosarajuSharir(a, res);
        }
    }
}
