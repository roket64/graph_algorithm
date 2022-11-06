#ifndef GRAPH_ALGORITHM_DINIC_H
#define GRAPH_ALGORITHM_DINIC_H

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include "base_structure.h"

class dinic_node : base_node {
};

template<class NodeType = int, class FlowType = int>
class dinic_edge : base_edge<NodeType> {
public:
    typedef FlowType flow_type;
    typedef flow_type *flow_t_pointer;
    typedef flow_type &flow_t_reference;
    typedef dinic_edge<NodeType, FlowType> edge;
    typedef dinic_edge<NodeType, FlowType> *edge_pointer;
    typedef dinic_edge<NodeType, FlowType> &edge_reference;

    typedef typename
    base_edge<NodeType>::node_type node_type;
    typedef typename
    base_edge<NodeType>::node_t_pointer node_t_pointer;
    typedef typename
    base_edge<NodeType>::node_t_reference node_t_reference;
    typedef typename
    base_edge<NodeType>::const_node_t_pointer const_node_t_pointer;

    dinic_edge() :
            base_edge<node_type>(), capacity_(0), flow_(0), reversal_edge_pointer_(nullptr) {
        std::cout << "dinic_edge::dinic_edge() called uwu\n";
    };

    explicit dinic_edge(const node_type to) :
            base_edge<node_type>(to), capacity_(0), flow_(0), reversal_edge_pointer_(nullptr) {};

    dinic_edge(const node_type to, const node_type from) :
            base_edge<node_type>(to, from), capacity_(0), flow_(0), reversal_edge_pointer_(nullptr) {};

    dinic_edge(const node_type to,
               const node_type from,
               const flow_type capacity) :
            base_edge<node_type>(to, from), capacity_(0), flow_(0), reversal_edge_pointer_(nullptr) {};

    dinic_edge(const node_type to,
               const node_type from,
               const flow_type capacity,
               node_t_pointer reversal) :
            base_edge<NodeType>(to, from), capacity_(capacity), flow_(0), reversal_edge_pointer_(reversal) {};

    inline flow_type capacity() {
        return this->capacity_;
    }

    inline flow_type flow() {
        return this->flow_;
    }

    flow_type spare() {
        return this->capacity_ - this->flow_;
    }

    void set_capacity(const flow_type amount) {
        this->capacity_ = amount;
    }

    void push_flow(flow_type amount) {
        this->reversal_edge_pointer_->flow_ -= amount;
        this->flow_ += amount;
    }

    void set_reversal(edge_pointer reversal) {
        this->reversal_edge_pointer_ = reversal;
    }

private:
    flow_type capacity_;
    flow_type flow_;
    edge_pointer reversal_edge_pointer_;
};

template<class NodeType = int, class FlowType = int>
class dinic : dinic_edge<NodeType, FlowType> {
public:
    typedef dinic_edge<NodeType, FlowType> edge;
    typedef dinic_edge<NodeType, FlowType> *edge_pointer;
    typedef dinic_edge<NodeType, FlowType> &edge_reference;

private:
    std::vector<int> level_;
    std::vector<int> work_;
    std::vector<edge> adj_;
};

#endif //GRAPH_ALGORITHM_DINIC_H
