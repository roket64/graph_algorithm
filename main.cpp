#include "base_structure.h"

#include <iostream>
#include <queue>

std::vector<int> work(5);
std::vector<int> level(5);

template<class T>
constexpr std::string_view type_name() {
#ifdef __clang__
    std::string_view p = __PRETTY_FUNCTION__;
    return {p.data() + 34, p.size() - 34 - 1};
#elif defined(__GNUC__)
    std::string_view p = __PRETTY_FUNCTION__;
#  if __cplusplus < 201402
    return string_view(p.data() + 36, p.size() - 36 - 1);
#  else
    return std::string_view(p.data() + 49, p.find(';', 49) - 49);
#  endif
#elif defined(_MSC_VER)
    string_view p = __FUNCSIG__;
    return string_view(p.data() + 84, p.size() - 84 - 7);
#endif
}

int dfs(int u, int t, int f, std::vector<std::vector<flow_edge<>>> &adj) {
    if (u == t) return f;
    for (auto &i = work[u]; i < adj[u].size(); ++i) {
        auto next_ = &adj[u][i];
        std::cout << next_->from() << " -> " << next_->to() << ": ";
        std::cout << next_->flow() << " / " << next_->capacity() << ", spare: " << next_->spare() << std::endl;
        if (level[next_->to()] == level[next_->from()] + 1 && next_->spare() > 0) {
            if (auto ret = dfs(next_->to(), t, std::min(f, next_->spare()), adj)) {
                next_->push_flow(ret);
                std::cout << "pushed: " << ret << ", ";
                std::cout << next_->flow() << " / " << next_->capacity() << std::endl;
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

    int ans = 0;
    while (auto flow = dfs(1, 4, 0x3f3f3f3f, adj)) {
        ans += flow;
    }
    std::cout << ans << std::endl;

//    1 -> 2: 0 / 10, spare: 10
//    2 -> 4: 0 / 10, spare: 10
//    pushed: 10, 10 / 10
//    pushed: 10, 10 / 10
//    1 -> 2: 10 / 10, spare: 0
//    1 -> 3: 0 / 10, spare: 10
//    3 -> 4: 0 / 10, spare: 10
//    pushed: 10, 10 / 10
//    pushed: 10, 10 / 10
//    1 -> 3: 10 / 10, spare: 0
//    20

    return 0;
}
