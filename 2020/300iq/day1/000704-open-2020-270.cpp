#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector <int> odd_manacher(string s) {
    int n = (int) s.size();
    vector <int> d(n);
    int l = 0, r = -1;
    for (int i = 0; i < n; i++) {
        int k = 0;
        if (i <= r) {
            int pos = r - i;
            k = min(d[l + pos], r - i);
        }
        while (i - (k + 1) >= 0 && i + (k + 1) < n && s[i - (k + 1)] == s[i + (k + 1)]) {
            k++;
        }
        d[i] = k;
        if (i + d[i] > r) {
            l = i - d[i], r = i + d[i];
        }
    }
    return d;
}

vector <int> even_manacher(string s) {
    int n = (int) s.size();
    vector <int> d(n);
    int l = 0, r = -1;
    for (int i = 0; i < n; i++) {
        if (i <= r) {
            int pos = r - i;
            d[i] = min(d[l + pos + 1], r - i);
        }
        int k = d[i];
        while (i - (k + 1) >= 0 && i + k < n && s[i - (k + 1)] == s[i + k]) {
            k++;
        }
        d[i] = k;
        if (d[i] && i + d[i] - 1 > r) {
            l = i - d[i], r = i + d[i] - 1;
        }
    }
    return d;
}

const int N = 5e5;

vector <pair <int, int> > add[N];
int fenw[2][N];

void inc(int t, int x, int y) {
    for (; x < N; x = (x | (x + 1))) {
        fenw[t][x] += y;
    }
}

int get(int t, int x) {
    int s = 0;
    for (; x >= 0; x = (x & (x + 1)) - 1) {
        s += fenw[t][x];
    }
    return s;
}

ll get_sum(int t, int l, int r) {
    return get(t, r) - get(t, l - 1);
}

ll solve_odd(string s) {
    vector <int> d = odd_manacher(s);
    int n = (int) s.size();
    for (int i = 0; i <= n; i++) {
        add[i].clear();
    }
    auto add_segm = [&] (int l, int r, int who) {
        r = min(r, n - 1);
        add[l].push_back({who, 1});
        add[r + 1].push_back({who, -1});
    };
    for (int i = 0; i < n; i++) {
        add_segm(i + 1, i + d[i] * 2 + 1, i);
    }
    ll ans = 0;
    for (int i = 0; i <= n; i++) {
        for (auto c : add[i]) {
            inc(c.first % 2, c.first, c.second);
        }
        if (i < n) {
            ans += get_sum((i + 1) % 2, i - d[i] * 2 - 1, i - 1);
        }
    }
    return ans;
}

ll solve_even(string s) {
    vector <int> d = even_manacher(s);
    int n = (int) s.size();
    for (int i = 0; i <= n; i++) {
        add[i].clear();
    }
    auto add_segm = [&] (int l, int r, int who) {
        r = min(r, n - 1);
        add[l].push_back({who, 1});
        add[r + 1].push_back({who, -1});
    };
    for (int i = 0; i < n; i++) {
        add_segm(i + 1, i + d[i] * 2, i);
    }
     ll ans = 0;
    for (int i = 0; i <= n; i++) {
        for (auto c : add[i]) {
            inc(c.first % 2, c.first, c.second);
        }
        if (i < n) {
            ans += get_sum(i % 2, i - d[i] * 2, i - 1);
        }
    }
    return ans;
}

int main() {
#ifdef iq
    freopen("a.in", "r", stdin);
#endif // iq
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    string s;
    cin >> s;
    cout << solve_odd(s) + solve_even(s) << endl;
}
