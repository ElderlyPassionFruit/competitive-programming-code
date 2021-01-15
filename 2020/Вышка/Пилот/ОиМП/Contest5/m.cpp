#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>
#include "query.h"

const int RESULTS_TO_PRINT = 3;

int main() {
    std::map<std::string, int> login_stats;
    std::string line;
    while (std::getline(std::cin, line)) {
        Query* q = parse_query(line.c_str());
        if (q->action == ACTION_COMMIT) {
            /* не знаю, как работать с map :( */
            login_stats[std::string(q->sender_login)]++;
        }

        delete q;
    }

    std::vector<std::pair<std::string, int>> stats_vec(
        login_stats.begin(), login_stats.end());
    // std::sort(stats_vec.begin(), stats_vec.end() /* не знаю, как сортировать по частоте :( */);
    std::sort(stats_vec.begin(), stats_vec.end(),
        [] (const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            return std::tie(a.second, b.first) > std::tie(b.second, a.first);
        });

    for (int i = 0; i < RESULTS_TO_PRINT; ++i) {
        if (i < stats_vec.size()) {
            std::cout << stats_vec[i].first << " " << stats_vec[i].second << "\n";
        }
    }
}