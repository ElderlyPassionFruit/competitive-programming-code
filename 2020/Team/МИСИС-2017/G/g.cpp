#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double

const double eps = 1e-9;

double f(double x, pair <int, int> a) {
    return (x - a.first) * (x - a.first) + a.second;
}

pair <int, pair <double, double> > check(pair <int, int> a, pair <int, int> b) {
    if (a.first == b.first) return {0, {-1, -1}};
    if (a.first > b.first) swap(a, b);
    double l = -1e18 + 0.0, r = 1e18 + 0.0;
    //cout << a.first << ' ' << a.second << ' ' << b.first << ' ' << b.second << '\n';
    int cnt = 0;
    while (cnt < 100) {
        double m = (l + r) / 2.0;
        //cout << m << ' ' << f(m, a) << ' ' << f(m, b) << '\n';
        if (f(m, a) <= f(m, b)) l = m;
        else r = m;
        ++cnt;
    }
    return {1, {l, f(l, a)}};
}

void solve() {
    int n;
    cin >> n;
    set <pair <int, int> > a;
    for (int i = 0; i < n; ++i) {
        int v1, v2;
        cin >> v1 >> v2;
        a.insert({v1, v2});
    }
    int cnt = 0;
    vector <pair <int, int> > b;
    for (auto el : a) b.push_back(el);
    vector <pair <double, double> > ans;
    //for (int i = 0; i < b.size(); ++i) ans.push_back({b[i].first + 0.0, b[i].second + 0.0});
    for (int i = 0; i < b.size(); ++i) {
    	ans.clear();
        for (int j = i + 1; j < b.size(); ++j) {
            auto res = check(b[i], b[j]);
            if (res.first) ans.push_back(res.second);
            //cout << b[i].first << ' ' << b[i].second << ' ' << b[j].first << ' ' << b[j].second << ' ' << res.second.first << ' ' << res.second.second << '\n';
        }
	    for (int i = 0; i < ans.size(); ++i) {
	        bool ch = 0;
	        for (int j = i - 1; j >= 0; --j) {
	            if (abs(ans[i].first - ans[j].first) <= eps && abs(ans[i].second - ans[j].second) <= eps) {
	                ch = 1;
	                break;
	            }
	        }
	        if (!ch) ++cnt;
	    }
    }
    cout << cnt + 1 + b.size();
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}
