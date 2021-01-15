#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool readString(const int alphabet, vector<bool>& usedChar) {
    string s;
    if (!(cin >> s)) {
        return false;
    } else {
        usedChar.assign(alphabet, false);
        for (const auto c : s) {
            usedChar[c - 'a'] = true;
        }
        return true;
    }
}

void mergeSets(vector<bool>& a, const vector<bool>& b) {
    for (size_t i = 0; i < a.size(); ++i) {
        a[i] = a[i] && b[i];
    }
}

int main() {
    const int alphabet= 26;
    vector<bool> usedChar(alphabet, true);
    vector<bool> checkChar;
    while (readString(alphabet, checkChar)) {
        mergeSets(usedChar, checkChar);
    }
    for (size_t i = 0; i < alphabet; ++i) {
        if (usedChar[i]) {
            cout << static_cast<char>(i + 'a');
        }
    }
    cout << "\n";
    return 0;
}
