#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string text;
    getline(cin, text);
    for (auto& i : text) {
        i = (i + 256) % 256;
    }
    for (size_t i = 0; i < text.size(); ++i) {
        if (!((1 << 7) & text[i])) {
            cout << static_cast<int>(text[i]) << " ";
        } else {
            int size = 0;
            for (int bit = 7; bit >= 0; --bit) {
                if (!(text[i] & (1 << bit))) {
                    break;
                }
                ++size;
            }
            vector<int> bytes;
            for (size_t j = 0; j < size; ++j) {
                bytes.push_back(text[i + j]);
            }
            int answer = bytes[0] & ((1 << (7 - size)) - 1);
            for (size_t bit = 1; bit < size; ++bit) {
                answer <<= 6;
                answer |= bytes[bit] & ((1 << 6) - 1);
            }
            cout << answer;
            i += size - 1;
            if (i != text.size()) {
                cout << " ";
            }
        }
    }
    cout << "\n";
    return 0;
}
