#ifndef GRAPH_ALGORITHM_BASE_STRUCTURE_H
#define GRAPH_ALGORITHM_BASE_STRUCTURE_H

#include <type_traits>
#include <concepts>

template<class T>
concept mutable_integer = std::is_integral_v<T> && !std::is_const_v<T>;

template<class NodeType = int> requires mutable_integer<NodeType>
class base_edge {
public:
    /*
     * declaration of types in base_edge
     */
    typedef NodeType node_t;
    typedef const node_t const_node_t;

    typedef node_t *node_t_ptr;
    typedef const node_t *const_node_t_ptr;

    typedef node_t &node_t_ref;
    typedef const node_t &const_node_t_ref;

    /*
     * constructors
     */
    base_edge() :
            to_(-1),
            from_(-1) {};

    explicit base_edge(const_node_t to) :
            to_(to),
            from_(-1) {};

    base_edge(const_node_t from, const_node_t to) :
            to_(to),
            from_(from) {};

    /*
     * getter functions
     */
    const_node_t_ref to() const {
        return this->to_;
    }

    const_node_t_ref from() const {
        return this->from_;
    }

private:
    const_node_t from_;
    const_node_t to_;
};

template<class NodeType = int, class FlowType = int> requires mutable_integer<FlowType>
class flow_edge : public base_edge<NodeType> {
public:
    /*
     * reuse of types from base_edge
     */
    typedef typename
    base_edge<NodeType>::node_t node_t;
    typedef typename
    base_edge<NodeType>::const_node_t const_node_t;

    typedef typename
    base_edge<NodeType>::node_t_ptr node_t_ptr;
    typedef typename
    base_edge<NodeType>::const_node_t_ptr const_node_t_ptr;

    typedef typename
    base_edge<NodeType>::node_t_ref node_t_ref;
    typedef typename
    base_edge<NodeType>::const_node_t_ref const_node_t_ref;

    /*
     * declaration of types in flow_edge
     */
    typedef FlowType flow_t;
    typedef const flow_t const_flow_t;

    typedef flow_t *flow_t_ptr;
    typedef const flow_t *const_flow_t_ptr;

    typedef flow_t &flow_t_ref;
    typedef const flow_t &const_flow_t_ref;

    typedef flow_edge<node_t, flow_t> edge;
    typedef const flow_edge<node_t, flow_t> const_edge;

    typedef flow_edge<node_t, flow_t> *edge_ptr;
    typedef const flow_edge<node_t, flow_t> *const_edge_ptr;

    typedef flow_edge<node_t, flow_t> &edge_ref;
    typedef const flow_edge<node_t, flow_t> &const_edge_ref;

    /*
     *  constructors
     */
    flow_edge() :
            base_edge<node_t>(),
            capacity_(0),
            flow_(0),
            reversal_edge_pointer_(nullptr) {};

    explicit flow_edge(const_node_t to) :
            base_edge<node_t>(to),
            capacity_(0),
            flow_(0),
            reversal_edge_pointer_(nullptr) {};

    flow_edge(const_node_t from,
              const_node_t to) :
            base_edge<node_t>(from, to),
            capacity_(0),
            flow_(0),
            reversal_edge_pointer_(nullptr) {};

    flow_edge(const_node_t from,
              const_node_t to,
              const_flow_t capacity) :
            base_edge<node_t>(from, to),
            capacity_(capacity),
            flow_(0),
            reversal_edge_pointer_(nullptr) {};

    flow_edge(const_node_t from,
              const_node_t to,
              const_flow_t capacity,
              edge_ptr reversal) :
            base_edge<node_t>(from, to),
            capacity_(capacity),
            flow_(0),
            reversal_edge_pointer_(reversal) {};

    /*
     *  getter functions
     */
    const_flow_t_ref capacity() const {
        return this->capacity_;
    }

    const_flow_t_ref flow() const {
        return this->flow_;
    }

    flow_t spare() const {
        return this->capacity_ - this->flow_;
    }

    /*
     * setter functions
     */
    void set_capacity(const_flow_t amount) {
        this->capacity_ = amount;
    }

    void set_reversal(edge_ptr reversal) {
        this->reversal_edge_pointer_ = reversal;
    }

    void push_flow(const_flow_t amount) {
        if (this->reversal_edge_pointer_ != nullptr)
            this->reversal_edge_pointer_->flow_ -= amount;
        this->flow_ += amount;
    }

private:
    flow_t capacity_;
    flow_t flow_;
    edge_ptr reversal_edge_pointer_;
};

#endif //GRAPH_ALGORITHM_BASE_STRUCTURE_H
