#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

mt19937 rnd(time(0));

int l_energy, r_energy, l_food, r_food;
int n;
void read() {
	cout << "Введите ограничения сверху-снизу на энергию и хавчик:" << endl;
	cin >> l_energy >> r_energy >> l_food >> r_food;
	cout << "Введите кол-во конфет" << endl;
	cin >> n;
}

vector<pair <int, int> > ans;

int get(int l, int r) {
	return rnd() % (r - l + 1) + l;
}

void run() {
	for (int i = 0; i < n; i++) {
		int x, y;
		x = get(l_energy, r_energy);
		y = get(l_food, r_food);
		ans.push_back({x, y});
	}
}

void out(int x) {
	if (x < 0) {
		cout << x;
	}
	if (x >= 0) {
		cout << " " << x;
	} 
}

void write() {
	cout << "энергия - хавчик" << endl;
	for (auto i : ans) {
		cout << "   ";
		out(i.first);
		cout << "      ";
		out(i.second); 
		cout << endl;
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}