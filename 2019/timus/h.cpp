#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int n, m;
const int MAXN = 110;
int table[MAXN][MAXN];
int used[MAXN][MAXN];

bool check(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && table[x][y] != 1;
}

vector<int> dx = {0, 1, 0, -1};
vector<int> dy = {1, 0, -1, 0};

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> table[i][j];
            used[i][j] = -1;
        }
    }
    queue<pair<int, int>> q;
    used[0][0] = 0;
    q.push({0, 0});
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        if (table[p.first][p.second] == 2) {
            cout << used[p.first][p.second] << endl;
            exit(0);
        }
        for (int i = 0; i < 4; i++) {
            int nx = p.first + dx[i], ny = p.second + dy[i];
            if (!check(nx, ny)) {
                continue;
            }
            if (used[nx][ny] != -1) continue;
            used[nx][ny] = used[p.first][p.second] + 1;
            q.push({nx, ny});
        }
    }
    return 0;
}