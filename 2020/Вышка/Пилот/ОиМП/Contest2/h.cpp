#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main() {
    int numberOfContests;
    map<string, vector<int>> scoreTable;
    cin >> numberOfContests;
    for (int i = 0; i < numberOfContests; ++i) {
        int numberOfStudents;
        cin >> numberOfStudents;
        for (int j = 0; j < numberOfStudents; ++j) {
            string name;
            int result;
            cin >> name >> result;
            if (scoreTable.find(name) == scoreTable.end()) {
                scoreTable[name].assign(numberOfContests, 0);
            }
            scoreTable[name][i] = result;
        }
    }
    for (const auto& [student, listOfResults] : scoreTable) {
        cout << student;
        for (const auto result : listOfResults) {
            cout << "\t" << result;
        }
        cout << "\n";
    }
    return 0;
}
