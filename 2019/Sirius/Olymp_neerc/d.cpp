#include <bits/stdc++.h> 


using namespace std;


#define int long long 


struct point
{
	double x, y;
	point(double val1, double val2)
	{
		x = val1;
		y = val2;
	}
	point()
	{
		x = 0;
		y = 0;
	}
};


struct line
{
	double a, b, c;
	line()
	{
		a = 0;
		b = 0;
		c = 0;
	}
	line(point A, point B)
	{
		a = (B.y - A.y);
		b = (A.x - B.x);
		c = ((-1) * (a * A.x + b * A.y));
	}
	line(double val1, double val2, double val3)
	{
		a = val1;
		b = val2;
		c = val3;
	}
};


point operator+(point a, point b)
{
	point c(a.x + b.x, a.y + b.y);
	return c;
}


point operator-(point a, point b)
{
	point c(a.x - b.x, a.y - b.y);
	return c;
}


double operator*(point a, point b)
{
	return a.x * b.x + a.y * b.y;
}


double operator^(point a, point b)
{
	return a.x * b.y - a.y * b.x;
}


double twSpace(point a, point b, point c)
{
	return (a - b) ^ (c - b);
}


double dist(point a, point b)
{
	double f = a.x - b.x, s = a.y - b.y;
	return sqrt(f * f + s * s);
}


double lineDist(point a, point b, point c)
{
	return (double)(abs(twSpace(a, b, c))) / dist(b, c);
}


double rayDist(point a, point b, point c)
{
	if (((c - b)*(a - b)) < 0)
	{
		return dist(a, b);
	}
	return lineDist(a, b, c);
}


double segmentDist(point a, point b, point c)
{
	if (((c - b)*(a - b)) < 0)
	{
		return dist(a, b);
	}
	if (((b - c)*(a - c)) < 0)
	{
		return dist(a, c);
	}
	return lineDist(a, b, c);
}

bool insideAngle(point a, point o, point b, point p)
{
	if (((b - o) ^ (a - o)) < 0)
	{
		swap(a, b);
	}
	if (((b - o) ^ (p - o)) >= 0 && ((a - o) ^ (p - o)) <= 0)
	{
		return true;
	}
	return false;
}



bool rayCross(point a, point b, point c, point d)
{
	if (((b - a) ^ (c - a)) == 0)
	{
		return (rayDist(c, a, b) == 0) || (rayDist(a, c, d) == 0);
	}
	return insideAngle(a, c, c + b - a, d) && ((b - a) ^ (d - c)) != 0;
}


bool segmentCross(point a, point b, point c, point d)
{
	return (rayCross(a, b, c, d)) && (rayCross(b, a, c, d)) && (rayCross(a, b, d, c)) && (rayCross(b, a, d, c));
}


double segmentSegmentDist(point a, point b, point c, point d)
{
	if (segmentCross(a, b, c, d))
	{
		return 0.0;
	}
	return min(min(segmentDist(a, c, d), segmentDist(b, c, d)), min(segmentDist(c, a, b), segmentDist(d, a, b)));
}

const double INF = 1e18;
const int MAXN = 210;

vector <point> is[MAXN];

vector <pair<int, double> > g[MAXN];
double d[MAXN][MAXN];

int n, a, b;
double ans;

double dist(vector <point> &p1, vector <point> &p2) {
	double ans = INF;
	int sz1 = p1.size(), sz2 = p2.size();
	for (int i = 0; i < p1.size(); i++) {

		for (int j = 0; j < p2.size(); j++) {

			point a = p1[i];
			point b = p1[(i + 1) % sz1];

			point c = p2[j];
			point d = p2[(j + 1) % sz2];
			ans = min(ans, segmentSegmentDist(a, b, c, d));
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
	if (ans < 0)
		while(true)
			cout << "puhh\n";
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