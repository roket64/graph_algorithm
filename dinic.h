#ifndef GRAPH_ALGORITHM_DINIC_H
#define GRAPH_ALGORITHM_DINIC_H

#include <vector>
#include <algorithm>
#include "base_structure.h"

template<class NodeType, class FlowType>
class dinic_edge : base_edge<NodeType> {
public:
    typedef FlowType flow_type;
    typedef flow_type *flow_t_pointer;
    typedef flow_type &flow_t_reference;

    typedef typename
    base_edge<NodeType>::node_type node_type;
    typedef typename
    base_edge<NodeType>::node_t_pointer node_t_pointer;
    typedef typename
    base_edge<NodeType>::node_t_reference node_t_reference;
    typedef typename
    base_edge<NodeType>::const_node_t_pointer const_node_t_pointer;

    dinic_edge() :
            base_edge<node_type>(), capacity_(0), flow_(0), reversal_edge_pointer_(nullptr) {};

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
        return this->flow();
    }

private:
    flow_type capacity_;
    flow_type flow_;
    node_t_pointer reversal_edge_pointer_;
};

class dinic {
private:
public:
};

#endif //GRAPH_ALGORITHM_DINIC_H
