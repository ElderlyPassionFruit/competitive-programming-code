#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(), (x).end()
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 100;
int a[MAXN][MAXN];

void build() {
	int it = 1;
	for (int i = 0; i < MAXN; i++) {
		for (int x = 0; i - x >= 0 && x < MAXN; x++) {
			a[x][i - x] = it++;
		}
	}
	cout << "a = " << endl;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

vector<int> dp[MAXN][MAXN];

void add(vector<int> & a, vector<int> & b, int x) {
	for (auto i : b)
		a.push_back(i + x);
	sort(all(a));
	a.resize(unique(all(a)) - a.begin());
}

bool check(vector<int> & a) {
	assert(!a.empty());
	return a.back() - a[0] + 1 == a.size();
}

vector<int> get(int x1, int y1, int x2, int y2) {
	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < MAXN; j++)
			dp[i][j].clear();
	x1--;
	y1--;
	x2--;
	y2--;
	dp[x1][y1] = {a[x1][y1]};
	for (int i = x1; i <= x2; i++) {
		for (int j = y1; j <= y2; j++) {
			if (i > 0) add(dp[i][j], dp[i - 1][j], a[i][j]);
			if (j > 0) add(dp[i][j], dp[i][j - 1], a[i][j]);
		}
	}
	return dp[x2][y2];
}

int get_l(int x1, int y1, int x2, int y2) {
	x1--;
	y1--;
	x2--;
	y2--;
	int ans = 0;
	for (int i = y1; i <= y2; i++)
		ans += a[x1][i];
	for (int j = x1 + 1; j <= x2; j++)
		ans += a[j][y2];
	return ans;
}

int get_r(int x1, int y1, int x2, int y2) {
	x1--;
	y1--;
	x2--;
	y2--;
	int ans = 0;
	for (int i = y1; i <= y2; i++)
		ans += a[x2][i];
	for (int j = x1; j < x2; j++)
		ans += a[j][y1];
	return ans;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    build();
    
    /*while (true) {
    	int x1, y1, x2, y2;
    	cin >> x1 >> y1 >> x2 >> y2;
    	cout << "ans = " << endl;
    	auto a = get(x1, y1, x2, y2);
    	cout << "check = " << check(a) << " L = " << a[0] << " R = " << a.back() << " cnt = " << a.size() << " getL = " << get_l(x1, y1, x2, y2) << " getR = " << get_r(x1, y1, x2, y2) << endl; 
    }*/
    for (int x1 = 1; x1 <= 30; x1++) {
    	for (int y1 = 1; y1 <= 30; y1++) {
    		for (int x2 = x1; x2 <= 30; x2++) {
    			for (int y2 = y1; y2 <= 30; y2++) {
    				auto a = get(x1, y1, x2, y2);
    				assert(check(a));
    				assert(a[0] == get_l(x1, y1, x2, y2));
    				assert(a.back() == get_r(x1, y1, x2, y2));	
    				assert(a.size() == (x2 - x1) * (y2 - y1) + 1);
    				cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
    			}
    		}
    	}
    }
    return 0;
}