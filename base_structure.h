#ifndef GRAPH_ALGORITHM_BASE_STRUCTURE_H
#define GRAPH_ALGORITHM_BASE_STRUCTURE_H

#include <iostream>
#include <type_traits>
#include <concepts>

template<class T>
concept integer = std::is_integral_v<T>;

class base_node {
};

template<class NodeType = int> requires integer<NodeType>
class base_edge {
public:
    typedef NodeType node_t;
    typedef const node_t const_node_t;

    typedef node_t *node_t_ptr;
    typedef const node_t *const_node_t_ptr;

    typedef node_t &node_t_ref;
    typedef const node_t &const_node_t_ref;

    //TODO: should remove output text later
    base_edge() : to_(-1), from_(-1) {
        std::cout << "base_edge::base_edge() called uwu\n";
    }

    explicit base_edge(const node_t to) : to_(to), from_(-1) {}

    base_edge(const node_t to, const node_t from) : to_(to), from_(from) {}

    inline node_t to() const {
        return this->to_;
    }

    inline node_t from() const {
        return this->from_;
    }

private:
    node_t to_;
    node_t from_;
};

template<class NodeType = int, class FlowType = int> requires integer<FlowType>
class flow_edge : base_edge<NodeType> {
public:
    typedef FlowType flow_t;
    typedef const flow_t const_flow_t;

    typedef flow_t *flow_type_ptr;
    typedef const flow_t *const_flow_t_ptr;

    typedef flow_t &flow_type_ref;
    typedef const flow_t &const_flow_t_ref;

    typedef flow_edge<NodeType, FlowType> edge;
    typedef flow_edge<NodeType, FlowType> *edge_ptr;
    typedef flow_edge<NodeType, FlowType> &edge_ref;

    typedef typename
    base_edge<NodeType>::node_t node_t;
    typedef typename
    base_edge<NodeType>::node_t_ptr node_t_ptr;
    typedef typename
    base_edge<NodeType>::node_t_ref node_t_ref;

    //TODO: should remove output text later
    flow_edge() :
            base_edge<node_t>(),
            capacity_(0),
            flow_(0),
            reversal_edge_pointer_(nullptr) {
        std::cout << "flow_edge::flow_edge() called uwu\n";
    };

    explicit flow_edge(const node_t to) :
            base_edge<node_t>(to),
            capacity_(0),
            flow_(0),
            reversal_edge_pointer_(nullptr) {};

    flow_edge(const node_t to,
              const node_t from) :
            base_edge<node_t>(to, from),
            capacity_(0),
            flow_(0),
            reversal_edge_pointer_(nullptr) {};

    flow_edge(const node_t to,
              const node_t from,
              const flow_t capacity) :
            base_edge<node_t>(to, from),
            capacity_(0),
            flow_(0),
            reversal_edge_pointer_(nullptr) {};

    flow_edge(const node_t to,
              const node_t from,
              const flow_t capacity,
              node_t_ptr reversal) :
            base_edge<NodeType>(to, from),
            capacity_(capacity),
            flow_(0),
            reversal_edge_pointer_(reversal) {};

    inline flow_type_ref capacity() const {
        return this->capacity_;
    }

    inline flow_type_ref flow() const {
        return this->flow_;
    }

    flow_type_ref spare() const {
        return this->capacity_ - this->flow_;
    }

    void set_capacity(const flow_t amount) {
        this->capacity_ = amount;
    }

    void push_flow(flow_t amount) {
        this->reversal_edge_pointer_->flow_ -= amount;
        this->flow_ += amount;
    }

    void set_reversal(edge_ptr reversal) {
        this->reversal_edge_pointer_ = reversal;
    }

private:
    flow_t capacity_;
    flow_t flow_;
    edge_ptr reversal_edge_pointer_;
};

#endif //GRAPH_ALGORITHM_BASE_STRUCTURE_H
