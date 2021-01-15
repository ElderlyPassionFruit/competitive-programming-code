#include <iostream>
#include <unordered_set>

using namespace std;

int main() {
    unordered_set<int> hasNumber;
    int x;
    while (cin >> x) {
        if (hasNumber.find(x) != hasNumber.end()) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
        hasNumber.insert(x);
    }
    return 0;
}
