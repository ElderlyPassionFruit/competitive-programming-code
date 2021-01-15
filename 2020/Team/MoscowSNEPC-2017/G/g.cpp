#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
const int N = 510;
int n, m;
int r[N][N], c[N][N];

void no() {
    cout << "No\n";
    exit(0);
}

bool used[N][N];
int val[N][N];

vector<int> dx = {0, 1, 0, -1};
vector<int> dy = {1, 0, -1, 0};

void dfs(int x, int y) {
    used[x][y] = true;
    for (int it = 0; it < 4; it++) {
        int nx = (x + dx[it] + n) % n;
        int ny = (y + dy[it] + m) % m;
        int nVal;
        if (it == 0) {
           // cout << "c[x][y + 1] = " << c[x][(y + 1) % m] << endl;
            nVal = val[x][y] + c[x][(y + 1) % m];
        } else if (it == 1) {
            nVal = val[x][y] - r[(x + 1) % n][y];
        } else if (it == 2) {
            nVal = val[x][y] - c[x][y];
        } else if (it == 3) {
            nVal = val[x][y] + r[x][y];
        }
        if (used[nx][ny]) {
            if (val[nx][ny] != nVal) {
               // cout << nx << " " << ny << " " << x << " " << y << " " << nVal << endl;
               /* cout << "used = " << endl;
                for (int i = 0; i < n; i++){
                    for (int j = 0; j < m; j++) {
                        cout << used[i][j] <<" ";
                    }
                    cout << endl;
                }
                cout << "val = " << endl;
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < m; j++) {
                        cout << val[i][j] << " ";
                    }
                    cout << endl;
                }*/
                no();
            }
            continue;
        }
        val[nx][ny] = nVal;
        dfs(nx, ny);
    }
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> r[i][j] >> c[i][j];
        }
    }
    /*cout << "r = " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << r[i][j] << " ";
        }
        cout << endl;
    }
    cout << "c = " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << c[i][j] << " ";
        }
        cout << endl;
    }*/
    dfs(0, 0);
    cout << "Yes\n";
	return 0;
}