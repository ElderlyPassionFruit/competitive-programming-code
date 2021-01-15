#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int N = 1e6 + 10;
int n;
int a[N];
int cnt[N];

int calcMex() {
    for (int i = 0; i < n; ++i) {
        if (a[i] > n) {
            continue;
        }
        cnt[a[i]]++;
    }
    int Mex = 0;
    while (cnt[Mex]) Mex++;
    return Mex;
}

int ansL = -1, ansR = -1;

void relax(int l, int r) {
    if (ansL == -1) {
        ansL = l, ansR = r;
        return;
    }
    if (ansR - ansL < r - l) return;
    ansL = l, ansR = r;
}

int last[N];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int k = calcMex();
    if (k == 0) {
        cout << "1 1\n";
        return 0;
    }
    set<pair<int, int>> pos;
    fill(last, last + N, -1);
    for (int i = n - 1; i >= 0; --i) {
        if (a[i] >= k) continue; 
        if (last[a[i]] != -1) {
            pos.erase({last[a[i]], a[i]});
        }
        last[a[i]] = i;
        pos.insert({last[a[i]], a[i]});
        if (pos.size() == k) {
            relax(i, (--pos.end())->first);
        }
    }

    cout << ansL + 1 << " " << ansR + 1 << endl;
	return 0;
}