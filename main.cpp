#include "base_structure.h"
#include "dinic.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

std::vector<std::vector<FlowEdge<> *>> adj(6);

void EdgeCheck() {
    FlowEdge<> *ptr = adj[2][0];
    std::cout << "ptr: " << ptr << std::endl;
    std::cout << ptr->from() << " -> " << ptr->to() << ", ";
    std::cout << ptr->flow() << " / " << ptr->capacity() << std::endl;
    std::cout << "rev: " << ptr->reversal() << std::endl;

    std::cout << "ptr: " << ptr->reversal() << std::endl;
    std::cout << ptr->reversal()->from() << " -> " << ptr->reversal()->to() << ", ";
    std::cout << ptr->reversal()->flow() << " / " << ptr->reversal()->capacity() << std::endl;
    std::cout << "rev: " << ptr->reversal()->reversal() << std::endl;

    ptr->push_flow(10);
    std::cout << ptr->flow() << std::endl;
    std::cout << ptr->reversal()->flow();
}

void AddEdge() {
    // 1 to 2 ~ 4
    for (int i = 2; i <= 4; ++i) {
        FlowEdge<> *e = new FlowEdge<>(1, i, 10);
        FlowEdge<> *rev = new FlowEdge<>(i, 1);
        e->set_reversal(rev);
        rev->set_reversal(e);
        adj[e->from()].push_back(e);
        adj[rev->from()].push_back(rev);
    }
    // 2 ~ 4 to 5
    for (int i = 2; i <= 4; ++i) {
        FlowEdge<> *e = new FlowEdge(i, 5, 5);
        FlowEdge<> *rev = new FlowEdge(5, i);
        e->set_reversal(rev);
        rev->set_reversal(e);
        adj[e->from()].push_back(e);
        adj[rev->from()].push_back(rev);
    }

    /*
    for (int i = 1; i <= 5; ++i) {
        std::cout << "node: " << i << std::endl;
        for (auto &e: adj[i]) {
            std::cout << "ptr: " << e << " ";
            std::cout << e->from() << " -> " << e->to() << ", ";
            std::cout << "[" << e->flow() << " / " << e->capacity() << "] ";
            std::cout << "rev: " << e->reversal() << std::endl;
        }
    }
    /**/
}

std::vector<int> level(6, -1);
std::vector<int> work(6, 0);

bool bfs(int source, int sink) {
    std::cout << "===========new bfs phase===========" << std::endl;
    std::queue<int> q;
    q.push(source);
    level[source] = 0;

    while (!q.empty()) {
        auto cur = q.front();
        std::cout << "node: " << cur << std::endl;
        q.pop();
        if (cur == sink) return true;
        for (auto &e: adj[cur]) {
            auto to_ = e->to();
            if (level[to_] == -1
                && e->spare() > 0) {
                std::cout << e->from() << " -> " << e->to() << ", ";
                std::cout << "[" << e->flow() << " / " << e->capacity() << "]" << std::endl;
                level[to_] = level[cur] + 1;
                q.push(to_);
            }
        }
    }
    return false;
}

int dfs(int cur, int sink, int flow) {
    std::cout << "cur: " << cur << " with " << flow << std::endl;
    if (cur == sink) {
        std::cout << "path found with " << flow << std::endl;
        return flow;
    }
    for (int &i = work[cur]; i < adj[cur].size(); ++i) {
        auto next = adj[cur][i];
        auto to_ = next->to();
        if (level[to_] == level[cur] + 1 && next->spare() > 0) {
            if (int ret = dfs(to_, sink, std::min(next->spare(), flow))) {
                next->push_flow(ret);
                std::cout << "pushed: " << ret << std::endl
                          << next->from() << " -> " << next->to() << ", "
                          << "[" << next->flow() << " / " << next->capacity() << "]" << std::endl
                          << next->reversal()->from() << " -> " << next->reversal()->to() << ", "
                          << "[" << next->reversal()->flow() << " / " << next->reversal()->capacity() << "]"
                          << std::endl;
                return ret;
            }
        }
    }
    return 0;
}

int main() {
//    AddEdge();

    /*
    std::cout << "=============bfs=============" << std::endl;
    bfs(1, 5);
    std::cout << "=============dfs=============" << std::endl;
    dfs(1, 5, 0x3f3f3f3f);

    int ans = 0;
    while (bfs(1, 5)) {
        std::cout << "===========new dfs phase===========" << std::endl;
        while (int flow = dfs(1, 5, 0x3f3f3f3f)) {
            ans += flow;
        }
    }
    std::cout << ans;
    /**/

    Dinic<> dinic = Dinic(5);
    // 1 to 2 ~ 4
    for (int i = 2; i <= 4; ++i) {
        dinic.add_edge(1, i, 10);
    }
    // 2 ~ 4 to 5
    for (int i = 2; i <= 4; ++i) {
        dinic.add_edge(i, 5, 5);
    }
    std::cout << dinic.GetMaxFlow(1, 5); // 15

    return 0;
}
