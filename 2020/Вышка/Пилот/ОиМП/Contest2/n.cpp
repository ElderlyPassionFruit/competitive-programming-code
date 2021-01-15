#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> baseNumbers;
vector<string> baseLetters;

void initBase() {
    for (int i = 1; i <= 20; ++i) {
        baseNumbers.push_back(i);
        string letter = "";
        letter += 'A' + (i - 1);
        baseLetters.push_back(letter);
    }
}

vector<string> parseSpaces(const string& s) {
    vector<string> answer;
    string::size_type startPos = 0;
    string::size_type endPos = s.find(' ');
    while (endPos != string::npos) {
        if (startPos != endPos) {
            answer.push_back(s.substr(startPos, endPos - startPos));
        }
        startPos = endPos + 1;
        endPos = s.find(' ', startPos);
    }
    return answer;
}

bool isLetter(const string& forCheck) {
    for (const auto& letter : baseLetters) {
        if (letter == forCheck) {
            return true;
        }
    }
    return false;
}

bool solve() {
    string input;
    if (!getline(cin, input)) {
        return false;
    }
    input += " ";
    auto parsedInput = parseSpaces(input);
    cout << parsedInput[0];
    int numberOfProblems = stoi(parsedInput[1]);

    if (parsedInput.size() == 2 || !isLetter(parsedInput[2])) {
        vector<int> problemNumbers;
        for (size_t i = 2; i < parsedInput.size(); ++i) {
            problemNumbers.push_back(stoi(parsedInput[i]));
        }
        vector<int> answer;
        set_difference(baseNumbers.begin(), baseNumbers.begin() + numberOfProblems,
                        problemNumbers.begin(), problemNumbers.end(),
                            inserter(answer, answer.begin()));
        for (const auto& problem : answer) {
            cout << " " << problem;
        }
    } else {
        vector<string> answer;
        set_difference(baseLetters.begin(), baseLetters.begin() + numberOfProblems,
                    parsedInput.begin() + 2, parsedInput.end(),
                        inserter(answer, answer.begin()));
        for (const auto& problem : answer) {
            cout << " " << problem;
        }
    }
    cout << "\n";
    return true;
}

int main() {
    initBase();
    while (solve()) {}
    return 0;
}