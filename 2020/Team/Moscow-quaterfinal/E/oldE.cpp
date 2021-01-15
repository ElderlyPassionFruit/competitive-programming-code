#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

string s;

void read() {
    cin >> s;
}

const int SUFF = 6;

string ans;

bool stupidCheck(string s) {
    if (s[0] == '0') return false;
    if (stoi(s) % 7) return false;
    return true;
}

void stupid() {
    sort(all(s));
    ans = "";
    do {
        if (!stupidCheck(s)) continue;
        if (ans.empty() || stoi(ans) < stoi(s)) {
            ans = s;
        }
    } while (next_permutation(all(s)));
    if (ans.empty()) {
        ans = "-1";
    }
}

const int N = 10;
int cnt[N];

int calcMod(vector<int> a) {
    int ans = 0;
    for (auto i : a) {
        ans = (ans * 10 + i) % 7;
    }
    return ans;
}

int calcMod() {

}

void smart() {
    fill(cnt, cnt + N, 0);
    for (auto i : s) {
        cnt[i - '0']++;
    }
    for (int num1 = 0; num1 < 10; ++num1) {
        if (!cnt[num1]) continue;
        --cnt[num1];
        for (int num2 = 0; num2 < 10; ++num2) {
            if (!cnt[num2]) continue;
            --cnt[num2];
            for (int num3 = 0; num3 < 10; ++num3) {
                if (!cnt[num3]) continue;
                --cnt[num3];
                for (int num4 = 0; num4 < 10; ++num4) {
                    if (!cnt[num4]) continue;
                    --cnt[num4];
                    for (int num5 = 0; num5 < 10; ++num5) {
                        if (!cnt[num5]) continue;
                        --cnt[num5];
                        for (int num6 = 0; num6 < 10; ++num6) {
                            if (!cnt[num6]) continue;
                            --cnt[num6];
                            
                            ++cnt[num6];
                        }
                        ++cnt[num5];
                    }
                    ++cnt[num4];
                }
                ++cnt[num3];
            }
            ++cnt[num2];
        }
        ++cnt[num1];
    }
}

void run() {
    if (s.size() <= 6) {
        stupid();
    } else {
        smart();
    }
}

void write() {
    cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    read();
    run();
    write();
    return 0;
}