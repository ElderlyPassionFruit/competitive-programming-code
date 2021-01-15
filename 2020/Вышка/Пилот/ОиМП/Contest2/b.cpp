#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

int main() {
    unordered_set<string> hasString;
    while (true) {
        char type;
        cin >> type;
        if (type == '#') {
            break;
        }
        string query;
        cin >> query;
        if (type == '+') {
            hasString.insert(query);
        } else if (type == '-') {
            if (hasString.find(query) != hasString.end()) {
                hasString.erase(query);
            }
        } else if (type == '?') {
            cout << (hasString.find(query) != hasString.end() ? "YES\n" : "NO\n");
        }
    }
    return 0;
}
