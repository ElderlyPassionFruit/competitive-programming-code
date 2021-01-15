#include <bits/stdc++.h>
 
using namespace std;
//#define int long long
string s;
int n;
void read() {
    cin >> s;
    n = s.length();
}
string ans = "";
int have = -1;
 
int check(string s) {
    int ans = 0;
    int cnt = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(')
            cnt++;
        if (s[i] == ')' && cnt > 0)
            ans++, cnt--;
    }
    return ans;
}
 
int f(int x) {
    int cnt = 0;
    string fans = "";
    for (int i = 0; i < n; i++) {
        if (s[i] == '?') {
            if (cnt < x) {
                cnt++;
                fans += '(';
            }
            else {
                fans += ')';
            }
        }
        else {
            fans += s[i];
        }
    }
    return check(fans);
}
const int MAXN = 1e7 + 10;
int pref[MAXN][2], suff[MAXN][2];
 
void run() {
    int c = 0;
    for (int i = 0; i < n; i++)
        c += s[i] == '?';
     
    for (int i = 1; i <= n; i++) {
        pref[i][0] = pref[i - 1][0];
        pref[i][1] = pref[i - 1][1];
        if (s[i - 1] == ')') {
            if (pref[i][1] > 0) {
                pref[i][0]++;
                pref[i][1]--;
            }
        }
        else {
            pref[i][1]++;
        }
    }
 
 
    for (int i = n; i >= 1; i--) {
        suff[i][0] = suff[i + 1][0];
        suff[i][1] = suff[i + 1][1];
        if (s[i - 1] == '(') {
            if (suff[i][1] > 0) {
                suff[i][0]++;
                suff[i][1]--;
            }
        }
        else {
            suff[i][1]++;
        }
    }
 
    int fans = -1e9, pos = 0;
 
    for (int i = 1; i <= n; i++) {
            if (pref[i][0] + suff[i + 1][0] + min(pref[i][1], suff[i + 1][1]) > fans) {
                fans = pref[i][0] + suff[i + 1][0] + min(pref[i][1], suff[i + 1][1]);
                pos = i;
            }
    }
    pos--;
 
    ans = "";
    for (int i = 0; i <= pos; i++) {
        if (s[i] == ')')
            ans += ')';
        else
            ans += '(';
    }
    for (int i = pos + 1; i < n; i++) {
        if (s[i] == '(')
            ans += '(';
        else
            ans += ')';
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