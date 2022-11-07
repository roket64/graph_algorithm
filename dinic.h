#ifndef GRAPH_ALGORITHM_DINIC_H
#define GRAPH_ALGORITHM_DINIC_H

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "base_structure.h"

template<class NodeType = int, class FlowType = int>
class dinic : public flow_edge<NodeType, FlowType> {
public:
    typedef flow_edge<NodeType, FlowType> *f_edge_pointer;
    typedef flow_edge<NodeType, FlowType> &f_edge_reference;

    /*
     * reuse of types from flow_edge
     */
    typedef typename
    flow_edge<NodeType>::node_t node_t;
    typedef typename
    flow_edge<node_t>::const_node_t const_node_t;

    typedef typename
    flow_edge<node_t>::flow_t flow_t;
    typedef typename
    flow_edge<node_t>::const_flow_t const_flow_t;

    typedef typename
    flow_edge<node_t, flow_t>::edge f_edge;
    typedef typename
    flow_edge<node_t, flow_t>::const_edge const_f_edge;

    typedef typename
    flow_edge<node_t, flow_t>::edge_ptr f_edge_ptr;
    typedef typename
    flow_edge<node_t, flow_t>::const_edge_ptr const_f_edge_ptr;

private:
    std::vector<int> level_;
    std::vector<int> work_;
    std::vector<f_edge> adj_;
    std::vector<f_edge_pointer> adj_ptr_;

    bool can_reach(node_t source, node_t sink) {
        std::fill(level_.begin(), level_.end(), -1);
        std::fill(work_.begin(), work_.end(), 0);
        std::queue<node_t> queue;

        while (!queue.empty()) {
            node_t cur_ = queue.front();
            queue.pop();
            if (cur_ == sink) return true;
            for (auto &edge_: adj_[cur_]) {
                const_node_t next_ = edge_.to();
                if (level_[next_] == -1
                    && edge_.spare() > 0) {
                    queue.push(next_);
                    level_[next_] = level_[cur_] + 1;
                }
            }
        }
    }
};

#endif //GRAPH_ALGORITHM_DINIC_H