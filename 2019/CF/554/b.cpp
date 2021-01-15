#include <bits/stdc++.h>

using namespace std;
#define int long long
int x;
void read() {
	cin >> x;
	if (x == 0) {
		cout << 0 << endl;
		exit(0);
	}
}

int pows(int a, int b) {
	int ans = 1;

	for (int i = 0; i < b; i++)
		ans *= a;
	return ans;
}

bool check(int x) {
	while (x % 2 == 0) { 
			x /= 2;
	}
	return x == 1;
}

void wr(int x) {
	vector <int> ans;
	while (x) {
		ans.push_back(x % 2);
		x /= 2;
	}
	reverse(ans.begin(), ans.end());
	for (auto i : ans)
		cout << i;
	cout << endl;
}

bool kek(int x) {
	while (x) {
		if (x % 2 == 0)
			return false;
		x /= 2;
	}
	return true;
}

vector <int> ans;
void run() {
	if (x % 2 == 0) {
		ans.push_back(0);
		x++;
	}
	while (!kek(x)){
		int cnt = 0;
		int a = x;
		bool flag = false;
		while (a) {
			if (a % 2 == 0) {
				flag = true;
			}
			else {
				if (flag)
					break;
			}
			a /= 2;
			cnt++;
		}

		ans.push_back(cnt);		
		x = x ^ (pows(2, cnt) - 1);
		x++;
	}
}


void write() {
	cout << ans.size() * 2 << endl;
	for (auto i : ans)
		cout << i << " ";
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