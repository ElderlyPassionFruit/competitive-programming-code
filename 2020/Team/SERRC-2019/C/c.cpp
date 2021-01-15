#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int N = 1e6 + 10;
int n;
bool used[N];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        if (s.size() > 6 || s[0] == '-' || stoi(s) >= N) {
            continue;
        }
        used[stoi(s)] = true;
    }
    for (int i = 0; i < N; ++i) {
        if (!used[i]) {
            cout << i << "\n";
            return 0;
        }
    }
	return 0;
}