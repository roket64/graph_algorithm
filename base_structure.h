#ifndef GRAPH_ALGORITHM_BASE_STRUCTURE_H
#define GRAPH_ALGORITHM_BASE_STRUCTURE_H

#include <type_traits>
#include <concepts>

template<class T>
concept mutable_integer = std::is_integral_v<T> && !std::is_const_v<T>;

template<class Node = int> requires mutable_integer<Node>
class BaseEdge {
public:
    /*
     * declaration of types in base_edge
     */
    typedef Node NodeType;
    typedef const NodeType kNodeType;

    typedef NodeType *pNodeType;
    typedef const NodeType *kpNodeType;

    typedef NodeType &rNodeType;
    typedef const NodeType &krNodeType;

    /*
     * constructors
     */
    BaseEdge() :
            to_(-1),
            from_(-1) {};

    explicit BaseEdge(kNodeType to) :
            to_(to),
            from_(-1) {};

    BaseEdge(kNodeType from, kNodeType to) :
            to_(to),
            from_(from) {};

    /*
     * getter functions
     */
    krNodeType to() const {
        return this->to_;
    }

    krNodeType from() const {
        return this->from_;
    }

private:
    kNodeType from_;
    kNodeType to_;
};

template<class Node = int, class Flow = int> requires mutable_integer<Flow>
class FlowEdge : public BaseEdge<Node> {
public:
    /*
     * reuse of types from base_edge
     */
    typedef typename
    BaseEdge<Node>::NodeType NodeType;
    typedef typename
    BaseEdge<NodeType>::kNodeType kNodeType;

    typedef typename
    BaseEdge<NodeType>::pNodeType pNodeType;
    typedef typename
    BaseEdge<NodeType>::kpNodeType kpNodeType;

    typedef typename
    BaseEdge<NodeType>::rNodeType rNodeType;
    typedef typename
    BaseEdge<NodeType>::krNodeType krNodeType;

    /*
     * declaration of types in flow_edge
     */
    typedef Flow FlowType;
    typedef const FlowType kFlowType;

    typedef FlowType *pFlowType;
    typedef const FlowType *kpFlowType;

    typedef FlowType &rFlowType;
    typedef const FlowType &krFlowType;

    typedef FlowEdge<NodeType, FlowType> Edge;
    typedef const FlowEdge<NodeType, FlowType> kEdge;

    typedef FlowEdge<NodeType, FlowType> *pEdge;
    typedef const FlowEdge<NodeType, FlowType> *kpEdge;

    typedef FlowEdge<NodeType, FlowType> &rEdge;
    typedef const FlowEdge<NodeType, FlowType> &krEdge;

    /*
     *  constructors
     */
    FlowEdge() :
            BaseEdge<NodeType>(),
            capacity_(0),
            flow_(0),
            reversal_edge_pointer_(nullptr) {};

    explicit FlowEdge(kNodeType to) :
            BaseEdge<NodeType>(to),
            capacity_(0),
            flow_(0),
            reversal_edge_pointer_(nullptr) {};

    FlowEdge(kNodeType from,
             kNodeType to) :
            BaseEdge<NodeType>(from, to),
            capacity_(0),
            flow_(0),
            reversal_edge_pointer_(nullptr) {};

    FlowEdge(kNodeType from,
             kNodeType to,
             kNodeType capacity) :
            BaseEdge<NodeType>(from, to),
            capacity_(capacity),
            flow_(0),
            reversal_edge_pointer_(nullptr) {};

    FlowEdge(kNodeType from,
             kNodeType to,
             kNodeType capacity,
             pEdge reversal) :
            BaseEdge<NodeType>(from, to),
            capacity_(capacity),
            flow_(0),
            reversal_edge_pointer_(reversal) {};

    /*
     *  getter functions
     */
    krFlowType capacity() const {
        return this->capacity_;
    }

    krFlowType flow() const {
        return this->flow_;
    }

    FlowType spare() const {
        return this->capacity_ - this->flow_;
    }

    /*
     * setter functions
     */
    void set_capacity(kFlowType amount) {
        this->capacity_ = amount;
    }

    void set_reversal(pEdge reversal) {
        this->reversal_edge_pointer_ = reversal;
    }

    void push_flow(kFlowType amount) {
        if (this->reversal_edge_pointer_ != nullptr)
            this->reversal_edge_pointer_->flow_ -= amount;
        this->flow_ += amount;
    }

private:
    FlowType capacity_;
    FlowType flow_;
    pEdge reversal_edge_pointer_;
};

#endif //GRAPH_ALGORITHM_BASE_STRUCTURE_H
