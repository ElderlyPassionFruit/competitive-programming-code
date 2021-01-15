#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

#define int ll

struct Point{
    int x, y;
    Point() {}
    Point(int _x, int _y) {
        x = _x, y = _y;
    }
};

Point operator-(const Point& a, const Point& b) {
    return Point(a.x - b.x, a.y - b.y);
}

ll operator^(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

#define Vec Point

bool check(vector<Point> a) {
    if (a.size() <= 2) return true;
    for (int i = 2; i < (int)a.size(); ++i) {
        Vec v1 = a[1] - a[0];
        Vec v2 = a[i] - a[0];
        if ((v1 ^ v2) != 0) {
            return false;
        }
    }
    return true;
}

int n;
vector<Point> a;

void read() {
    cin >> n;
    a.resize(n);
    for (auto& i : a) {
        cin >> i.x >> i.y;
    }
}

void yes() {
    cout << "yes\n";
    exit(0);
}

vector<Point> get(Point x, Point y) {
    vector<Point> ans;
    for (auto i : a) {
        Vec v1 = y - x;
        Vec v2 = i - x;
        if ((v1 ^ v2) != 0) {
            ans.push_back(i);
        }
    }
    return ans;
}

void run() {
    if (check(a)) {
        yes();
    }
    for (int i = 0; i < 3; ++i) {
        for (int j = i + 1; j < 3; ++j) {
            if (check(get(a[i], a[j]))) {
                yes();
            }
        }
    }
}

void write() {
    cout << "no\n";
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}