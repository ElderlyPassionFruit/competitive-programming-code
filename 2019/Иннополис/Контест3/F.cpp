#include <bits/stdc++.h>

using namespace std;

#define int long long
int n;
vector <int> a;
const int MOD = 1e9 + 7;
void read()
{
	cin >> n;
	for (int i = 0 ; i < n; i++)
	{
		int x;
		cin >> x;
		a.push_back(x);
	}
	sort(a.begin(), a.end());
}
int ans;
void run()
{
	ans = 1;
	for (int i = 0; i < n; i++)
	{
		ans *= (a[i] - i);
		ans %= MOD;
	}
}

void write()
{
	cout << ans << endl;
}

signed main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}