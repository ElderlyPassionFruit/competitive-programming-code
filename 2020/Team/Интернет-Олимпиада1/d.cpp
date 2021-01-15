#include <bits/stdc++.h>
#include <cstdio>
#include <cstdint>
using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()

const int MAXN = 1e6 + 1;
vector<int> pr;
int lp[MAXN], cnt[MAXN];

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.precision(20);

    for(int i = 2; i < MAXN; i++) {
        if(!lp[i]) {
            lp[i] = i;
            pr.push_back(i);
        }
        for(int j = 0; j < pr.size() && pr[j] * i < MAXN && pr[j] <= lp[i]; j++) {
            lp[i * pr[j]] = pr[j];
        }
    }

    int n;
    cin >> n;
    vector<ll> a(n);
    for(ll &i : a) 
        cin >> i;
    
    for(int i = 0; i < n; i++) {
        for(int j : pr) {
            if(a[i] %j ==0 ) {
                cnt[j]++;
            }
            while(a[i] % j == 0) a[i] /= j;
        }
    }

    int ans = 0;
    for(int i = 2; i < MAXN; i++) ans = max(ans, cnt[i]);
    for(int i = 0; i < n; i++)
    {
        map<ll,int> cc;
        for(int j = 0; j < n; j++) {
            if(i == j) continue;
            ll x = __gcd(a[i], a[j]);
            if(x > 1)
                cc[x]++;
        }
        for(auto j : cc) {
            ans = max(ans, j.second + 1);
        }
    }
    cout << ans;
    return 0;
}