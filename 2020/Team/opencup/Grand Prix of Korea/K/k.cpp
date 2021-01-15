#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct Pt{
    int x, y, ind;
};

Pt operator-(const Pt& a, const Pt& b) {
    return {a.x - b.x, a.y - b.y, 0};
}

ll operator^(const Pt& a, const Pt& b) {
    return (ll)a.x * b.y - (ll)a.y * b.x;
}

int sign(ll x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

ll dist(Pt a) {
    return (ll)a.x * a.x + (ll)a.y * a.y;
}

const int N = 1010;
int n;
Pt a[N];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i].x >> a[i].y;
        a[i].ind = i + 1;
    }
    int pos = min_element(a, a + n, [] (Pt x, Pt y) {return tie(x.x, x.y) < tie(y.x, y.y);}) - a;
    swap(a[0], a[pos]);
    sort(a + 1, a + n, [] (Pt x, Pt y){
        Pt vx = x - a[0];
        Pt vy = y - a[0];
        if (sign(vx ^ vy) == 0) {
            return dist(vx) < dist(vy);
        }
        return sign(vx ^ vy) == 1;
    });
    /*cout << "a = " << endl;
    for (int i = 0; i < n; ++i) {
        cout << a[i].x << " " << a[i].y << " " << a[i].ind << endl;
    }*/
    vector<int> ans;
    ans.push_back(a[0].ind);
    for (int l = 1; l < n; ++l) {
        int r = l;
        while (r < n && sign((a[l] - a[0]) ^ (a[r] - a[0])) == 0) ++r;
        for (int i = l; i < r; ++i) {
            ans.push_back(a[i].ind);
        }
        for (int i = r - 2; i >= l; --i) {
            ans.push_back(a[i].ind);
        }
        ans.push_back(a[0].ind);
        l = r - 1;
    }
    cout << ans.size() << "\n";
    for (auto i : ans) {
        cout << i << " ";
    }
    cout << "\n";
	return 0;
}