#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

void print(int person, unordered_map<int, vector<int>>& graph) {
    cout << person << "\n";
    for (const auto i : graph[person]) {
        print(i, graph);
    }
}

int main() {
    int n;
    cin >> n;
    unordered_map<int, vector<int>> graph;
    set<int> used;
    vector<int> roots;
    for (int i = 0; i < n; ++i) {
        int person, previousPerson;
        cin >> person >> previousPerson;
        if (!used.count(previousPerson)) {
            roots.push_back(person);
        } else {
            graph[previousPerson].push_back(person);
        }
        used.insert(person);
    }
    for (auto& [key, val] : graph) {
        reverse(val.begin(), val.end());
    }
    reverse(roots.begin(), roots.end());
    for (const auto i : roots) {
        print(i, graph);
    }
    return 0;
}
