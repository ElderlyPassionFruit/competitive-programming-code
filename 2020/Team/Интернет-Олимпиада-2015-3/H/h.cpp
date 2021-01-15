#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int N = 1e5 + 10;
const int A = 26;

string s;
int n;
int pref[N][A];
vector<int> pos[A];

void init() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < A; ++j) {
            pref[i][j] = pref[i - 1][j];
        }
        ++pref[i][s[i - 1] - 'a'];
    }
    for (int i = 0; i < n; ++i) {
        pos[s[i] - 'a'].push_back(i);
    }
}

int get(int l, int r, int x) {
    return pref[r + 1][x] - pref[l][x];
}

int get(int l, int r) {
    int ans = 0;
    int myPos = l;
    for (int x = 0; x < A; ++x) {
        if (get(l, r, x) == 0) continue;
        int lx = *lower_bound(all(pos[x]), l);
        int rx = *(--upper_bound(all(pos[x]), r));
        if (lx >= myPos) {
            ans += rx - myPos;
            myPos = rx;
        } else {
            rx = *(--upper_bound(all(pos[x]), myPos));
            ans += r - myPos + 1;
            myPos = l;
            ans += rx - myPos;
            myPos = rx;
        }
    }
    return ans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    freopen("minimal.in", "r", stdin);
    freopen("minimal.out", "w", stdout);
    cin >> s;
    n = s.size();
    init();
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        cout << get(l, r) << "\n";
    }
	return 0;
}