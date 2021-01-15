#include <iostream>
#include <string>

using namespace std;

int numberOf_l = 0;
int numberOf_w = 0;
int numberOf_m = 0;
int numberOf_L = 0;

void parseKeys(const string & keys) {
    for (const auto &key : keys) {
        if (key == 'l') {
            ++numberOf_l;
        } else if (key == 'w') {
            ++numberOf_w;
        } else if (key == 'm') {
            ++numberOf_m;
        } else if (key == 'L') {
            ++numberOf_L;
        }
    }
}

int main() {
    string keys;
    getline(cin, keys);
    parseKeys(keys);
    string line;
    int numberOfLines = 0;
    int numberOfWords = 0;
    int numberOfCharacters = 0;
    int maximumLength = 0;
    while (getline(cin, line)) {
        numberOfLines++;
        if (maximumLength < line.size()) {
            maximumLength = line.size();
        }
        numberOfCharacters += line.size() + 1;
        string word = "";
        for (const auto &c : line) {
            if (c == ' ') {
                if (!word.empty()) {
                    ++numberOfWords;
                    word = "";
                }
            } else {
                word += c;
            }
        }
        if (!word.empty()) {
            ++numberOfWords;
        }
    }
    bool flagWhiteSpace = false;
    for (int i = 0; i < numberOf_l; ++i) {
        if (flagWhiteSpace) cout << " ";
        flagWhiteSpace = true;
        cout << numberOfLines;
    }
    for (int i = 0; i < numberOf_w; ++i) {
        if (flagWhiteSpace) cout << " ";
        flagWhiteSpace = true;
        cout << numberOfWords;
    }
    for (int i = 0; i < numberOf_m; ++i) {
        if (flagWhiteSpace) cout << " ";
        flagWhiteSpace = true;
        cout << numberOfCharacters;
    }
    for (int i = 0; i < numberOf_L; ++i) {
        if (flagWhiteSpace) cout << " ";
        flagWhiteSpace = true;
        cout << maximumLength;
    }
    cout << "\n";
    return 0;
}
