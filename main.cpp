#include <iostream>
#include "dinic.h"

int main() {
    auto edge1 = dinic_edge<>();
    auto edge2 = dinic_edge<>();
    auto *p_edge1 = &edge1;
    auto *p_edge2 = &edge2;

    edge1.set_capacity(10);
    edge2.set_capacity(8);
    std::cout << edge1.capacity() << " " << edge1.flow() << "\n";
    std::cout << edge2.capacity() << " " << edge2.flow() << "\n";

    edge1.set_reversal(p_edge2);
    edge2.set_reversal(p_edge1);
    edge1.push_flow(3);
    std::cout << edge1.capacity() << " " << edge1.flow() << "\n";
    std::cout << edge2.capacity() << " " << edge2.flow() << "\n";

    return 0;
}
