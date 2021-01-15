#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

const int N = 3e5 + 10;
int n;
pair<int, int> a[N];

pair<int, int> readS() {
	string s;
	cin >> s;
	pair<int, int> ans = {0, 0};
	for (auto i : s) {
		ans.first += i == 'B';
		ans.second += i == 'N';
	}
	return ans;
}

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		a[i] = readS();
	}
	cout << "a = " << endl;
	for (int i = 0; i < n; i++) {
		cout << "(" << a[i].first << ", " << a[i].second << ")" << endl;
	}
}

const pair<int, int> INF = {-1, -1};
vector<pair<int, int>> myMin;

bool check(pair<int, int> a, pair<int, int> b, int dist) {
	if (a > b) return check(b, a, dist);
	if (a.first < b.first && a.second < b.second) {
		return b.first - a.first + b.second - a.second - min(b.first - a.first, b.second - a.second) <= dist;
	} else {
		return abs(a.first - b.first) + abs(a.second - b.second) <= dist;
	}
}

vector<pair<int, int>> get(pair<int, int> myMin, int dist) {
	vector<pair<int, int>> fans;
	fans.push_back(myMin);
	fans.push_back({myMin.first + dist, myMin.second});
	fans.push_back({myMin.first + dist, myMin.second + dist});
	fans.push_back({myMin.first, myMin.second + dist});
	fans.push_back({myMin.first, myMin.second - dist});
	fans.push_back({myMin.first - dist, myMin.second});
	fans.push_back({myMin.first - dist, myMin.second - dist});
	return fans;
}

mt19937 rnd(time(0));

pair<int, int> getP(int dist) {
	vector<pair<int, int>> fans;
	for (auto i : myMin) {
		auto add = get(i, dist);
		for (auto x : add) {
			fans.push_back(x);
		}
		//fans.push_back(get(i, dist));
	}
	for (int i = 0; i < 40; i++) {
		auto add = get(a[(int)rnd() % n], dist);
		for (auto x : add) {
			fans.push_back(x);
		}
	}
	vector<bool> ok(fans.size(), true);
	/*cout << "fans = " << endl;
	for (auto j : fans) {
		cout << "(" << j.first << ", " << j.second << ")" << endl;	
	}*/
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < (int)fans.size(); j++) {
			ok[j] = ok[j] && check(fans[j], a[i], dist);
		}
	}
	for (int i = 0; i < (int)fans.size(); i++) {
		if (ok[i]) {
			return fans[i];
		}
	}
	return INF;
}

bool check(int dist) {
	return getP(dist) != INF;
}

int ansDist;
string ansS;

void makeAns(int dist) {
	ansDist = dist;
	auto have = getP(dist);
	ansS = "";
	for (int i = 0; i < have.first; i++) {
		ansS += 'B';
	}
	for (int i = 0; i < have.second; i++) {
		ansS += 'N';
	}
}

void run() {
	myMin.push_back(*min_element(a, a + n));
	myMin.push_back(*min_element(a, a + n, [&] (pair<int, int> x, pair<int, int> y) {return tie(x.second, y.first) < tie(y.second, x.first);}));
	myMin.push_back(*max_element(a, a + n));
	myMin.push_back(*max_element(a, a + n, [&] (pair<int, int> x, pair<int, int> y) {return tie(x.second, y.first) < tie(y.second, x.first);}));
	int l = -1, r = 1e6 + 228;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid)) {
			r = mid;
		} else {
			l = mid;
		}
	}
	makeAns(r);
}

void write() {
	cout << ansDist << "\n";
	cout << ansS << "\n";
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	read();
	run();
	write();
	return 0;
}