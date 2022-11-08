#ifndef GRAPH_ALGORITHM_DINIC_H
#define GRAPH_ALGORITHM_DINIC_H

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "base_structure.h"

template<class Node = int, class Flow = int>
class dinic : public FlowEdge<Node, Flow> {
public:
    /*
     * reuse of types from flow_edge
     */
    typedef typename
    FlowEdge<Node>::NodeType NodeType;
    typedef typename
    FlowEdge<NodeType>::kNodeType kNodeType;

    typedef typename
    FlowEdge<NodeType>::FlowType FlowType;
    typedef typename
    FlowEdge<NodeType>::kNodeType kFlowType;

    typedef typename
    FlowEdge<NodeType, FlowType>::Edge Edge;
    typedef typename
    FlowEdge<NodeType, FlowType>::kEdge kEdge;

    typedef typename
    FlowEdge<NodeType, FlowType>::pEdge pEdge;
    typedef typename
    FlowEdge<NodeType, FlowType>::kpEdge kpEdge;

private:
    std::vector<int> level_;
    std::vector<int> work_;
    std::vector<Edge> adj_;
    std::vector<pEdge> adj_ptr_;

    bool bfs(NodeType source, NodeType sink) {
        std::fill(level_.begin(), level_.end(), -1);
        std::fill(work_.begin(), work_.end(), 0);
        std::queue<NodeType> queue;

        while (!queue.empty()) {
            NodeType cur_ = queue.front();
            queue.pop();
            if (cur_ == sink) return true;
            for (auto &edge_: adj_[cur_]) {
                kNodeType next_ = edge_.to();
                if (level_[next_] == -1
                    && edge_.spare() > 0) {
                    queue.push(next_);
                    level_[next_] = level_[cur_] + 1;
                }
            }
        }
    }

    FlowType dfs(NodeType cur, NodeType sink, FlowType flow) {
        if (cur == sink) return flow;
        for (auto &i = work_[cur]; i < adj_[cur].size(); ++i) {
            auto next_ = adj_[cur][i];
        }
    }
};

#endif //GRAPH_ALGORITHM_DINIC_H