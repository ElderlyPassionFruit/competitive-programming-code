#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

using namespace std;

string join(const vector<string>& a, char delimiter) {
    string answer;
    for (size_t i = 0; i < a.size(); ++i) {
        if (i > 0) {
            answer += delimiter;
        }
        answer += a[i];
    }
    return answer;
}

int main() {
    int m, n;
    cin >> m >> n;
    vector<string> words(m);
    for (auto& i : words) {
        cin >> i;
    }
    map<string, int> countGroups;
    for (size_t i = 0; i + n <= m; ++i) {
        vector<string> a;
        for (size_t j = 0; j < n; ++j) {
            a.push_back(words[i + j]);
        }
        countGroups[join(a, ' ')]++;
    }
    vector<pair<string, int>> answer;
    for (auto i : countGroups) {
        answer.push_back(i);
    }
    sort(answer.begin(), answer.end(),
        [] (const pair<string, int>& a, const pair<string, int>& b) {
            return tie(a.second, b.first) > tie(b.second, a.first);
        });
    for (const auto& i : answer) {
        cout << i.first << " - " << i.second << "\n";
    }
    return 0;
}

