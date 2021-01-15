#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 21;
const int MAXMASK = 1 << MAXN;
int path[MAXN], p[MAXN];

int n;

void read() {
	cin >> n;
    path[0] = 1;
    for (int i = 1; i < n; i++) {
        cin >> p[i];
        p[i]--;
        path[i] = (1 << i) | path[p[i]];
    }
}


int dp[MAXMASK];
int sub_tree[MAXN];

void build() {
	for (int i = n - 1; i >= 0; i--) {
        sub_tree[i] |= 1 << i;
        sub_tree[p[i]] |= sub_tree[i];
    }
    fill(dp, dp + MAXMASK, -1);
}

int calc(int mask) {
    if (mask + 1 >= (1 << n)) return 0;
    if (dp[mask] != -1) return dp[mask];
   	dp[mask] = 0;
    for (int i = 0; i < n; i++) {
        if (((mask >> i) & 1) == 0) {
            dp[mask] |= !calc(mask | path[i]);
        }
    }
    return dp[mask];
}

int ans;

void calc() {
	ans = 0;
    for (int i = 0; i < n; i++) {
        ans += calc(((1 << n) - 1) ^ sub_tree[i] ^ (1 << i));
    }
}

void run() {
 	build();
 	calc();
}

void write() {
	cout << ans << endl;
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