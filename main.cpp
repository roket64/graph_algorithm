#include "dinic.h"

#include <iostream>

int main() {
    auto edge1 = flow_edge<int, long long>();
    auto edge2 = flow_edge<int, long long>();
    auto *p_edge1 = &edge1;
    auto *p_edge2 = &edge2;

    edge1.set_capacity(10);
    edge2.set_capacity(8);
    std::cout << edge1.capacity() << " " << edge1.flow() << "\n";
    std::cout << edge2.capacity() << " " << edge2.flow() << "\n";

    edge1.set_reversal(p_edge2);
    edge2.set_reversal(p_edge1);
    edge1.push_flow(3);
    edge2.push_flow(3);

    std::cout << edge1.capacity() << " " << edge1.flow() << "\n";
    std::cout << edge2.capacity() << " " << edge2.flow() << "\n";

    return 0;
}
