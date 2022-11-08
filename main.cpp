#include "base_structure.h"

#include <iostream>
#include <queue>

std::vector<int> work(5);
std::vector<int> level(5);

/*
int dfs(int u, int t, int f, std::vector<std::vector<flow_edge<>::edge_ptr>> &adj) {
    if (u == t) return f;
    for (auto &i = work[u]; i < adj[u].size(); ++i) {
        auto next_ = adj[u][i];
        std::cout << next_->from() << " -> " << next_->to() << ": ";
        std::cout << next_->flow() << " / " << next_->capacity() << ", spare: " << next_->spare() << std::endl;
        if (level[next_->to()] == level[next_->from()] + 1 && next_->spare() > 0) {
            if (flow_edge<>::flow_t ret = dfs(next_->to(), t, std::min(f, next_->spare()), adj)) {
                next_->push_flow(ret);
                return ret;
            }
        }
    }
    return 0;
}
/**/

int dfs(int u, int t, int f, std::vector<std::vector<flow_edge<>>> &adj) {
    if (u == t) return f;
    for (auto &i = work[u]; i < adj[u].size(); ++i) {
        auto next_ = adj[u][i];
        std::cout << next_.from() << " -> " << next_.to() << ": ";
        std::cout << next_.flow() << " / " << next_.capacity() << ", spare: " << next_.spare() << std::endl;
        if (level[next_.to()] == level[next_.from()] + 1 && next_.spare() > 0) {
            if (flow_edge<>::flow_t ret = dfs(next_.to(), t, std::min(f, next_.spare()), adj)) {
                next_.push_flow(ret);
                return ret;
            }
        }
    }
    return 0;
}

int main() {

    auto e = flow_edge<>(1, 2, 10);
    auto *e_ptr = &e;

//    std::cout << std::boolalpha << std::is_const_v<flow_edge<>::flow_t> << std::endl;
//    std::cout << e.capacity() - e.flow() << std::endl;
//    std::cout << e_ptr->capacity() - e_ptr->flow() << std::endl;
//    std::cout << e.spare() << std::endl;

    std::vector<std::vector<flow_edge<>>> adj{
            std::vector<flow_edge<>>{
            },
            std::vector<flow_edge<>>{
                    flow_edge<>(1, 2, 10),
                    flow_edge<>(1, 3, 10)
            },
            std::vector<flow_edge<>>{
                    flow_edge<>(2, 4, 10)
            },
            std::vector<flow_edge<>>{
                    flow_edge<>(3, 4, 10)
            },
            std::vector<flow_edge<>>{
            },
    };

    std::fill(level.begin(), level.end(), -1);
    std::queue<int> q;
    q.push(1);
    level[1] = 0;

    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        for (auto &edg: adj[u]) {
            auto v = edg.to();
            if (level[v] == -1
                && edg.spare() > 0) {
                q.push(v);
                level[v] = level[u] + 1;
            }
        }
    }

    auto flow = dfs(1, 4, 0x3f3f3f3f, adj);
    std::cout << flow << std::endl;

    return 0;
}
