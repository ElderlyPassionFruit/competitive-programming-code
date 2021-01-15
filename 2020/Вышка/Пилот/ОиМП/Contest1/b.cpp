#include <iostream>
#include <vector>
#include <string>

using namespace std;

const vector<char> vowelLetters = {'a', 'e', 'h', 'i', 'o', 'u', 'w', 'y'};

bool checkVowelSound(const char & c) {
    for (const auto & vowelLetter : vowelLetters) {
        if (vowelLetter == c) {
            return true;
        }
    }
    return false;
}

const vector<vector<char>> numberOfLetters = {
    {'b', 'f', 'p', 'v'},
    {'c', 'g', 'j', 'k', 'q', 's', 'x', 'z'},
    {'d', 't'},
    {'l'},
    {'m', 'n'},
    {'r'}
};

int getNumberOfLetter(const char & c) {
    for (int number = 0; number < 6; ++number) {
        for (const auto &letterforCheck : numberOfLetters[number]) {
            if (letterforCheck == c) {
                return number + 1;
            }
        }
    }
}

int main() {
    string word;
    cin >> word;
    string answer = "";
    for (const auto &c : word) {
        if (answer.empty()) {
            answer += c;
        } else if (checkVowelSound(c)) {
            continue;
        } else {
            char forAdd = '0' + getNumberOfLetter(c);
            if (forAdd == answer.back()) continue;
            answer += forAdd;
        }
    }
    while (answer.size() > 4) answer.pop_back();
    while (answer.size() < 4) answer += "0";
    cout << answer << "\n";
    return 0;
}
