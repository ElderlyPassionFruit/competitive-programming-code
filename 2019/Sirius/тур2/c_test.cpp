#include <bits/stdc++.h>
 
using namespace std;
#define int long long
 
const int INF = 1e18;

struct line {
    int k, b;
    line() {
        k = 0;
        b = INF;
    }
    line(int k1, int b1) {
        k = k1;
        b = b1;
    }
};

int eval(line a, int x) {
    return a.k * x + a.b;
}

const int MAXH = 1e6 + 10;
line tree[4 * MAXH];

void upd(line val, int v = 1, int tl = 0, int tr = MAXH) {
    int tm = (tl + tr) / 2;
    bool left = eval(tree[v], tl) > eval(val, tl);
    bool mid = eval(tree[v], tm) > eval(val, tm);
 /*   cout << "upd: " << endl;
    cout << val.k << " " << val.b << endl;
    cout << left << " " << mid << endl;
    cout << endl;*/
    if (mid) 
        swap(val, tree[v]);
    if (tl == tr - 1)
        return;
    if (left != mid)
        upd(val, v * 2, tl, tm);
    else
        upd(val, v * 2 + 1, tm, tr);
}

int get(int pos, int v = 1, int tl = 0, int tr = MAXH){
    if (tl > pos || tr <= pos)
        return INF;
    if (tl == tr - 1)
        return eval(tree[v], pos);
    int tm = (tl + tr) / 2;
    return min(eval(tree[v], pos), min(get(pos, v * 2, tl, tm), get(pos, v * 2 + 1, tm, tr)));
}
 
int n;
const int MAXN = 1e5 + 10;
int h[MAXN], w[MAXN], dp[MAXN];
void read() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }   
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
}
 
int pref[MAXN];
 
int sq(int x) {
    return x*x;
}
 
void wr() {
    for (int i = 0; i <= n; i++)
        cout << dp[i] << " ";
    cout << endl;
}
 
void run() {
    for (int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] + w[i];
    }
 
    /*dp[1] = 0;
    for (int i = 2; i <= n; i++) {
        dp[i] = INF;
        for (int j = 1; j < i; j++) {
            dp[i] = min(dp[i], dp[j] + sq(h[i] - h[j]) + pref[i - 1] - pref[j]);
        }
    }*/
  //  wr();

    dp[1] = 0;
    upd(line(-2*h[1], sq(h[1]) + dp[1] - pref[1]));
    for (int i = 2; i <= n; i++) {
        dp[i] = get(h[i]) + sq(h[i]) + pref[i - 1];
        upd(line(-2*h[i], sq(h[i]) + dp[i] - pref[i]));
    }
  //  wr();
}
 
void write() {
    cout << dp[n] << endl;
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