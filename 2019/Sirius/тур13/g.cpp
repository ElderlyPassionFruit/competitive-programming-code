#include <bits/stdc++.h>

using namespace std;
#define int long long
int check_n;

bool check(int x, int y) {
	if ((x <= 0) || (y <= 0) || (x > check_n) || (y > check_n))
		return false;
	cout << "examine " << x << " " << y << endl;
	string ans;
	cin >> ans;
	return ans == "true";
}

void write(int x, int y) {
	cout << "solution " << x << " " << y << endl;
	cout.flush();
	exit(0);
}

int find_l(int x, int y, int n) {
	int l = 1;
	while (true) {
		bool flag = check(x - l, y);
		if (!flag)
			break;
		l *= 2;
	}

	int l1 = 0, r1 = l;
	while (l1 < r1 - 1) {
		int mid = (l1 + r1) / 2;
		bool flag = check(x - mid, y);
		if (flag)
			l1 = mid;
		else 
			r1 = mid;
	}
	return l1;
}

int find_r(int x, int y, int n) {
	int l = 1;
	while (true) {
		bool flag = check(x + l, y);
		if (!flag)
			break;
		l *= 2;
	}

	int l1 = 0, r1 = l;
	while (l1 < r1 - 1) {
		int mid = (l1 + r1) / 2;
		bool flag = check(x + mid, y);
		if (flag)
			l1 = mid;
		else 
			r1 = mid;
	}
	return l1;
}

int find_u(int x, int y, int n) {
	int u = 1;
	while (true) {
		bool flag = check(x, y + u);
		if (!flag)
			break;
		u *= 2;
	}

	int l1 = 0, r1 = u;
	while (l1 < r1 - 1) {
		int mid = (l1 + r1) / 2;
		bool flag = check(x, y + mid);
		if (flag)
			l1 = mid;
		else 
			r1 = mid;
	}
	return l1;
}

int find_d(int x, int y, int n) {
	int u = 1;
	while (true) {
		bool flag = check(x, y - u);
		if (!flag)
			break;
		u *= 2;
	}

	int l1 = 0, r1 = u;
	while (l1 < r1 - 1) {
		int mid = (l1 + r1) / 2;
		bool flag = check(x, y - mid);
		if (flag)
			l1 = mid;
		else 
			r1 = mid;
	}
	return l1;
}

void check1_1(int x, int y, int n, int m) {
	if (!check(x, y)) return;
	
	int x_l = x - 2 * m;
	int x_r = x + 2 * m;

	int y_d = y - 2 * m;
	int y_u = y + 2 * m;

	if (check(x_l, y_u) && check(x_l, y_d) && check(x_r, y_u) && check(x_r, y_d)) {
		write(x, y);
	}
}

signed main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, x, y;

	
	cin >> n >> x >> y;
	check_n = n;
	int l = x - find_l(x, y, n);
	int r = x + find_r(x, y, n);
	int u = y + find_u(x, y, n);
	int d = y - find_d(x, y, n);

	int m = r - l + 1;

	int mx = (l + r) / 2;
	int my = (u + d) / 2;

//	cout << "mx = " << mx << endl;
	//cout << "my = " << my << endl;
//	cout << "m = " << m << endl;

	int dx, dy;
	dx = 2 * m;
	dy = 2 * m;
	check1_1(mx + dx, my + dy, n, m);

	dx = 0;
	dy = 2 * m;
	check1_1(mx + dx, my + dy, n, m);

	dx = -2 * m;
	dy = 2 * m;
	check1_1(mx + dx, my + dy, n, m);

	dx = m;
	dy = m;
	check1_1(mx + dx, my + dy, n, m);

	dx = -m;
	dy = m;
	check1_1(mx + dx, my + dy, n, m);

	dx = 2 * m;
	dy = 0;
	check1_1(mx + dx, my + dy, n, m);

	dx = 0;
	dy = 0;
	check1_1(mx + dx, my + dy, n, m);


	dx = -2 * m;
	dy = 0;
	check1_1(mx + dx, my + dy, n, m);


	dx = m;
	dy = -m;
	check1_1(mx + dx, my + dy, n, m);


	dx = -m;
	dy = -m;
	check1_1(mx + dx, my + dy, n, m);

	dx = 2 * m;
	dy = -2 * m;
	check1_1(mx + dx, my + dy, n, m);

	dx = 0;
	dy = -2 * m;
	check1_1(mx + dx, my + dy, n, m);


	dx = -2 * m;
	dy = -2 * m;
	check1_1(mx + dx, my + dy, n, m);

	return 0;
}