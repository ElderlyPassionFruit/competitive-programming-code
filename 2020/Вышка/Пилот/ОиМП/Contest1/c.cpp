#include <iostream>

using namespace std;

int main() {
    for (int i = 0; i < 16; ++i) {
        if (i < 10) {
            cout << "\t" << i;
        } else {
            cout << "\t" << static_cast<char>('A' + i - 10);
        }
    }
    cout << "\n";
    for (int row = 0; row < 6; ++row) {
        cout << row + 2;
        for (int column = 0; column < 16; ++column) {
            cout << "\t" << static_cast<char>(32 + row * 16 + column);
        }
        if (row < 5) {
            cout << "\n";
        }
    }
    return 0;
}
