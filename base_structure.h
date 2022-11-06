#ifndef GRAPH_ALGORITHM_BASE_STRUCTURE_H
#define GRAPH_ALGORITHM_BASE_STRUCTURE_H

class base_node {

};

template<class NodeType>
class base_edge {
public:
    typedef NodeType node_type;
    typedef node_type *node_t_pointer;
    typedef const node_type *const_node_t_pointer;
    typedef node_type &node_t_reference;
    typedef const node_type &const_node_t_reference;

    base_edge() : to_(-1), from_(-1) {}

    explicit base_edge(const node_type to) : to_(to), from_(-1) {}

    base_edge(const node_type to, const node_type from) : to_(to), from_(from) {}

    inline node_type to() {
        return this->to_;
    }

    inline node_type from() {
        return this->from_;
    }

private:
    node_type to_;
    node_type from_;
};

#endif //GRAPH_ALGORITHM_BASE_STRUCTURE_H
