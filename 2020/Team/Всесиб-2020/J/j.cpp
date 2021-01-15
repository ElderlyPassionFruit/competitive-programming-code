#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct Point{
    ld x, y;
    Point() {}
    Point(ld _x, ld _y) {
        x = _x, y = _y;
    }
};

struct Line{
    ld k, b;
    Line() {}
    Line(Point x, Point y) {
        k = (ld)(x.y - y.y) / (x.x - y.x);
        b = (ld)(x.x * y.y - x.y * y.x) / (x.x - y.x);
    }
};

const int N = 310;
int n;
Point a[N];

ld ans;
Line fans;

void relax(Line l) {
    ld myAns = 0;
    for (int i = 0; i < n; ++i) {
        myAns += abs(a[i].y - (l.k * a[i].x + l.b));
    }
    if (ans <= myAns) return;
    ans = myAns;
    fans = l; 
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.setf(ios::fixed), cout.precision(20);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i].y;
    }
    for (int i = 0; i < n; ++i) {
        cin >> a[i].x;
    }
    ans = 1e20;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            relax(Line(a[i], a[j]));
            //cout << Line(a[i], a[j]).k << " " << Line(a[i], a[j]).b << endl; 
        }
    }
    cout << ans << " " << fans.k << " " << fans.b << endl;
	return 0;
}