#include <bits/stdc++.h>

using namespace std;
#define int long long

int n, d;
vector <int> p, s, v;
void read()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		p.push_back(x);
	}	
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		s.push_back(x);
	}
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		v.push_back(x);
	}
	cin >> d;
}

const int MAXN = 1e6 + 10;
int pref[MAXN];
int ans;


int get()
{
	int pos = 1;
	for (int i = 0; i < n; i++)
	{
		pos = pos * p[i] / __gcd(pos, p[i]);
	}
	return pos;
}

void run()
{
	int pos = get();

	ans = 0;
	for (int i = 1; i < MAXN; i++)
	{
		pref[i] = pref[i - 1];
		for (int j = 0; j < n; j++)
		{
			if (s[j] <= i)
			{
				if ((i - s[j]) % p[j] == 0)
				{
					pref[i] += v[j];
				}
			}
		}
		ans = max(ans, pref[i] - d*i)
;	}
	/*if (pos == 0)
	{
		cout << "puhh\n";
		exit(0);
	}*/	
	//cout << pos << " " << endl;
	if (pref[pos] - pos*d > 0)
		ans = -1;

/*	for (int i = 0; i <= pos; i++)
	{
		cout << pref[i] - i*d << " ";
	}
	cout << endl;

	cout << "pos " << pos << endl;*/
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