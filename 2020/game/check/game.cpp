#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int CNT = 10;

struct event{
	int energy, food;
	event() {}
};

int start;
int n;
vector<event> sweet;

void read() {
	cin >> start;
	cin >> n;
	sweet.resize(n);
	for (auto &i : sweet) {
		cin >> i.energy >> i.food;
	}
}

mt19937 rnd(time(0));

bool get_first(event a) {
	return rnd() % 2;
}

bool get_second(event a) {
	return rnd() % 2;
}

bool get(int type, event a) {
	if (type == 0)
		return get_first(a);
	else
		return get_second(a);
}

void relax(bool flag, int & energy, int & food, event a) {
	if (flag) {
		energy += a.energy;
		food += a.food;
	}
	else{
		energy--;
	}
}

void check(int energy, bool & flag) {
	if (energy <= 0) flag = false;
}

bool check(int first, int second, vector<event> sweet) {
	reverse(sweet.begin(), sweet.end());
	int now = first;
	
	int energy1 = start, energy2 = start;
	int food1 = 0, food2 = 0;
	bool can1 = true, can2 = true;

	while (!sweet.empty() && (can1 || can2)) {
		event a = sweet.back();
		sweet.pop_back();
		if (can1 && can2) {
			bool flag = get(now, a);
			if (now == first) {
				relax(flag, energy1, food1, a);
			}
			else {
				relax(flag, energy2, food2, a);
			}
		}
		else if (can1) {
			bool flag = get(first, a);
			relax(flag, energy1, food1, a);
		}
		else if (can2) {
			bool flag = get(second, a);
			relax(flag, energy2, food2, a);
		}
		else {
			assert(false);
		}
		check(energy1, can1);
		check(energy2, can2);
		now = 1 - now;
	}
	return food1 > food2;
}

int first, second;

void run() {
	first = 0;
	second = 0;
	for (int i = 0; i < CNT; i++) { 
		first += check(0, 1, sweet);
		second += check(1, 0, sweet);
	}
}

void write() {
	cout << first << " " << second;
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