// Original code by Gonçalo Leão
// Updated by DA 2023/2024 Team

#include "MSTTestAux.h"
#include "../data_structures/UFDS.h"

template <class T>
void dfsKruskalPath(Vertex<T> *v) {
    for (Edge<T>* e : v->getAdj()) {
        auto n = e->getDest();
        if (n->getPath() == nullptr) {
            n->setPath(v);
            dfsKruskalPath(n);
        }
    }
}

template <class T>
bool sortEdges(Edge<T>* a, Edge<T>* b) {
    return a->getWeight() < b->getWeight();
}

template <class T>
std::vector<Vertex<T> *> kruskal(Graph<T> *g) {
    std::vector<Vertex<T>*> mst;
    std::vector<Edge<T>*> edges;
    for (Vertex<T>* v : g->getVertexSet()) {
        for (auto e : v->getAdj()) {
            edges.push_back(e);
        }
    }
    std::sort(edges.begin(), edges.end(), sortEdges<T>);
    UFDS ufds(g->getNumVertex());

    for (Edge<T>* e : edges) {
        Vertex<T>* u = e->getOrig();
        Vertex<T>* v = e->getDest();

        if (ufds.findSet(u->getInfo()) != ufds.findSet(v->getInfo())) {
            mst.push_back(u);
            mst.push_back(v);
            ufds.linkSets(u->getInfo(), v->getInfo());
        }
    }
    return mst;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP3_Ex3, test_kruskal) {
    Graph<int> graph = createMSTTestGraph<int>();
    std::vector<Vertex<int> *> res = kruskal(&graph);

    std::stringstream ss;
    for(const auto v : res) {
        ss << v->getInfo() << "<-";
        if ( v->getPath() != nullptr ) {
            ss << v->getPath()->getOrig()->getInfo();
        }
        ss << "|";
    }
    std::cout << ss.str() << std::endl;

    EXPECT_TRUE(isSpanningTree(res));
    EXPECT_EQ(spanningTreeCost(res), 11);
}