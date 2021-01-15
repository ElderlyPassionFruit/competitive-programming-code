#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}
string s;

void read() {
    cin >> s;
}

int getLen(int a, int b) {
    int len = 1;
    while (a + len < s.size() && b + len < s.size() && s[a + len] == s[b + len] && s[a + len] != s[a]) {
        ++len;
    }
    return len;
}

pair<int, int> calc(char a) {
    int cnt = 0;
    for (auto i : s) {
        cnt += i == a;
    }
    if (cnt == 0) {
        return {-1, -1};
    }
    int first = 0;
    while (first < s.size() && s[first] != a) ++first;
    assert(first < s.size());
    int len = s.size() - first;
    for (int i = first + 1; i < s.size(); ++i) {
        if (s[i] == a) {
            len = min(getLen(first, i), len);
        }
    }
    return {cnt, len};
}

string ans;

void makeAns(char a, int len) {
    for (int i = 0; i < (int)s.size(); ++i) {
        if (s[i] == a) {
            ans = s.substr(i, len);
            break;
        }
    }
}

void run() {
    char ansA = '-';
    int ansLen = -1;
    int ansCnt = -1;
    for (char a = 'a'; a <= 'z'; ++a) {
        auto [myCnt, myLen] = calc(a);
        if (myCnt < ansCnt) continue;
        if (myCnt == ansCnt && myLen <= ansLen) continue;
        ansCnt = myCnt;
        ansLen = myLen;
        ansA = a;
    }
    makeAns(ansA, ansLen);
}

void write() {
    cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}