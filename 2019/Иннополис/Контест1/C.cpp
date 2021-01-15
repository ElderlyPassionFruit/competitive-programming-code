#include <bits/stdc++.h>

using namespace std;
#define int long long

void read()
{
	string s;
	cin >> s;
	map <char, set <int> >  a;
	for (int i = 0; i < s.length() / 3; i++)
	{
		char type = s[i * 3];
		int x = s[i * 3 + 1] - '0';
		int y = s[i * 3 + 2] - '0';
		int num = x * 10 + y;
		if (a[type].find(num) != a[type].end())
		{
			cout << "GRESKA";
			exit(0);
		}
		a[type].insert(num);
	}
	cout << 13 -a ['P'].size() << " " << 13 - a['K'].size() << " " << 13 - a['H'].size() << " " << 13 - a['T'].size(); 
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