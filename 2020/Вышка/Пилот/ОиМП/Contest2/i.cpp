#include <iostream>
#include <climits>
#include <string>
#include <vector>

using namespace std;

int calcDifference(const vector<int>& a, const vector<int>& b) {
    int difference = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        difference += a[i] * b[i];
    }
    return difference;
}

int main() {
    int m, n;
    cin >> m >> n;
    string baseWord;
    cin >> baseWord;
    vector<int> baseVector(n);
    for (auto& i : baseVector) {
        cin >> i;
    }
    int answerVal = INT_MIN;
    vector<string> answerWords;
    for (int i = 0; i < m - 1; ++i) {
        string word;
        cin >> word;
        vector<int> wordVector(n);
        for (auto& j : wordVector) {
            cin >> j;
        }
        int currentVal = calcDifference(baseVector, wordVector);
        if (currentVal < answerVal) {
            continue;
        } else if (currentVal > answerVal) {
            answerVal = currentVal;
            answerWords.clear();
        }
        answerWords.push_back(word);
    }
    for (const auto& word : answerWords) {
        cout << word << "\n";
    }
    return 0;
}
