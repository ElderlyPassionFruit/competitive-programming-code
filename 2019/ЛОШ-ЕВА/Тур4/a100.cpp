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
	if (q == 1) {
		for (auto i : a)
			cout << i << " ";
		cout << endl;
		exit(0);
	}
	if (p == q) {
		cout << a[0] - p + 1 << " "; 
		for (int i = 1; i < q; i++)
			cout << 1 << " ";
		cout << endl;
		exit(0);
	}
}

vector<int> check(int a0) {
	vector<int> ans(p, -1);
	ans[0] = a0;
	int ind_now = 0;
	while (true) {
		int ind_next = (ind_now + q) % p;
		int next_num = ans[ind_now] - a[ind_now] + a[(ind_now + 1) % p];

		if (ans[ind_next] != -1) {
			return ans;
		}

		ans[ind_next] = next_num;
		ind_now = ind_next;
	}
}

void print(vector<int> a) {
	for (auto i : a)
		cout << i << " ";
	cout << endl;
}

void run() {
	//print(check(0));
	//print(check(1));
	//print(check(2));
	//print(check(3));

	auto v = check(0);

	int min_num = 1e9;
	for (auto i : v)
		min_num = min(i, min_num);
	v = check(abs(min_num) + 1);


	/*cout << "v = ";
	for (auto i : v)
		cout << i << " ";
	cout << endl;*/



	int l = -1e9, r = 1e9;
	while (l < r - 1) {
		int mid = (l + r) / 2;

		int sum = 0;
		for (int i = 0; i < q; i++)
			sum += v[i] + mid;
		if (a[0] <= sum)
			r = mid;
		else
			l = mid;
	}

	for (int i = 0; i < p; i++)
		v[i] += r;	
	for (auto i : v)
		cout << i << " ";
	cout << endl;
}

void write() {

}

signed main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}