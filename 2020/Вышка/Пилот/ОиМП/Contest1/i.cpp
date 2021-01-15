#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> resultOfOperation(n, vector<int> (n));
    for (auto &i : resultOfOperation) {
        for (auto &j : i) {
            cin >> j;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                int firstResult = resultOfOperation[resultOfOperation[i][j]][k];
                int secondResult = resultOfOperation[i][resultOfOperation[j][k]];
                if (firstResult != secondResult) {
                    cout << "NO\n";
                    return 0;
                }
            }
        }
    }
    cout << "YES\n";
    return 0;
}
