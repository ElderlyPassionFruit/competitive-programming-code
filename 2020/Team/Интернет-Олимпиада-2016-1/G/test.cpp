#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int N = 1e3 + 10;
int n;
string a[N];
int ans;

void no() {
    cout << "" << endl;
    exit(0);
}

const int LEN = 1e5 + 10, A = 10;
int nxt[N][A];

void buildNxt(const string& a) {
    for (int i = 0; i < A; ++i) {
        nxt[a.size()][i] = -1;
    }
    for (int i = (int)a.size() - 1; i >= 0; --i) {
        for (int j = 1; j < A; ++j) {
            nxt[i][j] = nxt[i + 1][j];
        }
        nxt[i][a[i] - '0'] = i;
    }
}

string get(string a, int len) {
    buildNxt(a);
    string ans = "";
    int now = 0;
    for (int i = 0; i < len; ++i) {
        for (int num = 9; num >= 1; --num) {
            if (nxt[now][num] == -1) continue;
            if ((int)a.size() - nxt[now][num] + ans.size() < len) continue;
            ans += num + '0';
            now = nxt[now][num] + 1;
            break;
        }
    }
    return ans;
}

int getCommonPrefix(string a, string b) {
    int now = 0;
    int ans = -1;
    for (int num = b[0] - '0' - 1; num >= 1; --num) {
        if (nxt[now][num] == -1) continue;
        if (a.size() - nxt[now][num] < b.size()) continue;
        ans = max(ans, 0);
        break;
    }
    for (int cnt = 1; cnt <= (int)b.size(); ++cnt) {
        if (now == a.size()) break;
        if (nxt[now][b[cnt - 1] - '0'] == -1) break;
        if (a.size() - nxt[now][b[cnt - 1] - '0'] + cnt < b.size()) break;
        now = nxt[now][b[cnt - 1] - '0'] + 1;
        if (cnt == b.size()) {
            ans = max(ans, cnt);
        } else {
            for (int num = b[cnt] - '0' - 1; num >= 1; --num) {
                if (now == a.size()) break;
                if (nxt[now][num] == -1) continue;
                if (a.size() - nxt[now][num] + cnt < b.size()) continue;
                //cout << "a  = " << a << " b = " << b << " cnt = " << cnt << " now = " << now << " num = " << num << endl;
                ans = max(ans, cnt);
                break;
            }
        }
    }
    return ans;
}

string getEqualLength(string a, string b) {
    buildNxt(a);
    int l = getCommonPrefix(a, b);
    //cout << "l = " << l << endl;
    if (l == -1) return {};
    if (l == b.size()) return b;
    string ans = "";
    ans += b.substr(0, l);
    int now = 0;
    for (int i = 0; i < l; ++i) {
        now = nxt[now][b[i] - '0'] + 1;
    }
    int myNum = -1;
    for (int num = b[l] - '0' - 1; num >= 1; --num) {
        if (nxt[now][num] == -1) continue;
        if (a.size() - nxt[now][num] + l < b.size()) continue;
        myNum = num;
        break;
    }
    assert(myNum != -1);
    ans += myNum + '0';
    if (ans.size() == b.size()) return ans;
    now = nxt[now][myNum] + 1;
    ans += get(a.substr(now, a.size() - now), b.size() - ans.size());
    return ans;
}

string getDiffLength(string a, string b) {
    buildNxt(a);
    return get(a, (int)b.size() - 1);
}

string get(string a, string b) {
    if (a.size() < b.size()) return a;
    auto fans = getEqualLength(a, b);
    if (!fans.empty()) {
        ans += a.size() - b.size();
        return fans;
    }
    if (b.size() == 1) no();
    fans = getDiffLength(a, b);
    ans += a.size() - b.size() + 1;
    return fans;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.precision(20);
    //cout << get("43", "6") << endl;
    string a, b;
    cin >> a >> b;
    cout << get(a, b) << endl;
    return 0;
}