#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int N = 1e3 + 10;
int n;
int a[N];
vector<int> ans;

void no() {
    cout << "No\n";
    exit(0);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    int zeros = 0;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    map<int, int> cnt;
    for (int i = 0; i < n; ++i) {
        if (a[i] < 0) {
            a[i] = -a[i];
            if(cnt[a[i]] > 0) {
                cnt[a[i]]--;
            } else if (zeros > 0) {
                --zeros;
                ans.push_back(a[i]);
            } else {
                no();
            }
        } else if (a[i] > 0) {
            cnt[a[i]]++;
        } else {
            zeros++;
        }
    }
    while (zeros--) {
        ans.push_back(1);
    }
    cout << "Yes\n";
    for (auto i : ans) {
        cout << i << " ";
    }
    cout << "\n";
	return 0;
}