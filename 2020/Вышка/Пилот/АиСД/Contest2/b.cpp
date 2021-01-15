#include <bits/stdc++.h>

using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(a) a.begin(), a.end()

using namespace std;

template<typename T1, typename T2> inline void chkmin(T1& x, const T2& y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1& x, const T2& y) {if (x < y) x = y;}

const int A = 7;
int n;
int cnt[A];

void read() {
    cin >> n;
    fill(cnt, cnt + A, 0);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        cnt[x]++;
    }
}

int ans;

void merge(int a, int b) {
    int add = min(cnt[a], cnt[b]);
    ans += add;
    cnt[a] -= add;
    cnt[b] -= add;
}

int Cnt[A];

int solve(int cnt42, int cnt33, int cnt32) {
    for (int i = 0; i < A; ++i) {
        Cnt[i] = cnt[i];
    }
    int ans = cnt42 + cnt33 + cnt32;
    if (min(Cnt[4], Cnt[2]) < cnt42) return n;
    Cnt[4] -= cnt42;
    Cnt[2] -= cnt42;
    ans += Cnt[4];
    //cout << "ans = " << ans << endl; 
    Cnt[1] -= Cnt[4] * 2;
    chkmax(Cnt[1], 0);
    if (Cnt[3] < cnt33 * 2) return n;
    Cnt[3] -= cnt33 * 2;
    if (min(Cnt[3], Cnt[2]) < cnt32) return n;
    Cnt[3] -= cnt32;
    Cnt[2] -= cnt32;
    Cnt[1] -= cnt32;
    chkmax(Cnt[1], 0);
    if (Cnt[3] > 1) return n;
    ans += Cnt[3];
    Cnt[1] -= 3 * Cnt[3];
    chkmax(Cnt[1], 0);
    Cnt[1] += Cnt[2] * 2;
    ans += (Cnt[1] + 5) / 6;
    return ans;
}

void run() {
    cnt[0] = n;
    ans = 0;
    merge(6, 0);
    merge(5, 1);
    merge(5, 0);
    int add = n;
    //cout << solve(0, 0, 0);
    //exit(0);
    for (int cnt42 = 0; cnt42 <= min(cnt[4], cnt[2]); ++cnt42) {
        for (int cnt33 = 0; cnt33 <= cnt[3] / 2; ++cnt33) {
            for (int cnt32 = 0; cnt32 <= min(cnt[3], cnt[2]); ++cnt32) {
                /*if(solve(cnt42, cnt33, cnt32) == 3) {
                    cout << cnt42 << " " << cnt33 << " " << cnt32 << endl;
                }*/
                chkmin(add, solve(cnt42, cnt33, cnt32));
            }
        }
    }
    ans += add;
}

void write() {
    cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    read();
    run();
    write();
    return 0;
}