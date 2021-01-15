#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()
 
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
 
string s;
int n;
 
void make(string & s) {
    string ans = "";
    for (auto i : s) {
        if (i == '?') {
            ans += i;
            continue;
        }
        if (i == 'A' || i == 'E' || i == 'U' || i == 'I' || i == 'O')
            ans += "1";
        else
            ans += "0";
    }
    s = ans;
}
 
void read() {
    cin >> s;
    make(s);
    n = s.size();
}
 
const int MAXN = 55;
bool dp[MAXN][6][4][2][2];
 
string ans;
 
void calc() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= 5; j++)
            for (int k = 0; k <= 3; k++)
                for (int l = 0; l < 2; l++)
                    for (int flag = 0; flag < 2; flag++)
                        dp[i][j][k][l][flag] = false;
 
    if (s[0] == '?') {
        dp[0][1][0][0][0]= true; 
        dp[0][0][1][1][0] = true;
    }
    else if (s[0] == '1') {
        dp[0][0][1][1][0] = true;
    }
    else {
        dp[0][1][0][0][0] = true;
    }
 
    for (int i = 0; i < n - 1; i++) {
        for (int cnt0 = 0; cnt0 <= 5; cnt0++) {
            for (int cnt1 = 0; cnt1 <= 3; cnt1++) {
                if (cnt0 && cnt1) break;
                for (int now = 0; now < 2; now++) {
                    for (int flag = 0; flag < 2; flag++) {
                        if (!dp[i][cnt0][cnt1][now][flag]) continue;
                        if (s[i + 1] == '?') {
                            dp[i + 1][min(cnt0 + 1, 5)][0][0][flag || (cnt0 + 1 >= 5)] = true;
                            dp[i + 1][0][min(cnt1 + 1, 3)][1][flag || (cnt1 + 1 >= 3)] = true;
                        }
                        else if (s[i + 1] == '0') {
                            dp[i + 1][min(cnt0 + 1, 5)][0][0][flag || (cnt0 + 1 >= 5)] = true;
                        }
                        else if (s[i + 1] == '1') {
                            dp[i + 1][0][min(cnt1 + 1, 3)][1][flag || (cnt1 + 1 >= 3)] = true;
                        }
                    }
                }
            }
        }
    }
}
 
void make_ans() {
    int flag1 = 0, flag2 = 0;
    for (int cnt0 = 0; cnt0 <= 5; cnt0++) {
        for (int cnt1 = 0; cnt1 <= 3; cnt1++) {
            if (cnt0 && cnt1) break;
            for (int now = 0; now < 2; now++) {
                for (int flag = 0; flag < 2; flag++) {
                    if (!dp[n - 1][cnt0][cnt1][now][flag]) continue;
                    //cout << cnt0 << " " << cnt1 << " " << now << " " << flag << endl;
                    if (flag) 
                        flag2 = 1;
                    else
                        flag1 = 1;
                }
            }
        }
    }
    //cout << flag1 << " " << flag2 << endl;
    if (flag1 && flag2) {
        ans = "42";
    } 
    else if (flag1) {
        ans = "NICE";
    } 
    else if (flag2) {
        ans = "UGLY";
    }
    assert(flag1 || flag2);
}
 
void run() {
    calc();
    make_ans();
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