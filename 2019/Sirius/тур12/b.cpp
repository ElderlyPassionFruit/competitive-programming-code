#include <bits/stdc++.h>
 
using namespace std;
//#define int long long
const int MAXN = 1e5 + 10;
int h[MAXN];
int n, m;
void read() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }
}
 
int get(int l, int r, int val) {
    int ans = -1;
    for (int i = r; i >= l; i--) {
        if (h[i] > val){
            ans = i;
            break;
        }
    }
    return ans;
}

const int INF = 1e9;
int pref[MAXN];
pair <int, int> help[MAXN];
pair <int, int> get_ans(int l, int r) {
	int n = r - l + 1;
	help[n] = make_pair(INF, INF);
    for (int i = l; i <= r; i++) {
    	help[i - l] = make_pair(h[i], i);
    }
    sort(help, help + n);
    pref[n] = 0;
    for (int i = n - 1; i >= 0; i--) {
        pref[i] = max(pref[i + 1], help[i].second);
    }

    pair <int, int> ans = {-1, -1};
    int pos = 1;
    for (int i = 0; i < n - 1; i++) {
        while (pos < n && help[pos].first <= help[i].first)
            pos++;
        if (pos > n - 1)
            break;
        if (pref[pos] - help[i].second > ans.second - ans.first) {
            ans = {help[i].second + 1, pref[pos] + 1};
        }
    }
    return ans;
}
 
void run() {
    int m;
    cin >> m;
    while (m--) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        pair <int, int> ans = get_ans(l, r);
        cout << ans.first << " " << ans.second << '\n';
    }
}
 
void write() {
 
}
 
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    read();
    run();
    write();
    return 0;
}