#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int N = 11;
int n;
char a[N][N];
bool used[N][N];

map<vector<pair<int, int>>, int> mem;
vector<vector<pair<int, int>>> now;

pair<int, int> forDivide[N * N];
int topD;

int divideColor[N][N];
int itColor = 1;

vector<int> dx = {0, 1, 0, -1};
vector<int> dy = {1, 0, -1, 0};

bool checkCell(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n;
}

void get(int x, int y) {
    now.push_back({});
    queue<pair<int, int>> q;
    q.push({x, y});
    now[now.size() - 1].push_back({x, y});
    divideColor[x][y] = 0;
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int it = 0; it < 4; ++it) {
            int nx = x + dx[it];
            int ny = y + dy[it];
            if (!checkCell(nx, ny)) continue;
            if (divideColor[nx][ny] != itColor) continue;
            divideColor[nx][ny] = 0;
            now[now.size() - 1].push_back({nx, ny});
            q.push({nx, ny});
        }
    }    
    sort(all(now[now.size() - 1]));
}

vector<vector<pair<int, int>>> get(const vector<pair<int, int>>& a, const pair<int, int>& pt) {
    topD = 0;
    ++itColor;
    for (const auto& i : a) {
        if (abs(i.first - pt.first) + abs(i.second - pt.second) <= 1) continue;
        forDivide[topD++] = i;
        divideColor[i.first][i.second] = itColor;
    }
    /*cout << "forDivide = " << endl;
    for (int it = 0; it < topD; ++it) {
        cout << forDivide[it].first << " " << forDivide[it].second << endl;
    }
    cout << endl;
    cout << "divideColor = " << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << divideColor[i][j] << " ";             
        }
        cout << endl;
    }*/
    now.clear();
    for (int it = 0; it < topD; ++it) {
        if (divideColor[forDivide[it].first][forDivide[it].second] != itColor) continue;
        get(forDivide[it].first, forDivide[it].second);    
        //++topNow;
    }
    return now;
}

int solve(const vector<pair<int, int>>& a) {
    if (a.empty()) return 0;
    if (mem.count(a)) return mem[a];
    //int fIt = 0;
    vector<bool> fMex(a.size() + 1, false);
    for (auto i : a) {
        auto now = get(a, i);
        /*cout << "del = " << i.first << " " << i.second << endl;
        cout << "now = " << endl;
        for (int it = 0; it < (int)now.size(); ++it) {
            for (auto i : now[it]) {
                cout << i.first << " " << i.second << endl;
            }
            cout << endl;
        }
        cout << endl;*/
        //exit(0);
        /*if (fIt++ == 2) {
            //exit(0);
        }*/
        int fans = 0;
        for (int it = 0; it < (int)now.size(); ++it) {
            fans ^= solve(now[it]);
        }
        fMex[fans] = true;
    }
    int ans = 0;
    while (fMex[ans]) ++ans;
    /*cout << "a = " << endl;
    for (auto i : a) {
        cout << i.first << " " << i.second << endl;
    }
    cout << "ans = " << ans << endl;
    cout << endl;*/
    return mem[a] = ans;
}

vector<vector<pair<int, int>>> have;

int color[N][N];
vector<pair<int, int>> comps[N * N];

void dfsWater(int x, int y, int c) {
    color[x][y] = c;
    comps[c].push_back({x, y});
    for (int it = 0; it < 4; ++it) {
        int nx = x + dx[it];
        int ny = y + dy[it];
        if (!checkCell(nx, ny)) continue;
        if (a[nx][ny] != '*') continue;
        if (color[nx][ny]) continue;
        dfsWater(nx, ny, c);
    }
}

void dfsGroups(int x, int y, int c) {
    used[x][y] = true;
    have[have.size() - 1].push_back({x, y});
    for (int it = 0; it < 4; ++it) {
        int nx = x + dx[it];
        int ny = y + dy[it];
        if (!checkCell(nx, ny)) continue;
        if (color[nx][ny] != c) continue;
        if (used[nx][ny]) continue;
        dfsGroups(nx, ny, c);
    }
}

void build() {
    int c = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i][j] != '*') continue;
            if (color[i][j]) continue;
            dfsWater(i, j, ++c);
        }
    }
    /*cout << "water = " << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << color[i][j] << " ";
        }
        cout << endl;
    }*/
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            color[i][j] = 0;
        }
    }
    for (int i = 1; i <= c; ++i) {
        for (auto [x, y] : comps[i]) {
            for (int it = 0; it < 4; ++it) {
                int nx = x + dx[it];
                int ny = y + dy[it];
                if (!checkCell(nx, ny)) continue;
                if (a[nx][ny] != '.') continue;
                color[nx][ny] = i;
            }
        }
    }
    /*cout << "fGroups = " << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << color[i][j] << " ";
        }
        cout << endl;
    }*/
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!color[i][j]) continue;
            if (used[i][j]) continue;
            have.push_back({});
            dfsGroups(i, j, color[i][j]);
            sort(all(have[have.size() - 1]));
        }
    }
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
        }
    }
    build();
    int ans = 0;
    for (auto i : have) {
        int fans = solve(i);
        //cout << "fans = " << fans << endl;
        ans ^= fans;
    }
    //vector<pair<int, int>> myPt = {{0, 1}, {0, 2}, {0, 3}, {1, 0}, {1, 1}, {1, 2}};
    //ans = solve(myPt);
    //cout << ans << endl;
    if (ans) {
        cout << "First player will win\n";
    } else {
        cout << "Second player will win\n";
    }
	return 0;
}