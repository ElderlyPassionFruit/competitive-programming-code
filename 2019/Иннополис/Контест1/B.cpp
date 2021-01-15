#include <bits/stdc++.h>

using namespace std;
#define int long long

void read()
{
	int n;
	cin >> n;
	vector <int> a(n);
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	sort(a.begin(), a.end());
	reverse(a.begin(), a.end());
	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		if (i % 3 != 2)
			ans += a[i];
	}
	cout << ans;
}

void run()
{

}

void write()
{

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