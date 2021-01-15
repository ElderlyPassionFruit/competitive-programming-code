#include <algorithm>
#include <string>
#include <vector>

std::string common_prefix(const std::vector<std::string>& words) {
    std::string commonPrefix;
    if (words.empty()) return commonPrefix;
    size_t maxLength = (*std::min_element(words.begin(), words.end(),
        [] (const std::string& a, const std::string& b) {
            return a.size() < b.size();
        })).size();
    for (size_t i = 0; i < maxLength; ++i) {
        bool sameChar = true;
        for (size_t j = 1; j < words.size(); ++j) {
            if (words[j][i] != words[0][i]) {
                sameChar = false;
                break;
            }
        }
        if (!sameChar) {
            break;
        }
        commonPrefix += words[0][i];
    }
    return commonPrefix;
}

#include <bits/stdc++.h>
using namespace std;
int main() {
    string a = "a";
    string b = "aa";
    cout << common_prefix({a, b}) << endl;
    return 0;
}
