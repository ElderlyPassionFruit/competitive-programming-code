#include <bits/stdc++.h>

using namespace std;
//#define int long long
signed main()
{
	int n;
	cin >> n;
	vector <int> a(n);
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	if (n <= 2)
	{
		cout << 0;
		return 0;
	}
	bool flag = true;
	long long ans = 0;
	while (flag)
	{
		flag = false;
		for (int i = 1; i < n - 1; i++)
		{
			if (a[i - 1] + a[i + 1] < a[i] * 2)
			{
				flag = true;
				int old = a[i];
				a[i] = (a[i + 1] + a[i - 1]) / 2;
				ans += (long long) old - a[i];
			}
		}
	}
	cout << ans << endl;
	return 0;
}