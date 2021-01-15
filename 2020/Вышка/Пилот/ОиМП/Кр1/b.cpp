#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int m;
    cin >> m;
    if (m == 0) {
        return 0;
    }
    vector<vector<string>> files(m);
    for (size_t i = 0; i < m; ++i) {
        int n;
        cin >> n;
        files[i].resize(n);
        for (auto& s : files[i]) {
            cin >> s;
        }
    }
    size_t maxLength = (*max_element(files.begin(), files.end(),
        [] (const vector<string>& a, const vector<string>& b) {
            return a.size() < b.size();
        })).size();
    for (size_t i = 0; i < maxLength; ++i) {
        for (size_t j = 0; j < m; ++j) {
            if (j > 0) {
                cout << "\t";
            }
            if (i < files[j].size()) {
                cout << files[j][i];
            }
        }
        cout << "\n";
    }
    return 0;
}