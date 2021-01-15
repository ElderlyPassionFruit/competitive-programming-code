#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector <int> odd_manacher(string s) {
    int n = (int) s.size();
    vector <int> d(n);
    for (int i = 0; i < n; i++) {
        int k = 0;
        while (i - (k + 1) >= 0 && i + (k + 1) < n && s[i - (k + 1)] == s[i + (k + 1)]) {
            k++;
        }
        d[i] = k;
    }
    return d;
}

vector <int> even_manacher(string s) {
    int n = (int) s.size();
    vector <int> d(n);
    for (int i = 0; i < n; i++) {
        int k = 0;
        while (i - (k + 1) >= 0 && i + k < n && s[i - (k + 1)] == s[i + k]) {
            k++;
        }
        d[i] = k;
    }
    return d;
}

ll solve_odd(string s) {
    vector <int> d = odd_manacher(s);
    int n = (int) s.size();
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((j - i) % 2 && d[i] >= (j - i) / 2 && d[j] >= (j - i) / 2) {
                ans++;
            }
        }
    }
    return ans;
}

ll solve_even(string s) {
    vector <int> d = even_manacher(s);
    int n = (int) s.size();
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((j - i) % 2 == 0 && d[i] >= (j - i) / 2 && d[j] >= (j - i) / 2) {
                ans++;
            }
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
