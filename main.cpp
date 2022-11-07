#include "dinic.h"
#include "base_structure.h"

#include <iostream>

int main() {
    auto e1 = flow_edge<>();
    auto e2 = flow_edge<>();
    auto *e1_ptr = &e1;
    auto *e2_ptr = &e2;

    e1.set_reversal(e2_ptr);
    e2.set_reversal(e1_ptr);
    std::cout << e1_ptr << " " << e2_ptr << std::endl;

    return 0;
}
