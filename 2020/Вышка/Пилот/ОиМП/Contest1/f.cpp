#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int code;
    string answer = "";
    while (cin >> code) {
        if (code < (1 << 8)) {
            answer += static_cast<char> (code);
        } else {
            vector<int> bytes;
            while (code >= (1 << 6)) {
                bytes.push_back(code & ((1 << 6) - 1));
                code >>= 6;
            }
            if (code >= (1 << (8 - static_cast<int>(bytes.size()) - 2))) {
                bytes.push_back(code);
                code = 0;
            }
            bytes.push_back(code);
            reverse(bytes.begin(), bytes.end());
            for (size_t i = 0; i < bytes.size(); ++i) {
                bytes[i] |= 1 << 7;
                bytes[0] |= 1 << (7 - i);
            }
            for (const auto& i : bytes) {
                answer += i;
            }
        }
    }
    cout << answer << "\n";
    return 0;
}