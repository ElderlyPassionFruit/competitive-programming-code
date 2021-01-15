#include <bits/stdc++.h>

using namespace std;
#define double long double

struct point{
	double x, y;
	point() {
		x = 0, y = 0;
	}
	point(double a, double b) {
		x = a, y = b;
	}
};

struct line {
	int a, b, c;
	line() {
		a = b = c = 0;
	}
	line(point x, point y) {
		a = y.y - x.y;
		b = x.x - y.x;
		c = x.y * y.x - y.y * x.x;
	}
};

double cross(line a, line b) {
	return (double) (a.b * b.c - b.b * a.c) / (b.b * a.a - a.b * b.a);
}

bool operator<(point a, point b) {
	if (a.x != b.x)
		return a.x < b.x;
	return a.y < b.y; 
}

const int MAXN = 1e5 + 10;
deque <point> g[MAXN];
int n;
void wr()  {
	//cout << endl << "puhh" << endl;
}

void read() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int k;
		cin >> k;
		for (int j = 0; j < k; j++) {
			point a;
			cin >> a.x >> a.y;
			g[i].push_back(a);
		}
	}	
	//wr();
	for (int i = 1; i <= n; i++) {
		int cnt = 0;
		while (g[i][0].y != 0 || g[i][1].y == 0) {
	/*		//cout << i << endl;
			for (int j = 0; j < g[i].size(); j++) {
				//cout << j << " " << g[i][j].x << " " << g[i][j].y << endl;
 			}
 			//cout << endl;
	*/		g[i].push_back(g[i][0]);
			g[i].pop_front();
	//		cnt++;
	//		if (cnt > 1)
	//			break;
		}
	}
	//wr();
}

double dist(int a, int b) {
	//cout << endl;
 	point L, R;
 	double l = 1e18, r = -1e18;
 	L = {1e18, 1e18}, R = {-1e18, -1e18};
 	
 	// Поиск граничеых точек. Перемещение a левее b.
 	for (int i = 0; i < g[b].size(); i++) {
 		if (L.x > g[b][i].x)
 			L = g[b][i];
 		r = max(r, g[b][i].x);
 	}

 	for (int i = 0; i < g[a].size(); i++) {
 		if (R.x < g[a][i].x) 
 			R = g[a][i];
 		l = min(l, g[a][i].x);
 	}
 	
 	for (int i = 0; i < g[a].size(); i++) {
 		g[a][i].x += L.x - R.x;
 	}

 	l += L.x - R.x;

 	//cout << "l = " << l << " " << "r = " << r << endl;
 	//cout << "многоугольник a:" << endl;
 	//for (int i = 0; i < g[a].size(); i++) {
 		//cout << "x = " << g[a][i].x << " y = " << g[a][i].y << endl;
 //	} 
 	//cout << "многоугольник b:" << endl;
 	//for (int i = 0; i < g[b].size(); i++) {
 		//cout << "x = " << g[b][i].x << " y = " << g[b][i].y << endl;
 	//} 

 	double fans = 1e18;
 	
 	// Поиск максимальной высоты в b
 	int max_h = 0, pos_h = 0;
 	for (int i = g[b].size() - 1; i >= 0; i--) {
 		if (g[b][i].y >= max_h) {
 			max_h = g[b][i].y;
 			pos_h = i;
 		}
 	}

 //	//cout << "max_h = " << max_h << " pos_h = " << pos_h << endl;

 	// Для каждой точки многоугольника a 
 	// ищем максимально низкую границу сверху 
 	// в левой огибающей многоугольника b
 	////cout << endl;
 	

 	int f_l = pos_h;
 	int f_r = g[b].size() - 1;
 	while (g[b][f_r].y == 0) f_r--;
 	f_r++;
 	for (int i = 0; i < g[a].size(); i++) {
 		if (g[a][i].y > max_h)
 			break;

 		int l = f_l, r = f_r, mid;
 		while (l < r - 1) {
 	//		wr();
 			mid = (l + r) / 2;
 			if (g[b][mid].y >= g[a][i].y) {
 				l = mid;
 			} 
 			else {
 				r = mid;
 			}
 		}

 		//cout << "i = " << i << " " << "l = " << l << endl;
 		line l1;
 		l1.a = 0;
 		l1.b = 1;
 		l1.c = -g[a][i].y;
 		
 		line l2 = line(g[b][l], g[b][(l + 1) % (int) g[b].size()]);

 		fans = min(fans, abs(g[a][i].x - cross(l1, l2)));

 		if (g[a][i].y >= g[a][i + 1].y)
 			break;
 	}

 	max_h = 0, pos_h = 0;
 	for (int i = 0; i < g[a].size(); i++) {
 		if (g[a][i].y > max_h) {
 			pos_h = i;
 			max_h = g[a][i].y;
 		}
 	}


 	for (int i = g[b].size() - 1; i >= 0; i--) {
 		if (g[b][i].y > max_h) 
 			break;
 		int l = 0, r = pos_h + 1, mid;
 		while (l < r - 1) {
 			mid = (l + r) / 2;
 			if (g[a][mid].y <= g[b][i].y) {
 				l = mid;
 			} 
 			else {
 				r = mid;
 			}
 		}

 		line l1;
 		l1.a = 0;
 		l1.b = 1;
 		l1.c = -g[b][i].y;

 		line l2 = line(g[a][l], g[a][(l + 1) % (int) g[a].size()]);

 		fans = min(fans, abs(g[b][i].x - cross(l1, l2)));

 		if (g[b][i].y >= g[b][i - 1].y)
 			break;
 	}
 	//cout << "fans = " << fans << endl;

 	for (int i = 0; i < g[a].size(); i++) {
 		g[a][i].x += fans;
 	}

 	l = 1e18;
 	r = -1e18;

 	for (int i = 0; i < g[a].size(); i++)
 		l = min(l, g[a][i].x), r = max(r, g[a][i].x);
 	for (int i = 0; i < g[b].size(); i++)
 		r = max(r, g[b][i].x), l = min(l, g[b][i].x);
 	//cout << "r = " << r << " l = " << l << endl;
 	return r - l;
} 


int q;
vector <double> ans;
void run() {
	cin >> q;
	//wr();
	map <pair <int, double> , double> help;
	set <pair <int, double> > help2;
	for (int i = 0; i < q; i++) {
		int a, b;
		cin >> a >> b;
		if (a > b) swap(a, b);
		double ax;
		if (help2.find({a, b}) != help2.end())
			ax = help[{a, b}];
		else {
			ax = min(dist(a, b), dist(b, a));
			help[{a, b}] = ax;
			help2.insert({a, b});
		}
		ans.push_back(ax);
	}
}

void write() {
	for (auto i : ans) {
		cout << i << endl;
	}
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