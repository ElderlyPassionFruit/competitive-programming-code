#include <iostream>
#include <string>

using namespace std;

int main() {
    string text;
    getline(cin, text);
    int numberOfUnicodeSymbols = 0;
    for (size_t i = 0; i < text.size(); ++i) {
        ++numberOfUnicodeSymbols;
        if (!((1 << 7) & text[i])) continue;
        int cntOnes = 0;
        for (int bit = 7; bit >= 0; --bit) {
            if (!(text[i] & (1 << bit))) {
                break;
            }
            ++cntOnes;
        }
        i += cntOnes - 1;
    }
    cout << numberOfUnicodeSymbols << "\n";
    return 0;
}
