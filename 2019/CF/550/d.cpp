#include <bits/stdc++.h>

using namespace std;
#define int long long
int n;
const int MAXN = 2e5 + 10;
int arr[MAXN];
map <int, int> a; 	
void read() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
		a[arr[i]]++;
	}
}

vector <vector <int> > ans;

void run() {
	int fans, cnt;
	cnt = -1;
	fans = -1;
	for (auto i : a) {
		if (i.second > cnt) {
			cnt = i.second;
			fans = i.first;
		}
	}

	arr[0] = fans;

	cout << n - cnt << endl;
	for (int i = 1; i <= n; i++) {
		if (arr[i] == fans) {
			int pos = i - 1;
			while (pos > 0 && arr[pos] != fans) {
				if (arr[pos] > fans) {
					cout << 2 << " " << pos << " " << pos + 1 << '\n';
				}
				else {
					cout << 1 << " " << pos << " " << pos + 1 << '\n';
				}
				arr[pos] = fans;
				pos--;
			}
			pos = i + 1;
			while (pos <= n && arr[pos] != fans) {
				if (arr[pos] > fans) {
					cout << 2 << " " << pos << " " << pos - 1 << '\n';
				}
				else {
					cout << 1 << " " << pos << " " << pos - 1 << '\n';
				}
				arr[pos] = fans;
				pos++;
			}
		}
	}
}

void write() {

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