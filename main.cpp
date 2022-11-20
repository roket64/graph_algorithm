#include "include/base_structure.h"
#include "network_flow/dinic.h"
#include <iostream>
#include <bitset>

using namespace std;

vector<vector<FlowEdge<> *>> adj(5);

int main() {
    auto *e1 = new FlowEdge<>(1, 2, 1);
    auto *e2 = new FlowEdge<>(1, 3, 1);
    auto *e3 = new FlowEdge<>(2, 4, 1);
    auto *e4 = new FlowEdge<>(3, 4, 1);

    auto *r1 = new FlowEdge<>(2, 1);
    e1->set_reversal(r1);
    auto *r2 = new FlowEdge<>(3, 1);
    e2->set_reversal(r2);
    auto *r3 = new FlowEdge<>(4, 2);
    e3->set_reversal(r3);
    auto *r4 = new FlowEdge<>(4, 3);
    e4->set_reversal(r4);

    adj[e1->from()].push_back(e1);
    adj[e1->reversal()->from()].push_back(e1->reversal());

    adj[e2->from()].push_back(e2);
    adj[e2->reversal()->from()].push_back(e2->reversal());

    adj[e3->from()].push_back(e3);
    adj[e3->reversal()->from()].push_back(e3->reversal());

    adj[e4->from()].push_back(e4);
    adj[e4->reversal()->from()].push_back(e4->reversal());

    for (int i = 1; i <= 4; ++i) {
        for (auto &e: adj[i]) {
            cout << e->from() << " -> " << e->to() << ", "
                 << e->flow() << " / " << e->capacity() << "\n";
        }
    }
    /* output:
    1 -> 2, 0 / 1
    1 -> 3, 0 / 1
    2 -> 1, 0 / 0
    2 -> 4, 0 / 1
    3 -> 1, 0 / 0
    3 -> 4, 0 / 1
    4 -> 2, 0 / 0
    4 -> 3, 0 / 0
     */

    return 0;
}
