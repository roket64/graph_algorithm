#ifndef GRAPH_ALGORITHM_DINIC_H
#define GRAPH_ALGORITHM_DINIC_H

#include <queue> // to use of BFS
#include <algorithm> // to use of std::min
#include <limits> // to use of std::numeric_limits<>::max()
#include "include/base_structure.h"

template<class Node = int, class Flow = int>
class Dinic {
public:
    Dinic() :
            source_(0),
            sink_(0) {};

    Dinic(Node max_v) :
            source_(0),
            sink_(0) {
        level_.resize(max_v + 1);
        work_.resize(max_v + 1);
        adj_.resize(max_v + 1);
    }

    Dinic(Node source,
          Node sink) :
            source_(source),
            sink_(sink) {};

    Dinic(Node source,
          Node sink,
          Node max_v) :
            source_(source),
            sink_(sink) {
        level_.resize(max_v + 1);
        work_.resize(max_v + 1);
        adj_.resize(max_v + 1);
    }

private:
    const Flow INF = std::numeric_limits<Flow>::max();
    Node source_, sink_;

    std::vector<Node> level_;
    std::vector<Node> work_;
    std::vector<std::vector<FlowEdge<> *>> adj_;
};

#endif //GRAPH_ALGORITHM_DINIC_H