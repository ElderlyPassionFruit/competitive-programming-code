#include <bits/stdc++.h>

using namespace std;

#define int long long

vector <int> a, b;

void read()
{
	a.clear();
	b.clear();
	string s;
	cin >> s;
	int n = s.length();
	for (int i = 0; i < n; i++)
	{
		if (s[i] > '9' || s[i] < '0')
			break;
		a.push_back(s[i] - '0');
	}
	cin >> s;
	n = s.length();
	for (int i = 0; i < n; i++)
	{
		if (s[i] > '9' || s[i] < '0')
			break;
		b.push_back(s[i] - '0');
	}
}

pair <vector <int>, bool> get(vector <int> p, bool flag)
{
	if (flag)
	{
		p[p.size() - 1] += 1;
	}

	for (int i = p.size() - 1; i > 0; i--){
		if (p[i] > 9){
			p[i] -= 10;
			p[i - 1]++;
		}
	}
	int fans = flag && p[0] > 9;
	if (p[0] > 9)
	{
		p[0] -= 10;
	}
	return {p, fans};
}

vector <int> ans;
void run()
{
	ans.clear();
	int s1 = a.size();
	int s2 = b.size();

	int lcm = s1*s2/__gcd(s1, s2);
	//cout << endl << s1 << " " << s2 << " " << lcm << endl;

	for (int i = 0; i < lcm/s1 - 1; i++)
	{
		for (int j = 0; j < s1; j++)
		{
			a.push_back(a[j]);
		}
	}

	for (int i = 0; i < lcm/s2 - 1; i++)
	{
		for (int j = 0; j < s2; j++)
		{
			b.push_back(b[j]);
		}
	}

	/*cout << endl << "a: " << endl;
	for (auto i : a)
	{
		cout << i << " ";
	}
	cout << endl << "b: " << endl;
	for (auto i : b)
	{
		cout << i << " ";
	}
	cout << endl;
*/
	vector <int> fans(lcm, 0);
	for (int i = 0; i < lcm; i++)
	{
		fans[i] = a[i] + b[i];
	}

	auto p = get(fans, 1);
	if (p.second == 0)
		p = get(fans, 0);
	fans = p.first;
	ans.clear();
	int q;
	cin >> q;
	while (q--)
	{
		int x;
		cin >> x;
		x--;
		x %= lcm;
		ans.push_back(fans[x]);
	}
}

int cnt = 0;
void write()
{
	cnt++;
		for (auto i : ans)
			cout << i;
	cout << endl;
}


signed main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while(t--)
	{
		read();
		run();
		write();
	}
	return 0;
}