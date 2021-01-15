#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

#define int long long
#define double long double
const int MAXN = 1e5 + 10;
int dp[MAXN][2], cnt[MAXN][2];
vector <pair <int, pair<int, int> > > g[MAXN];
int n;
void read()
{
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        a--;
        b--;
        g[a].push_back({ b, {c, d} });
        g[b].push_back({ a, {c, d} });
    }
}

void dfs_down(int v, int p)
{
    for (auto i : g[v])
    {
        int u = i.first;
        int cost = i.second.first;
        int type = i.second.second;
        if (u != p)
        {
            dfs_down(u, v);
            if (type == 0)
            {
                dp[v][0] += dp[u][0] + cnt[u][0] * cost + cost;
                cnt[v][0] += cnt[u][0] + 1;

                dp[v][1] += dp[u][1] + cnt[u][1] * cost;
                cnt[v][1] += cnt[u][1];
            }
            else if (type == 1)
            {
                dp[v][1] += dp[u][0] + cnt[u][0] * cost;
                dp[v][1] += dp[u][1] + cnt[u][1] * cost + cost;
                cnt[v][1] += cnt[u][0];
                cnt[v][1] += cnt[u][1] + 1;
            }
        }
    }
}
void dfs_up(int v, int p)
{
    for (auto i : g[v])
    {
        int u = i.first;
        int cost = i.second.first;
        int type = i.second.second;
        if (u != p)
        {
            int x;
            if (type == 0)
            {
                x = dp[v][0] - dp[u][0] - cnt[u][0] * cost - cost + (cnt[v][0] - cnt[u][0] - 1) * cost + cost;
                dp[u][0] += x;
                x = cnt[v][0] - cnt[u][0] - 1 + 1;
                cnt[u][0] += x;

                x = dp[v][1] - dp[u][1] - cnt[u][1] * cost + (cnt[v][1] - cnt[u][1]) * cost;
                dp[u][1] += x;
                x = cnt[v][1] - cnt[u][1];
                cnt[u][1] += x;
            }
            else if (type == 1)
            {
                int y = dp[v][0] + cnt[v][0] * cost;
                //cout << "ето от dp[v][0] " << y << endl;
                x = dp[v][1] - dp[u][1] - dp[u][0] - (cnt[u][1] + cnt[u][0] + 1) * cost + (cnt[v][1] - (cnt[u][1] + cnt[u][0] + 1)) * cost + cost;
                //cout << "ето от dp[v][1] " << x << endl;
                dp[u][1] += x;
                dp[u][1] += y;
                x = cnt[v][1] - cnt[u][0] - cnt[u][1] - 1 + 1;
                cnt[u][1] += x;
                cnt[u][1] += cnt[v][0];
            }
            dfs_up(u, v);
        }
    }
}



double ans;
double run()
{
    dfs_down(0, 0);
    dfs_up(0, 0);
    ans = 0;
    int full = 0;
    for (int i = 0; i < n; i++)
    {
        ans += dp[i][1];
        full += cnt[i][1];
    }
    ans /= full;
    if (full == 0)
        return 0;
    return ans;
}


double ax;
int cnt_x;
void dfs(int v, int p, int length, int is)
{
    ax += length*is;
    cnt_x += is;
    for (auto i : g[v])
    {
        if (i.first != p)
        {
            dfs(i.first, v, length + i.second.first, is | i.second.second);
        }
    }
}


double run2()
{
    double ans = 0;
    int full_cnt = 0;
    for (int i = 0; i < n; i++)
    {
        ax = 0;
        cnt_x = 0;
        dfs(i, i, 0, 0);
        ans += ax;
        full_cnt += cnt_x;
    }
    if (full_cnt == 0)
        return 0;
    return ans / full_cnt;
}

void clear()
{
    for (int i = 0; i < n; i++)
    {
        dp[i][0] = 0;
        dp[i][1] = 0;
        cnt[i][0] = 0;
        cnt[i][1] = 0;
        g[i].clear();
    }
}

void generate(int x)
{
    n = x;
    clear();
    for (int i = 1; i < n; i++)
    {
        int v = rand() % i;
        int cost = rand() % 1000 + 1;
        int type = rand() % 2;
        g[v].push_back({ i, {cost, type} });
        g[i].push_back({ v, {cost, type} });
    }
}

void write()
{
    cout << ans << endl;
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout.precision(20);
    int c = 0;
    while (true)
    {
        c++;
        cout << "test " << c << " ";
        generate(100);
        double ans1 = run();
        double ans2 = run2();
        if (ans1 != ans2)
        {
            cout << "WA\n";
            cout << ans1 << " " << ans2 << endl;
            cout << n << endl;
            set <pair <pair <int, int>, pair <int, int> > > a;
            for (int i = 0; i < n; i++)
            {
                for (auto j : g[i])
                {
                    int x, y;
                    x = i;
                    y = j.first;
                    if (x > y)
                        swap(x, y);
                    a.insert({ {x, y}, j.second });
                }
            }
            for (auto i : a)
            {
                cout << i.first.first + 1 << " " << i.first.second + 1 << " " << i.second.first << " " << i.second.second << endl;
            }
            
                return 0;
        }
        cout << "OK\n";
    }
    read();
    cout << run2() << endl;
    //write();
    return 0;
}