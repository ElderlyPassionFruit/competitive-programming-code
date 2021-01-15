#include <iostream>
#include <vector>

using namespace std;

int rows, columns, numberOfBombs;

bool isInField(int x, int y) {
    return x >= 0 && x < rows && y >= 0 && y < columns;
}

int main() {
    cin >> rows >> columns >> numberOfBombs;
    vector<vector<char>> field(rows, vector<char> (columns));
    for (int i = 0; i < numberOfBombs; ++i) {
        int x, y;
        cin >> x >> y;
        --x;
        --y;
        field[x][y] = '*';
    }

    const vector<int> deltaRows = {-1, -1, -1, 0, 1, 1, 1, 0};
    const vector<int> deltaColumns = {-1, 0, 1, 1, 1, 0, -1, -1};

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (field[i][j] == '*') {
                continue;
            }
            field[i][j] = '0';
            for (size_t direction = 0; direction < deltaRows.size(); ++direction) {
                int x = i + deltaRows[direction];
                int y = j + deltaColumns[direction];
                if (!isInField(x, y)) {
                    continue;
                }
                if (field[x][y] != '*') {
                    continue;
                }
                field[i][j]++;
            }
        }
    }
    for (const auto &row : field) {
        for (const auto &column : row) {
            cout << column << " ";
        }
        cout << "\n";
    }
}
