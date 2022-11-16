#ifndef GRAPH_ALGORITHM_DINIC_H
#define GRAPH_ALGORITHM_DINIC_H

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include "base_structure.h"

template<int MAX_V, class Node = int, class Flow = int>
class Dinic : public FlowEdge<Node, Flow> {
public:
private:
    int level[MAX_V];
};

#endif //GRAPH_ALGORITHM_DINIC_H