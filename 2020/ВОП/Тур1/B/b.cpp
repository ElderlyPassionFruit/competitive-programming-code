#include <bits/stdc++.h>
   
using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(), (x).end()
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}
 
const int MAXN = 5e3 + 10;
int l, n;
int a[MAXN];
   
void read() {
    cin >> l >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a, a + n);
}
   
const int INF = 1e9 + 228;
int dp[MAXN][2][2];
short int par[MAXN][MAXN][2];
   
int len[MAXN];
   
int get_len(int x) {
    int ans = 0;
    while (x) {
        ans++;
        x /= 10;
    }
    return ans;
}
  
const int MAXLEN = 10;
 
int nine[MAXLEN];
 
void build() {
    int x = 1;
    for (int i = 1; i < MAXLEN; i++) {
        x *= 10;
        nine[i] = x - 1;
    }
    for (int i = 0; i < n; i++) {
        len[i] = get_len(a[i]);
    }
    for (ll i = 10, x = 1; i < INF; i = i * 10, x++) {
        if (get_len(i - 1) >= get_len(a[0])) break;
        dp[get_len(i - 1) + 2][0][1] = a[0] - (i - 1);
        par[get_len(i - 1) + 2][0][1] = x + n;
    }
    dp[0][0][0] = 1;
}
   
void relax(int Len, int cnt, int flag, int cost, int Par) {
	//cerr << cnt << endl;
    if (Len > l) return;
    if (cnt > n) return;
    if (dp[Len][1][flag] <= cost && dp[Len][1][flag] != 0) return;
    dp[Len][1][flag] = cost;
    par[Len][cnt][flag] = Par;
}
  
void calc() {
    vector<int> have; 
    for (int cnt = 0; cnt < n; cnt++) {
        if (cnt > 0) {
            have.clear();
            for (int x = 1; x < MAXLEN; x++) {
                ll i = nine[x] + 1;
                if (i - 1 == a[cnt]) break;
                if (i - 1 == a[cnt - 1]) break;
                if (x >= len[cnt]) break;
                if (x < len[cnt - 1]) continue;
                have.push_back(x);
            }
        }
        for (int Len = 0; Len < l - 1; Len++) {
            for (int flag = 0; flag < 2; flag++) {
                int now = dp[Len][0][flag];
                if (now == 0) continue;
                if (flag == 0) {
                    relax(Len + len[cnt] + 1, cnt + 1, 0, now, cnt);
                    relax(Len + len[cnt] + 2, cnt + 1, 1, now + a[cnt + 1] - a[cnt] - 1, cnt);
                    if (cnt > 0) {
                        for (auto x : have) {
                            int i = nine[x] + 1;
                            relax(Len + x + 2, cnt + 1, 1, now + a[cnt + 1] - (i - 1) - 1, n + x);
                        }
                    }
                } else {
                    relax(Len + len[cnt] + 1, cnt + 1, 0, now, par[Len][cnt][flag]);
                    relax(Len, cnt + 1, 1, now + a[cnt + 1] - a[cnt] - 1, par[Len][cnt][flag]);
                }
            }
        }
        for (int Len = 0; Len < MAXN; Len++) {
        	for (int flag = 0; flag < 2; flag++) {
        		dp[Len][0][flag] = dp[Len][1][flag];
        		dp[Len][1][flag] = 0;
        	}
        }
    }
}
   
string ans;
   
string get_string(int x) {
    string ans = "";
    while (x) {
        ans += x % 10 + '0';
        x /= 10;
    }
    reverse(all(ans));
    return ans;
}
   
void make_ans() {
    int Len = 0;
    for (int i = 1; i <= l - 1; i++) {
        if (dp[i][0][0] == 0) continue;
        if (dp[i][0][0] >= dp[Len][0][0] && dp[Len][0][0] != 0) continue;
        Len = i;
    }
    assert(dp[Len][0][0] != INF);
    int now = n;
    int flag = 0;
    while (now > 0) {
        int last = par[Len][now][flag];
        if (last < n) {
            last = a[last];
        } else {
            last = nine[last - n];
        }
        if (last == a[now - 1]) {
            string fans = get_string(a[now - 1]) + ",";
            reverse(all(fans));
            ans += fans;
            Len -= fans.size();
        } else {
            string fans = get_string(last) + ".." + get_string(a[now - 1]) + ",";
            reverse(all(fans));
            ans += fans;
            Len -= fans.size();
        }
        while (now > 0 && a[now - 1] >= last) now--;
    }
    reverse(all(ans));
    ans.pop_back();
    ans = "[" + ans + "]";
}
   
void run() {
    build();
    calc();
    make_ans();
}
   
void write() {
    cout << ans << endl;
}
   
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    read();
    run();
    write();
    return 0;
}