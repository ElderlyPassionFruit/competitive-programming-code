#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

vector<int> perm = {1, 2, 3, 4, 5, 6};

int Q = 100;

int calc(vector<int> perm) {
    int ans = 0;
    for (int i = 0; i < perm.size(); ++i) {
        for (int j = i + 1; j < perm.size(); ++j) {
            if (perm[i] > perm[j]) {
                ++ans;
            }
        }
    }
    return ans;
}

bool LOCAL = false;

int query(int pos) {
    assert(--Q >= 0);
    cout << pos << endl;
    if (!LOCAL) {
        string s;
        cin >> s;
        if (s[0] == 'H') return 1;
        return 0;
    } else {
        int fans = calc(perm);
        swap(perm[pos - 1], perm[pos]);
        return calc(perm) < fans;
    }
}

void outAns() {
    if (LOCAL) {
        assert(calc(perm) == 0); 
    }
    cout << 0 << endl;
    exit(0);
}

mt19937 rnd(time(0));

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    int n;
    if (!LOCAL) {
        cin >> n;
    } else {
        n = perm.size();
        shuffle(all(perm), rnd);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j < n - i; ++j) {
            if (!query(j)) {
                query(j);
            }
        }
    }
    outAns();
	return 0;
}