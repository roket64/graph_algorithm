#ifndef GRAPH_ALGORITHM_DINIC_H
#define GRAPH_ALGORITHM_DINIC_H

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include "base_structure.h"

template<class NodeType = int, class FlowType = int>
class dinic : flow_edge<NodeType, FlowType> {
public:
    typedef flow_edge<NodeType, FlowType> edge;
    typedef flow_edge<NodeType, FlowType> *edge_pointer;
    typedef flow_edge<NodeType, FlowType> &edge_reference;

private:
    std::vector<int> level_;
    std::vector<int> work_;
    std::vector<edge> adj_;
};

#endif //GRAPH_ALGORITHM_DINIC_H
