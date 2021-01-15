#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main() {
    unordered_map<string, long long> sumOfScores;
    unordered_map<string, int> cntOfScores;
    int cntQueries;
    cin >> cntQueries;
    for (int i = 0; i < cntQueries; ++i) {
        string name;
        int score;
        cin >> name >> score;
        sumOfScores[name] += score;
        cntOfScores[name]++;
        cout << sumOfScores[name] / cntOfScores[name] << "\n";
    }
    return 0;
}
