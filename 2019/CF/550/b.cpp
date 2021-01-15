#include <bits/stdc++.h>

using namespace std;
#define int long long
int n;
const int MAXN = 2010;
int arr[MAXN];
int ans;
void read() {
	cin >> n;
	ans = 0;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];	
		ans += arr[i];
	}
}

void run() {
	int cnt0 = 0, cnt1 = 0;
	for (int i = 0; i < n; i++) {
		if (arr[i] % 2 == 0)
			cnt0++;
		else
			cnt1++;
	}
	cnt0 = min(cnt0, cnt1 + 1);
	cnt1 = min(cnt1, cnt0 + 1);

	sort(arr, arr + n);
	reverse(arr, arr + n);
	for (int i = 0; i < n; i++) {
		if (arr[i] % 2 == 0 && cnt0 > 0) {
			ans -= arr[i];
			cnt0--;
		}
		if (arr[i] % 2 == 1 && cnt1 > 0) {
			ans -= arr[i];
			cnt1--;
		}
	}
}

void write() {
	cout << ans << endl;
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