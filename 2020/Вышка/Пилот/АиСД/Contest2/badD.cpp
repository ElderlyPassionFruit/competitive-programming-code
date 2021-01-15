#include <cstdio>
#include <random>
#include <vector>

static constexpr int MAX = 1000 * 10000;

int Walk(const std::vector<std::vector<int>>& g, int s, int t) {
    std::mt19937 gen{std::random_device{}()};
    int numberOfSteps = 0;
    while (s != t) {
        s = g[s][gen() % g[s].size()];
        ++numberOfSteps;
        if (numberOfSteps == MAX) {
            return numberOfSteps;
        }
    } 
    return numberOfSteps;
}

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    std::vector<std::vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int u , v;
        scanf("%d%d", &u, &v);
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int s, t;
    scanf("%d%d", &s, &t);
    --s, --t;
    //cout << "s = " << s << " t = " << t << endl;
    int it = Walk(g, s, t);
    cout << it << "\n";
    //cout << "it = " << it << endl;
    /*if (it == MAX) {
        printf("Crashed\n");
    } else {
        printf("Passed\n");
    }*/

    return 0;
}