#include <iostream>
#include <string>

using namespace std;

int main() {
    string password;
    cin >> password;
    bool ok = true;
    int small = 0, big = 0, digit = 0, other = 0;
    for (const auto &c : password) {
        if (c < 33 || c > 126) {
            ok = false;
        } else if ('a' <= c && c <= 'z') {
            small = 1;
        } else if ('A' <= c && c <= 'Z') {
            big = 1;
        } else if ('0' <= c && c <= '9') {
            digit = 1;
        } else {
            other = 1;
        }
    }
    if (small + big + digit + other < 3) {
        ok = false;
    }
    if (password.size() < 8 || password.size() > 14) {
        ok = false;
    }
    if (ok) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
    return 0;
}