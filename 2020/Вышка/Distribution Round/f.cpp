#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

const int N = 101;
int n, m;
char a[N][N];
string s;

void read() { 
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }
    cin >> s;
}

struct Event{
    int x, y, len;
    Event() {}
    Event(int _x, int _y, int _len) {
        x = _x, y = _y, len = _len;
    }
};

const int INF = 1e9 + 10;
queue<Event> q;
int dp[N][N][N];

void build() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                dp[i][j][k] = INF;
            }
        }
    }
}

bool checkCell(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && a[x][y] != 'X';
}

void relax(int x, int y, int len, int cost) {
    assert(checkCell(x, y));
    //if (!checkCell(x, y)) return;
    if (len > (int)s.size()) return;
    if (dp[x][y][len] <= cost) return;
    dp[x][y][len] = cost;
    q.push({x, y, len});
}

//‘N’, ‘S’, ‘E’ и ‘W’
vector<int> dx = {-1, 1, 0, 0};
vector<int> dy = {0, 0, 1, -1};

int getDir(char x) {
    if (x == 'N') return 0;
    if (x == 'S') return 1;
    if (x == 'E') return 2;
    if (x == 'W') return 3;
    assert(false);
    return -1;
}

pair<int, int> getPt(int x, int y, int dx, int dy) {
    int nx = x + dx;
    int ny = y + dy;
    if (checkCell(nx, ny)) return {nx, ny};
    return {x, y};
}

void bfs() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == 'P') {
                relax(i, j, 0, 0);
                break;
            }
        }
    }
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        int myDist = dp[v.x][v.y][v.len];
        for (int it = 0; it < 4; ++it) {
            auto [nx, ny] = getPt(v.x, v.y, dx[it], dy[it]);
            relax(nx, ny, v.len, myDist + 1);
        }
        relax(v.x, v.y, v.len + 1, myDist + 1);
        if (v.len == s.size()) continue;
        int dir = getDir(s[v.len]);
        auto [nx, ny] = getPt(v.x, v.y, dx[dir], dy[dir]);
        relax(nx, ny, v.len + 1, myDist);
    }
    /*for (int len = 0; len <= s.size(); ++len) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cout << dp[i][j][len] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }*/
}

int ans;

void makeAns() {
    ans = INF;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == 'E') {
                for (int len = 0; len <= (int)s.size(); ++len) {
                    chkmin(ans, dp[i][j][len]);
                }
                break;
            }
        }
    }
}

void run() {
    build();
    bfs();
    makeAns();
}

void write() {
    cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}