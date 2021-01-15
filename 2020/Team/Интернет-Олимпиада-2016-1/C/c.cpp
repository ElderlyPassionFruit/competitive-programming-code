#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const ll INF = 1e18;

ll mul(ll a, ll b) {
    if (a == 0 || b == 0) return 0;
    if (INF / a < b) return INF;
    return a * b;
}

struct Monom{
    ll A, N, M; 
    Monom() {}

    Monom(ll _A, ll _N, ll _M) {
        A = _A;
        N = _N;
        M = _M;
    }

    Monom(string s) {
        assert(!s.empty());
        char flag = '+';
        if (s[0] == '-') {
            flag = '-';
            s.erase(s.begin());
        } else if (s[0] == '+') {
            s.erase(s.begin());
        }
        A = 1, N = 0, M = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '*') continue;
            if (s[i] >= '0' && s[i] <= '9') {
                int r = i;
                while (r < s.size() && s[r] >= '0' && s[r] <= '9') {
                    ++r;
                }
                A = mul(A, stoi(s.substr(i, r - i)));
                i = r - 1;
            } else {
                string add = "";
                bool forN = s[i] == 'n';
                if (i == s.size() || s[i + 1] != '^') {
                    add = "1";
                } else {
                    int l = i + 2;
                    int r = i + 2;
                    while (r < s.size() && s[r] >= '0' && s[r] <= '9') {
                        ++r;
                    }
                    add = s.substr(l, r - l);
                    i = r - 1;
                }
                if (forN) {
                    N += stoi(add);
                } else {
                    M += stoi(add);
                }
            }
        }
        if (flag == '-') {
            A = -A;
        }
    }

    void write() {
        cerr << "A = " << A << endl;
        cerr << "N = " << N << endl;
        cerr << "M = " << M << endl;
    }
};

bool operator<(const Monom& a, const Monom& b) {
    return tie(a.N, a.M, a.A) < tie(b.N, b.M, b.A);
}

vector<string> parseMonoms(string s) {
    vector<string> ans;
    string now = "";
    for (auto i : s) {
        if (i == '+' || i == '-') {
            if (!now.empty()) {
                ans.push_back(now);
                now = "";
            }
            now += i;
        } else {
            now += i;
        }
    }
    if (!now.empty()) {
        ans.push_back(now);
    }
    return ans;
}

void solve() {
    string s;
    cin >> s;
    vector<string> parsedS = parseMonoms(s);
    /*for (auto i : parsedS) {
        cerr << i << " ";
    }
    cerr << endl;
    */
    vector<Monom> a;
    for (auto i : parsedS) {
        a.push_back(Monom(i));
    }
    /*for (auto i : a) {
        i.write();
        cerr << endl;
    }*/
    sort(all(a));
    vector<Monom> fans;
    for (auto [A, N, M] : a) {
        if (fans.empty() || tie(fans.back().N, fans.back().M) != tie(N, M)) {
            fans.push_back({A, N, M});
        } else {
            fans[fans.size() - 1].A += A;
        }
    }
    vector<Monom> ans;
    for (auto i : fans) {
        if (i.A == 0) continue;
        ans.push_back(i);
    }
    bool plus = false;
    if (ans.empty()) {
        cout << "0\n";
        return;
    }
    for (auto [A, N, M] : ans) {
        if (A > 0) {
            if (plus) {
                cout << "+"; 
            }
            if (A > 1 || (N == 0 && M == 0)) {
                cout << A;
            }
        } else {
            cout << "-";
            A = abs(A);
            if (A > 1 || (N == 0 && M == 0)) {
                cout << A;
            }
        }
        if (N > 0) {
            cout << "n";
            if (N > 1) {
                cout << "^" << N;
            }
        }
        if (M > 0) {
            cout << "m";
            if (M > 1) {
                cout << "^" << M;
            }
        }
        plus = true;
    }
    cout << "\n";
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    freopen("polynomial.in", "r", stdin);
    freopen("polynomial.out", "w", stdout);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
	return 0;
}