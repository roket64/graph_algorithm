#ifndef GRAPH_ALGORITHM_DINIC_H
#define GRAPH_ALGORITHM_DINIC_H

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "base_structure.h"

template<class Node = int, class Flow = int>
class Dinic : public FlowEdge<Node, Flow> {
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

    Dinic() {};

    Dinic(NodeType sz) {
        level_.resize(sz + 1);
        work_.resize(sz + 1);
        adj_.resize(sz + 1);
    }

    FlowType GetMaxFlow(NodeType source, NodeType sink) {
        FlowType ret = 0;
        while (IsReachable(source, sink)) {
            while (FlowType flow = GetMinFlow(source, sink, 0x3f3f3f3f)) {
                ret += flow;
            }
        }
        return ret;
    }

    void add_edge(NodeType from, NodeType to, FlowType capacity) {
        // TODO: this edges must be deallocated later
        pEdge edge = new FlowEdge<>(from, to, capacity);
        pEdge rev = new FlowEdge<>(to, from);
        edge->set_reversal(rev);
        rev->set_reversal(edge);
        adj_[edge->from()].push_back(edge);
        adj_[rev->from()].push_back(rev);
    }

private:
    std::vector<NodeType> level_;
    std::vector<NodeType> work_;
    std::vector<std::vector<pEdge>> adj_;

    void init() {
        std::fill(level_.begin(), level_.end(), -1);
        std::fill(work_.begin(), work_.end(), 0);
    }

    bool IsReachable(kNodeType &source, kNodeType &sink) {
        init();
        std::queue<NodeType> q;
        q.push(source);
        level_[source] = 0;

        while (!q.empty()) {
            NodeType cur = q.front();
            q.pop();
            if (cur == sink) return true;
            for (auto &e: adj_[cur]) {
                auto to_ = e->to();
                if (level_[to_] == -1
                    && e->spare() > 0) {
                    level_[to_] = level_[cur] + 1;
                    q.push(to_);
                }
            }
        }
        return false;
    }

    FlowType GetMinFlow(NodeType cur, NodeType sink, FlowType flow) {
        if (cur == sink) return flow;
        for (int &i = work_[cur]; i < adj_[cur].size(); ++i) {
            auto next = adj_[cur][i];
            auto to_ = next->to();
            if (level_[to_] == level_[cur] + 1 && next->spare() > 0) {
                if (int ret = GetMinFlow(to_, sink, std::min(next->spare(), flow))) {
                    next->push_flow(ret);
                    return ret;
                }
            }
        }
        return 0;
    }
};

#endif //GRAPH_ALGORITHM_DINIC_H