#include <iostream>
#include <list>
#include <string>

class Vim{
private:
    static const bool READ_MOD = false;
    static const bool INSERT_MOD = true;
    std::list<char> str;
    std::list<char>::iterator it;
    bool modType;

public:
    Vim() {
        str = {};
        it = str.begin();
        modType = READ_MOD;
    }

    void makeReadMod() {
        modType = READ_MOD;
    }

    void insertChar(char x) {
        if (modType == INSERT_MOD) {
            it = str.insert(it, x);
            ++it;
        }
    }

    void makeInsertMod() {
        if (modType == READ_MOD) {
            modType = INSERT_MOD;
        } else {
            insertChar('i');
        }
    }

    void moveRight() {
        if (modType == READ_MOD) {
            if (it != str.end()) {
                ++it;
            }
        } else {
            insertChar('l');
        }
    }

    void moveLeft() {
        if (modType == READ_MOD) {
            if (it != str.begin()) {
                --it;
            }
        } else {
            insertChar('h');
        }
    }

    void write() {
        for (auto i : str) {
            std::cout << i;
        }
        std::cout << '\n';
    }
};

using namespace std;

int main() {
    Vim myString;
    string s;
    cin >> s;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == 'h') {
            myString.moveLeft();
        } else if (s[i] == 'l') {
            myString.moveRight();
        } else if (s[i] == 'i') {
            myString.makeInsertMod();
        } else if (s[i] == '<') {
            i += 4;
            myString.makeReadMod();
        } else {
            myString.insertChar(s[i]);
        }
    }
    myString.write();
    return 0;
}