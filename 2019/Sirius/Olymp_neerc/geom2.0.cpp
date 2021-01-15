#include <bits/stdc++.h>
 
using namespace std;
 
#define int long long
const long double INF = 1e18;
const int MAXN = 210;
 
struct point{
    long double x, y;
    point() {
        x = 0, y = 0;
    }
    point(long double a, long double b) {
        x = a, y = b;
    }
};
 
struct line{
    long double a, b, c;
    line() {
        a = b = c = 0;
    }
    line(long double a1, long double b1, long double c1) {
        a = a1, b = b1, c = c1;
    }
    line(point x, point y) {
        a = y.y - x.y;
        b = x.x - y.x;
        c = x.y * y.x - y.y * x.x;
    }
};
 
point cross(line a1, line a2) {
    point ans;
    ans.x = a2.b * a1.c - a1.b * a2.c;
    ans.y = a2.c * a1.a - a1.c * a2.a;
    ans.x /= a1.b * a2.a - a2.b * a1.a;
    ans.y /= a1.b * a2.a - a2.b * a1.a;
    return ans;
}
 
point operator+(point a, point b) {
    return point(a.x + b.x, a.y + b.y);
}
 
const long double EPS = 1e-9;
bool check(point a, point b, point x) {
    if (a.x > b.x)
        swap(a, b);
    long double A = b.y - a.y;
    long double B = a.x - b.x;
    long double C = a.y * b.x - b.y * a.x;
    if (abs(A * x.x + B * x.y + C) < EPS && (x.x >= a.x) && (x.x <= b.x))
        return true;
    return false; 
}
 
 
vector <point> is[MAXN];
 
vector <pair<int, long double> > g[MAXN];
long double d[MAXN][MAXN];
 
int n, a, b;
long double ans;
 
long double sq(long double x) {
    return x * x;
}
 
long double dist(point a, point b) {
    return sqrt(sq(a.x - b.x) + sq(a.y - b.y));
}
 
long double dist(point a, point b, point x) {
    long double ans = min(dist(a, x), dist(b, x));
    long double A = b.y - a.y;
    long double B = a.x - b.x;
    long double C = a.y * b.x - b.y * a.x;
 
    point norm(B, A);
    point cr = cross(line(a, b), line(x, x + norm));
    if (check(a, b, cr))
    {
        long double fans = A * x.x + B * x.y + C;
        fans /= sqrt(A * A + B * B);
        fans = abs(fans);
        ans = min(ans, fans);
    }
    return ans; 
}
 
long double dist(point a, point b, point c, point d) {
    long double ans = INF;
    ans = min(ans, dist(a, b, c));
    ans = min(ans, dist(a, b, d));
    ans = min(ans, dist(c, d, a));
    ans = min(ans, dist(c, d, b));
    return ans;
}
 
long double dist(vector <point> &p1, vector <point> &p2) {
    long double ans = INF;
    for (int i = 0; i < p1.size(); i++) {
        for (int j = 0; j < p2.size(); j++) {
            point a = p1[i];
            point b = p1[(i + 1) % (int) p1.size()];
            point c = p2[j];
            point d = p2[(j + 1) % (int) p2.size()];
            ans = min(ans, dist(a, b, c, d));
    /*  
            cout << "b = " << b.x << " " << b.y << endl;
 
            cout << "c = " << c.x << " " << c.y << endl;
 
            cout << "d = " << d.x << " " << d.y << endl;
            cout << "dist = " << dist(a, b, c, d) << endl;*/
        }
    }
    return ans;
}
 
 
void read() {
    cin >> n >> a >> b;
    a--;
    b--;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            point x;
            cin >> x.x >> x.y;
            is[i].push_back(x);
        }
    }
}
 
void run() {
	//Построение графа
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			double D = dist(is[i], is[j]);
		//	cout << "i = " << i << " j = " << j << " D = " << D << endl;
			d[i][j] = D;
			d[j][i] = D;
		}
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
	ans = d[a][b];
}
 
void write() {
    cout << ans << endl;
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