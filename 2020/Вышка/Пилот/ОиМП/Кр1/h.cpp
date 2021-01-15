#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    getline(cin, s);
    uint64_t answer = 0;
    int shift = 0;
    for (uint8_t byte : s) {
        answer |= (static_cast<uint64_t>(byte & ((1 << 7) - 1))) << shift;
        shift += 7;
    }
    cout << answer << "\n";
    return 0;
}