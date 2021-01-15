#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int n;
string s;
vector<bool> used;

queue<int> get(queue<int> q, int need) {
    queue<int> ans;
    for (int i = 0; i < n && !q.empty(); ++i) {
        if (s[i] - '0' != need) continue;
        if (q.front() > i) continue;
        if (used[i]) continue;
        used[i] = true;
        ans.push(i);
        q.pop();
    }
    if (!q.empty()) return {};
    return ans;
}

bool check(int x) {
    queue<int> q;
    for (int i = 0; i < x; ++i) {
        q.push(-1);
    }
    used.assign(n, false);
    q = get(q, 2);
    if (q.empty()) return false;
    q = get(q, 0);
    if (q.empty()) return false;
    q = get(q, 2);
    if (q.empty()) return false;
    q = get(q, 0);
    if (q.empty()) return false;
    return true;
}

void solve() {
    cin >> s;
    int l = 0, r = n / 4 + 1;
    while (l < r - 1) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << l << '\n';
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    while (cin >> n) {
        solve();
    }
	return 0;
}