#ifndef GRAPH_ALGORITHM_BASE_STRUCTURE_H
#define GRAPH_ALGORITHM_BASE_STRUCTURE_H

#include <iostream>
#include <type_traits>
#include <concepts>

template<class T>
concept mutable_integer = std::is_integral_v<T> && !std::is_const_v<T>;

template<class Node = int> requires mutable_integer<Node>
class BaseEdge {
public:
    BaseEdge() :
            from_(0),
            to_(0) {};

    explicit BaseEdge(BaseEdge<> &e) :
            from_(e.from()),
            to_(e.to()) {};

    BaseEdge(Node from, Node to) :
            from_(from),
            to_(to) {};

    const Node &from() const {
        return this->from_;
    }

    const Node &to() const {
        return this->to_;
    }

private:
    Node from_, to_;
};

template<class Node = int, class Flow = int> requires mutable_integer<Flow>
class FlowEdge : public BaseEdge<Node> {
public:
    FlowEdge() :
            BaseEdge<Node>(),
            capacity_(0),
            flow_(0),
            reversal_(nullptr) {};

    explicit FlowEdge(FlowEdge<> &e) :
            BaseEdge<Node>(e.from(), e.to()),
            capacity_(e.capacity()),
            flow_(e.flow()),
            reversal_(e.reversal()) {};

    FlowEdge(Node from,
             Node to) :
            BaseEdge<Node>(from, to),
            capacity_(0),
            flow_(0),
            reversal_(nullptr) {};

    FlowEdge(Node from,
             Node to,
             Flow capacity) :
            BaseEdge<Node>(from, to),
            capacity_(capacity),
            flow_(0),
            reversal_(nullptr) {};

    FlowEdge(Node from,
             Node to,
             Flow capacity,
             FlowEdge<> *reversal) :
            BaseEdge<Node>(from, to),
            capacity_(capacity),
            flow_(0),
            reversal_(reversal) {};

    const Flow &capacity() const {
        return this->capacity_;
    }

    const Flow &flow() const {
        return this->flow_;
    }

    FlowEdge<> *reversal() const {
        return this->reversal_;
    }

    const Flow spare() const {
        return this->capacity_ - this->flow_;
    }

    void set_reversal(FlowEdge<> *e) {
        this->reversal_ = e;
        e->reversal_ = this;
    }

    void push_flow(Flow amount) {
        if (this->reversal_ != nullptr) {
            this->reversal_->flow_ -= amount;
        }
        this->flow_ += amount;
    }

private:
    Flow capacity_, flow_;
    FlowEdge<> *reversal_;
};

#endif //GRAPH_ALGORITHM_BASE_STRUCTURE_H
