// Original code by Gonçalo Leão
// Updated by DA 2023/2024 Team

#include "../data_structures/Graph.h"
#include "../data_structures/MutablePriorityQueue.h"
#include "MSTTestAux.h"

template <class T>
std::vector<Vertex<T> *> prim(Graph<T> * g) {
    // Priority queue with all graph vertices
    MutablePriorityQueue<Vertex<T>> q;
    for (auto v : g->getVertexSet()) {
        q.insert(v);
    }


    return g->getVertexSet();
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP3_Ex2, test_prim) {
    Graph<int> graph = createMSTTestGraph<int>();
    std::vector<Vertex<int> *> res = prim(&graph);

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