#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

int main() {
    map<int, set<string>> lables;
    int cntLables;
    cin >> cntLables;
    for (int i = 0; i < cntLables; ++i) {
        string lable;
        int position;
        cin >> lable >> position;
        lables[position].insert(lable);
    }
    for (const auto& [position, listOfLables] : lables) {
        cout << position;
        for (const auto& lable : listOfLables) {
            cout << " " << lable;
        }
        cout << "\n";
    }
    return 0;
}
