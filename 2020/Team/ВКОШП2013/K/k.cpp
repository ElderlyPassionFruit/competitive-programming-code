#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,abm,mmx,avx,avx2,popcnt,tune=native")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()
int n,m;

bool a[100][100];
bool used[100][100];
int k;
int ans =0 ;
vector<int> dx{1,0,-1,0};
vector<int> dy{0,-1,0,1};
vector<pair<int,int>> jopa;
void dfs(int x228)
{
	if(x228 == k)
	{
		ans++;/*
		for(int i =0 ; i< n;++i)
		{
			for(int j = 0 ; j< m;++j)
			{
				cout<<a[i][j]<<' ' ;
			}
			cout<<endl;
		}
		cout<<endl;*/
		return;
	}
	vector<pair<int,int>> ololo;
	for(auto kekos : jopa)
	{
	//	if(!a[kekos.first][kekos.second]) continue;
		int i = kekos.first;
		int j = kekos.second;
		for(int x=  0; x< 4;++x)
		{
			int nx = i + dx[x];
			int ny = j + dy[x];
			if(nx >=0 && ny>=0 && nx <n && ny < m && ! used[nx][ny] && ! a[nx][ny])
			{
				ololo.push_back({nx, ny});
			}
		}
	}
	sort(all(ololo));
	ololo.resize(unique(all(ololo)) - ololo.begin());	
	for(auto i : ololo)
	{
	//	if(used[i.first][i.second]) continue;
		a[i.first][i.second] = 1;
		jopa.push_back(i);
		used[i.first][i.second] = 1;
		dfs(x228 + 1);
		jopa.pop_back();
		a[i.first][i.second] = 0;
//		dfs(x228+1);
	}
	for(auto i : ololo)
	{
		used[i.first][i.second] = 0;
	}
}
signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	freopen("virus.in","r",stdin);
	freopen("virus.out","w",stdout);
	cin>>n>>m >> k;
	for(int i = 0;i < n;++i)
	{
		for(int j =0 ; j< m;++j)
		{
			char x;
			cin>>x;
			if(x=='*')
			{
				a[i][j] = 1;
				jopa.push_back({i,j});
			}
		}
	}
	dfs(0);
	cout<<ans;
	return 0;
}