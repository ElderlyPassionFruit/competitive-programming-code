#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
const int MAXN=  1e5 + 10;
const int inf = 1e9;
vector<vector<pair<int,int>>> g(MAXN);

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n,m;
	cin>>n>>m;
	for(int  i =0 ; i< m;++i)
	{
		int a,b,c;
		cin>>a>>b>>c;
		g[a].pb({b,c});
		//g[b].pb({a,c});
	}
	deque<int> q;
	vector<int> d(MAXN,inf);
	d[1] = 0;
	q.pb(1);
	vector<int> p(MAXN, - 1);
	while(q.size())
	{
		int v = q.front();
		q.pop_front();
		for(auto i : g[v])
		{
			if(d[i.first] > d[v]  + i.second)
			{
				p[i.first] = v;
				d[i.first] = d[v] + i.second;
				if(i.second == 0) q.push_front(i.first);
				else q.push_back(i.first);
			}
		}
	}
	if(d[n] == inf)
	{
		cout<<"IMPOSSIBLE";
		return 0;
	}
	vector<int> ans;
	for(int v = n; v!=1; v= p[v])
	{
		ans.pb(v);
	}
	ans.pb(1);
	reverse(all(ans));
	cout<<d[n]<<' '<< ans.size()<<endl;
	for(int i : ans) cout<<i<<' ';
	return 0;
}