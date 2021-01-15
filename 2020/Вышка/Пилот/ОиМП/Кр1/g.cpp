#include <algorithm>
#include <map>
#include <string>
#include <vector>

std::map<std::string, int> final_standings(const std::vector<std::map<std::string, int>>& results) {
    std::map<std::string, int> finalStandings;
    for (const auto& contest : results) {
        for (const auto& student : contest) {
            if (finalStandings.count(student.first)) {
                finalStandings[student.first] =
                    std::max(finalStandings[student.first], student.second);
            } else {
                finalStandings[student.first] = student.second;
            }
        }
    }
    return finalStandings;
}

#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<map<string, int>> a;
    map<string, int> add;
    add["a"] = 1;
    add["b"] = 2;
    a.push_back(add);
    add.clear();
    add["a"] = -1;
    add["b"] = 3;
    a.push_back(add);
    add = final_standings(a);
    for (auto i : add) {
        cout << i.first << " " << i.second << endl;
    }
    return 0;
}