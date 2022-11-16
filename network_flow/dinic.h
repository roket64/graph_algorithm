#ifndef GRAPH_ALGORITHM_DINIC_H
#define GRAPH_ALGORITHM_DINIC_H

#include <queue> // to use of BFS
#include <algorithm> // to use of std::min
#include <limits> // to use of std::numeric_limits<>::max()
#include "../include/base_structure.h"

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

    Flow GetMaxFlow(Node source, Node sink) {}

    Flow GetMaxFlow() {}

    void add_edge(Node from,
                  Node to,
                  Flow capacity,
                  bool directional = true) {
        if (directional) {
            FlowEdge<> *forward_edge_ = new FlowEdge<Node, Flow>(from, to, capacity);
            FlowEdge<> *backward_edge_ = new FlowEdge<Node, Flow>(to, from, 0);
            forward_edge_->set_reversal(backward_edge_);
            adj_[from].push_back(forward_edge_);
            adj_[to].push_back(backward_edge_);
        } else {
            FlowEdge<> *forward_edge_ = new FlowEdge<Node, Flow>(from, to, capacity);
            FlowEdge<> *backward_edge_ = new FlowEdge<Node, Flow>(to, from, capacity);
            forward_edge_->set_reversal(backward_edge_);
            adj_[from].push_back(forward_edge_);
            adj_[to].push_back(backward_edge_);
        }
    }

private:
    bool IsReachable() {
        std::fill(level_.begin(), level_.end(), -1);
        std::fill(work_.begin(), work_.end(), 0);

        std::queue<Node> q_;
        q_.push(source_);
        level_[source_] = 0;

        while (!q_.empty()) {
            Node cur_node_ = q_.front();
            q_.pop();

            for (FlowEdge<> *&next_edge_: adj_[cur_node_]) {
                auto next_node_ = next_edge_->to();
                if (next_edge_->spare() < 0
                    || level_[next_node_] != -1)
                    continue;
                level_[next_node_] = level_[cur_node_] + 1;
                q_.push(next_node_);
            }
        }
        return level_[sink_] != -1;
    }

    Flow GetMinFlow(Node cur_node_, Flow cur_flow_) {
        if (cur_node_ == sink_) return cur_flow_;
        for (int &i = work_[cur_node_]; i < adj_[cur_node_].size(); ++i) {
            FlowEdge<> *next_edge_ = adj_[cur_node_][i];
            auto next_node_ = next_edge_->to();
            if (level_[next_node_] == level_[cur_node_] + 1 && next_edge_->spare() > 0) {
                if (Flow min_flow_ =
                        GetMinFlow(next_node_, std::min(next_edge_->spare(), cur_flow_))) {
                    next_edge_->push_flow(min_flow_);
                    return min_flow_;
                }

            }
        }
        return 0;
    }

    const Flow INF = std::numeric_limits<Flow>::max();
    Node source_, sink_;

    std::vector<Node> level_;
    std::vector<Node> work_;
    std::vector<std::vector<FlowEdge<> *>> adj_;
};

#endif //GRAPH_ALGORITHM_DINIC_H