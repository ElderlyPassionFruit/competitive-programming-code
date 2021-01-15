#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

struct Student{
    string name;
    string lastName;
    int day;
    int month;
    int year;
    int score;
    int numberOfPreferences;
    vector<string> preferences;
    void read() {
        cin >> name >> lastName >> day >> month >> year >> score;
        cin >> numberOfPreferences;
        preferences.resize(numberOfPreferences);
        for (auto& i : preferences) {
            cin >> i;
        }
    }
};

bool operator<(const Student& a, const Student& b) {
    if (a.score != b.score) {
        return a.score > b.score;
    }
    return tie(a.year, a.month, a.day, a.lastName, a.name) <
        tie(b.year, b.month, b.day, b.lastName, b.name);
}

int main() {
    int numberOfUniversities;
    cin >> numberOfUniversities;
    map<string, int> numberOfPlaces;
    map<string, vector<Student>> results;
    for (int i = 0; i < numberOfUniversities; ++i) {
        string university;
        int places;
        cin >> university >> places;
        numberOfPlaces[university] = places;
        results[university] = {};
    }
    int numberOfStudents;
    cin >> numberOfStudents;
    vector<Student> students(numberOfStudents);
    for (auto& i : students) {
        i.read();
    }
    sort(students.begin(), students.end());
    for (const auto& student : students) {
        for (const auto& university : student.preferences) {
            if (numberOfPlaces[university] > 0) {
                --numberOfPlaces[university];
                results[university].push_back(student);
                break;
            }
        }
    }
    for (auto& [university, students] : results) {
        cout << university;
        sort(students.begin(), students.end(),
            [] (const Student& a, const Student& b) {
                return tie(a.lastName, a.name, a.year, a.month, a.day) <
                    tie(b.lastName, b.name, b.year, b.month, b.day);
            });
        for (const auto& student : students) {
            cout << "\t" << student.name << " " << student.lastName;
        }
        cout << "\n";
    }
    return 0;
}
