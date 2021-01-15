#include <bits/stdc++.h>

using namespace std;
#define int long long

int p, q;
vector<int> a;
void read() {
	cin >> p >> q;
	a.resize(p);
	for (auto &i : a)
		cin >> i;
}

bool check(vector<int> ans) {
	int sum = 0;
	for (int i = 0; i < q; i++)
		sum += ans[i];

	for (int i = 0; i < p; i++) {
		if (sum != a[i])
			return false;
		sum -= ans[i];
		sum += ans[(i + q) % p];
	}
	return true;
}

void check(int a0) {
	vector<int> ans(p, -1);
	ans[0] = a0;
	int ind_now = 0;
	while (true) {
		int ind_next = (ind_now + q) % p;
		int next_num = ans[ind_now] - a[ind_now] + a[(ind_now + 1) % p];
		if (next_num < 1)
			return;

		if (ans[ind_next] != -1) {
			if (ans[ind_next] != next_num)
				return;
			if (!check(ans))
				return;
			for (auto i : ans)
				cout << i << " ";
			cout << endl;
			exit(0);
		}

		ans[ind_next] = next_num;
		ind_now = ind_next;
	}
}

void run() {
	for (int i = 1; i <= 100000; i++) {
		check(i);
	}
}

void write() {

}

signed main() {
	
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}