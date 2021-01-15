#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

struct student{
    string name, lastName;
    int day, month, year;
};

bool checkLessBirthday(const student& a, const student& b) {
    return tie(a.year, a.month, a.day) < tie(b.year, b.month, b.day);
}

bool checkLessName(const student& a, const student& b) {
    return tie(a.lastName, a.name) < tie(b.lastName, b.name);
}

bool comparatorBirthday(const student& a, const student& b) {
    if (tie(a.year, a.month, a.day) == tie(b.year, b.month, b.day)) {
        return checkLessName(a, b);
    }
    return checkLessBirthday(a, b);
}

bool comparatorName(const student& a, const student& b) {
    if (tie(a.lastName, a.name) == tie(b.lastName, b.name)) {
        return checkLessBirthday(a, b);
    }
    return checkLessName(a, b);
}

int main() {
    int n;
    cin >> n;
    vector<student> students(n);
    for (auto &i : students) {
        cin >> i.name >> i.lastName >> i.day >> i.month >> i.year;
    }
    string sortType;
    cin >> sortType;
    if (sortType == "date") {
        sort(students.begin(), students.end(), comparatorBirthday);
    } else {
        sort(students.begin(), students.end(), comparatorName);
    }
    for (const auto& i : students) {
        cout << i.name << " ";
        cout << i.lastName << " ";
        cout << i.day << ".";
        cout << i.month << ".";
        cout << i.year << "\n";
    }
    return 0;
}
