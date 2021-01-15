#include <bits/stdc++.h>
 
using namespace std;
#define int long long
//#define double long double
struct point{
    double x, y;
    point() {
        x = y = 0;
    }
    point (double a, double b) {
        x = a, y = b;
    }
};
 
struct line{
    int a, b, c;
    line() {
        a = b = c = 0;
    }
    line(int x, int y, int z) {
        a = x;
        b = y;
        c = z;
    }
};
 
point cross(line l1, line l2) {
    point ans;
    ans.x = l2.b * l1.c - l1.b * l2.c;
    ans.y = l2.c * l1.a - l1.c * l2.a;
    ans.x /= l1.b * l2.a - l2.b * l1.a;
    ans.y /= l1.b * l2.a - l2.b * l1.a;
    return ans;
}
 
double dist(point a, line l) {
    return abs(l.a * a.x + l.b * a.y + l.c) / (sqrt(l.a * l.a + l.b * l.b));
}
 
const int MAXN = 1e5 + 10, MAXT = 20;
int n, t;
line arr[MAXN], l[MAXT];
void read() {
    cin >> n >> t;
    for (int i = 0; i < n; i++) 
        cin >> arr[i].a >> arr[i].b >> arr[i].c;
    for (int i = 0; i < t; i++) 
        cin >> l[i].a >> l[i].b >> l[i].c;
}
 
bool operator<(point a, point b) {
    if (a.x != b.x)
        return a.x < b.x;
    return a.y < b.y;
}
 
bool cmp(pair <point, line> a, pair <point, line> b) {
    return a.first < b.first;
}
 
void run(){
    for (int i = 0; i < t; i++) {
        vector <pair <point, line> > help;
        for (int j = 0; j < n; j++) {
            point c = cross(l[i], arr[j]);
            help.push_back({c, arr[j]});
        }
        double d = 1e9;
        sort(help.begin(), help.end(), cmp);
 
        for (int j = 0; j < n - 1; j++) {
            point c = cross(help[j].second, help[j + 1].second);
            d = min(d, dist(c, l[i]));
        } 
        cout << d << '\n';
    }
}
void write() {
}
 
signed main() {
    cout.precision(20);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    read();
    run();
    write();
    return 0;
}