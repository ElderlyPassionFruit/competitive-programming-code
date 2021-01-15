#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ii pair <int, int>
#define app push_back
#define all(a) a.begin(), a.end()
#define bp __builtin_popcountll
#define ll long long
#define mp make_pair
#define f first
#define s second
#define Time (double)clock()/CLOCKS_PER_SEC
#define double long double

const int N = 20, V = 107 * 107, INF = 5e18;
int n, m, A, B;
string a[N];
double dist[N][N];

double dp[N][V];
double cost[N];
bool used[N][N];

struct State {
    int x, y;
    double d;
    bool operator < (const State s) const {
        return s.d < d;
    }
};  
priority_queue <State> q;

signed main() {
    #ifdef HOME
    freopen("input.txt", "r", stdin);
    #else
    #define endl '\n'
    ios_base::sync_with_stdio(0); cin.tie(0);
    #endif

    cin >> n >> m >> A >> B;
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < V; ++j)
            dp[i][j] = INF;
    dp[0][1] = 0;
    for (int i = 0; i + 1 < N; ++i) {
        for (int j = 1; j < V; ++j) {
            if (dp[i][j] == INF)
                continue;
            for (int k = max(1ll, j - B); k <= j + A && k < V; ++k) {
                dp[i+1][k] = min(dp[i+1][k], dp[i][j]+(2.0/(j+k)));
            }   
        }   
    }          
    for (int i = 0; i < N; ++i)
        cost[i] = dp[i][1];

    //'.' - empty
    //'C' - car
    //'V' - Vasya
    //'E' - exit

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            dist[i][j] = INF;
        }   
    }   
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == 'V') {
                dist[i][j] = 0;
                q.push({i, j, 0});
            }   
        }   
    }

    vector <ii> dir = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
    while (q.size()) {
        auto s = q.top(); q.pop();
        if (used[s.x][s.y])
            continue;
        used[s.x][s.y] = 1;
        for (auto v : dir) {
            int x = s.x, y = s.y;
            int len = 0;
            while (1) {
                x += v.f;
                y += v.s;
                ++len;

                if (x < 0 || x >= n || y < 0 || y >= m) {
                    break;
                }
                if (a[x][y] == 'C')
                    break;
                if (dist[s.x][s.y] + cost[len] < dist[x][y]) {
                    dist[x][y] = dist[s.x][s.y] + cost[len];
                    q.push({x, y, dist[x][y]});
                }   
            }
        }   
    }

    vector <ii> out;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == 'E') {
                out.app(mp(i, j));
            }
        }   
    }   

    double ans = INF;
    for (auto e : out) {
        int ex = e.f, ey = e.s;
        for (auto v : dir) {
            double add = 0;
            int x = ex, y = ey;
            double speed = 1;
            while (1) {
                if (x < 0 || x >= n || y < 0 || y >= m) {
                    break;
                }
                if (a[x][y] == 'C')
                    break;

                if (dist[x][y] != INF) {
                    ans = min(ans, dist[x][y]+add);
                }

                add += 2.0 / (speed + speed + A);
                speed += A;
                x += v.f;
                y += v.s;
            }   
        }
    }

    if (ans == INF) {
        cout << "-1" << endl;
        exit(0);
    }   

    cout.precision(20);
    cout << fixed << ans << endl;
}