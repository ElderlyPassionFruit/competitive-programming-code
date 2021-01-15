#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

mt19937 rnd(time(0));
const int MOD = 998244353;
//const int base[2] = {(int)rnd() % 228 + 1337, (int)rnd() % 228 + 1337};
//const int base[2] = {2, 3};

int base[2];

void initBase() {
    for (int it = 0; it < 2; ++it) {
        base[it] = (int)rnd() % 228 + 1337;
    }
}

int add(int a, int b) {
    a += b;
    if (a >= MOD) return a - MOD;
    return a;
}

int sub(int a, int b) {
    a -= b;
    if (a < 0) return a + MOD;
    return a;
}

int mul(int a, int b) {
    return (ll) a * b % MOD;
}

struct SuperString{
    const int N = 1e4 + 228;
    int val;
    vector<int> st;
    bool ok;
    unordered_map<int, pair<int, int>> mySon;
    SuperString() {}

    void upd(char c) {
        if (!ok) return;
        if (c == 'C') {
            st.push_back(st.back());
        } else if (c == 'D') {
            st.pop_back();
        } else if (c == 'L') {
            if (mySon.find(st.back()) == mySon.end()) {
                ok = false;
                return;
            } else {
                int add = mySon[st.back()].first;
                st.pop_back();
                st.push_back(add);
            }
        } else if (c == 'P') {
            int a = st.back();
            st.pop_back();
            int b = st.back();
            st.pop_back();
            int now = add(mul(a, base[0]), mul(b, base[1]));
            st.push_back(now);
            mySon[now] = {a, b};
        } else if (c == 'R') {
            if (mySon.find(st.back()) == mySon.end()) {
                ok = false;
                return;
            } else {
                int add = mySon[st.back()].second;
                st.pop_back();
                st.push_back(add);
            }
        } else if (c == 'S') {
            int a = st.back();
            st.pop_back();
            int b = st.back();
            st.pop_back();
            st.push_back(a);
            st.push_back(b);
        } else if (c == 'U') {
            if (mySon.find(st.back()) == mySon.end()) {
                ok = false;
                return;
            } else {
                auto [a, b] = mySon[st.back()];
                st.pop_back();
                st.push_back(b);
                st.push_back(a);
            }
        } else {
            assert(false);
        }
    }

    void wr() {
        cout << "ok = " << ok << endl;
        cout << "val = " << val << endl;
        cout << "st = " << endl;
        for (auto i : st) {
            cout << i << " ";
        }
        cout << endl;
    }

    SuperString(const string& a) {
        ok = true;
        st = {};
        for (int i = N; i > 0; --i) {
            st.push_back(i);
        }
        for (const auto c : a) {
            upd(c);
            //wr();
            //cout << endl;
            if (!ok) return;
        }
    }

};

bool operator==(const SuperString& a, const SuperString& b) {
    if (a.ok != b.ok) return false;
    if (!a.ok) return true;
    return a.st == b.st;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.precision(20);
    string a, b;
    cin >> a >> b;
    //auto fansA = SuperString(a);
    //auto fansB = SuperString(b);

    //fansA.wr();
    //fansB.wr();

    bool ok = true;
    for (int it = 0; it < 100; ++it) {
        initBase();
        auto fansA = SuperString(a);
        auto fansB = SuperString(b);
        ok &= fansA == fansB;
    }
    if (ok) {
        cout << "True\n";
    } else {
        cout << "False\n";
    }
    return 0;
}