#include <iostream>
#include "../data_structures/Graph.h"

using namespace std;
template <typename T>

/****************** toposort ********************/
/*
 * Performs a topological sorting of the vertices of a graph.
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */
vector<T> topsort(const Graph<T>* g) {
    vector<T> res;
    queue<Vertex<T>*> Q;
    unordered_set<Vertex<T>*> incoming;

    for (Vertex<T>* v : g->getVertexSet()) {
        bool hasIncoming = false;
        for (const Edge<T>& edge : v->getAdj()) {
            incoming.insert(edge.getDest());
            hasIncoming = true;
        }

        if (!hasIncoming) {
            Q.push(v);
        }
    }

    while (!Q.empty()) {
        Vertex<T>* u = Q.front();
        Q.pop();

        for (const Edge<T>& edge : u->getAdj()) {
            Vertex<T>* v = edge.getDest();
            incoming.erase(v);
            Q.push(v);
        }

        res.push_back(u->getInfo());
    }

    // Se é DAG
    if (!isDAG(g)) {
        return vector<T>();
    }
    return res;
}
