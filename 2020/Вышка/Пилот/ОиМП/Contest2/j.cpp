#include <deque>
#include <iostream>

using namespace std;

int main() {
    int numberOfWorks;
    cin >> numberOfWorks;
    deque<string> stackOfWorks;
    for (int i = 0; i < numberOfWorks; ++i) {
        string lastName, type;
        cin >> lastName >> type;
        if (type == "top") {
            stackOfWorks.push_front(lastName);
        } else if (type == "bottom") {
            stackOfWorks.push_back(lastName);
        }
    }
    int numberOfQueries;
    cin >> numberOfQueries;
    for (int i = 0; i < numberOfQueries; ++i) {
        int position;
        cin >> position;
        --position;
        cout << stackOfWorks[position] << "\n";
    }
    return 0;
}
