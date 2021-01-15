#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, mod;

void read() {
    cout << "Input N, M" << endl;
    cin >> n >> mod;
}

string wr(int x) {
    string ans = "";
    for (int i = 0; i < n; i++) {
        ans += '0' + ((x >> i) & 1) * (i + 1);
        ans += " ";
    }
    return ans;
}

map<vector<int>, pair<bool, int>> mem;

int get(int x) {
    return __builtin_popcount(x);
}

pair<bool, int> solve(int sum, int a, int b, int type) {
    //cout << sum << " " << wr(a) << " " << wr(b) << " " << type << endl;
    assert(get(a) <= get(b) && abs(get(a) - get(b)) <= 1);
    vector<int> state = {sum, a, b, type};
    if (mem.count(state)) {
        return mem[state];
    }
    if (sum % mod == 0 && sum) {
        return mem[state] = {0, 0};
    }
    if (!a && !b) {
        return {0, 0};
    }

    if (!type) {
        assert(a);
        bool ans = false;
        int cnt = 1e9;
        for (int i = 0; i < n; i++) {
            if ((a >> i) & 1) {
                auto have = solve(sum + i + 1, a ^ (1 << i), b, type ^ 1);
                if (have.first) continue;
                ans = true;
                chkmin(cnt, have.second + 1);
            }
        }
        if (ans) {
            return mem[state] = {ans, cnt};
        }
        cnt = 0;
        for (int i = 0; i < n; i++) {
            if ((a >> i) & 1) {
                chkmax(cnt, solve(sum + i + 1, a ^ (1 << i), b, type ^ 1).second + 1);
            }
        }
        return mem[state] = {ans, cnt};
    } else {
        assert(b);
        bool ans = false;
        int cnt = 1e9;
        for (int i = 0; i < n; i++) {
            if ((b >> i) & 1) {
                auto have = solve(sum + i + 1, a, b ^ (1 << i), type ^ 1);
                if((have.first && (have.second != 1))) {
                    cout << n << " " << mod << " " << sum << " " << wr(a) << " " << wr(b) << " " << type << endl;
                    cout << "i = " << i + 1 << " " << have.second << endl;
                    assert(false);
                }
                if (have.first) continue;
                ans = true;
                chkmin(cnt, have.second + 1);
            }
        }
        if (ans) {
            return mem[state] = {ans, cnt};
        }
        cnt = 0;
        for (int i = 0; i < n; i++) {
            if ((b >> i) & 1) {
                chkmax(cnt, solve(sum + i + 1, a, b ^ (1 << i), type ^ 1).second + 1);
            }
        }
        return mem[state] = {ans, cnt};
    }
}

void run() {
    mem.clear();
    int have = (1 << n) - 1;
    cout << (solve(0, have, have, 0).first ? "First player will win" : "Second player will win") << endl;
    cout << "cnt states = " << mem.size() << endl;
    cout << "mem = " << endl;
    for (auto i : mem) {
        cout << "sum = " << i.first[0] << " a = " << wr(i.first[1]) << " b = " << wr(i.first[2]) << " player = " << (i.first[3] == 0 ? "First" : "Second") << " " << (i.second.first ? "win" : "lose") << endl;
    }
    exit(0);
    int sum = 0, a = have, b = have;
    int start = 0;
    while (true) {
        cout << "Sum = " << sum << " a = " << wr(a) << " b = " << wr(b) << endl;
        cout << (start == 0 ? "First" : "Second") << " player variants:" << endl;
        for (int i = 0; i < n; i++) {
             if (!start && ((a >> i) & 1)) {
                auto have = solve(sum + i + 1, a ^ (1 << i), b, start ^ 1);
                cout << i + 1 << " " << (have.first ? "lose" : "win") << " in " << have.second << " moves" << endl;
            } else if (start && ((b >> i) & 1)) {
                auto have = solve(sum + i + 1, a, b ^ (1 << i), start ^ 1);
                cout << i + 1 << " " << (have.first ? "lose" : "win") << " in " << have.second << " moves" << endl;
            }
        }

        cout << "Input next move:" << endl;

        int x;
        cin >> x;
        if (!start) {
            while (!((a >> (x - 1)) & 1)) {
                cout << "Incorrect input" << endl;
                cin >> x;
            }
        }
        else if (start) {
            while (!((b >> (x - 1)) & 1)) {
                cout << "Incorrect input" << endl;
                cin >> x;
            }
        }
        sum += x;
        if (!start) {
            a ^= (1 << (x - 1));
        } else if (start) {  
            b ^= (1 << (x - 1));
        }
        if (sum % mod == 0) {
            cout << (start == 0 ? "First" : "Second") << " player win" << endl;
            return;
        }
        start ^= 1;
    }
}

void write() {

}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //n = 6, mod = 4;
    //solve(0, (1 << n) - 1, (1 << n) - 1, 0);
    //return 0;
    for (n = 1; n <= 10; n++) {
        for (mod = n + 2; mod <= 50; mod++) {
            mem.clear();
            cout << solve(0, (1 << n) - 1, (1 << n) - 1, 0).first << " ";
            cout.flush();
        }
        cout << endl;
    }
    return 0;
    for (int it = 0; ; it++) {
        cout << "Round #" << it << endl;
        read();
        run();
        write();
    }
    return 0;
}