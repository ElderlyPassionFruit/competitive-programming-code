#include<bits/stdc++.h>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;
using dd = long double;
using ldd = long double;
using si = short int;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

ll mod = 1e9 + 9;
ll p = 137;

void solve()
{
    string curr = "";
    string in;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> in;
        //if (i == 0)
            reverse(in.begin(), in.end());
        int del = 0;
        ll mp = 1;
        ll h1 = 0, h2 = 0;
        for (int i = 0; i < min(in.size(), curr.size()); ++i)
        {
            h1 = (h1 * p + curr[curr.size() - 1 - i]) % mod;
            h2 = (h2 + mp * (ll)in[i]) % mod;
            mp = mp * p % mod;
            if (h1 == h2)
                del = i + 1;
        }
        cout << curr << " " << in << endl;
        cout << h1 << " " << h2 << endl;
        for (int i = del; i < in.size(); ++i)
            curr += in[i];
    }
    cout << curr;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
    int t;
    t = 1;
    //cin >> t;
    for (int i = 0; i < t; ++i)
        solve();

    return 0;
}