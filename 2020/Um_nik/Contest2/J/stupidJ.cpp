#include<stdio.h>
#include<vector>
#include<algorithm>
#include<stdlib.h>
#include<math.h>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll>pii;
typedef pair<pii,pii>pi4;
typedef pair<pi4,pii>pi6;
ll mod=1000000007;
ll gcd(ll a,ll b)
{
	for(;;)
	{
		if(a<b)
		{
			swap(a,b);
		}
		a%=b;
		if(a==0)
		{
			return b;
		}
	}
}
pii reduct(pii a)
{
	if(a.second==0)
	{
		return make_pair(1LL,0LL);
	}
	if(a.first==0)
	{
		return make_pair(0LL,1LL);
	}
	ll g=gcd(abs(a.first),abs(a.second));
	if(a.second<0)
	{
		a.first=-a.first;
		a.second=-a.second;
	}
	return make_pair(a.first/g,a.second/g);
}
pii pls(pii a,pii b)
{
	return reduct(make_pair(a.first*b.second+a.second*b.first,a.second*b.second));
}
pii mins(pii a,pii b)
{
	return reduct(make_pair(a.first*b.second-a.second*b.first,a.second*b.second));
}
pii tim(pii a,pii b)
{
	return reduct(make_pair(a.first*b.first,a.second*b.second));
}
pii div(pii a,pii b)
{
	return reduct(make_pair(a.first*b.second,a.second*b.first));
}
pi4 getsum(pi4 a,pi4 b)
{
	return make_pair(pls(a.first,b.first),pls(a.second,b.second));
}
pii getinc(pi4 a,pi4 b)
{
	pii dx=mins(b.first,a.first);
	pii dy=mins(b.second,a.second);
	return div(dy,dx);
}
pi4 inv(ll za,ll zb,ll zc,ll zd)
{
	pii dist=pls(tim(make_pair(za,zb),make_pair(za,zb)),tim(make_pair(zc,zd),make_pair(zc,zd)));
	return (make_pair(div(make_pair(za,zb),dist),div(make_pair(zc,zd),dist)));
}
vector<int>tov(vector<pii>vec)
{
	pii now=make_pair(2000000000000000000LL,2000000000000000000LL);
	vector<int>ret;
	for(int i=0;i<vec.size();i++)
	{
		if(now!=vec[i])
		{
			ret.push_back(1);
			now=vec[i];
		}
		else
		{
			ret[ret.size()-1]++;
		}
	}
	return ret;
}
ll calc(vector<pii>v)
{
	vector<int>vec=tov(v);
	ll ret=1;
	for(int i=0;i<vec.size();i++)
	{
		ret*=vec[i]+1;
		ret%=mod;
	}
	ret=(ret+mod-1-int(v.size()))%mod;
	return ret;
}

#define point pair<pair<int, int>,pair<int, int>>
#define x first
#define y second
#define ld long double

void wrPoint(point a) {
	cout.precision(20);
	cerr << "(" << (ld)a.x.x / a.x.y << "," << (ld)a.y.x / a.y.y << ")" << endl;
	//cerr << a.x.x << " " << a.x.y << " " << a.y.x << " " << a.y.y << endl;
}

int main()
{
	int num;
	scanf("%d",&num);
	vector<pi4>dat;
	//cerr << "points = " << endl;
	for(int i=0;i<num;i++)
	{
		ll za,zb,zc,zd;
		//scanf("%I64d%I64d%I64d%I64d",&za,&zb,&zc,&zd);
		cin >> za >> zb >> zc >> zd;
		dat.push_back(inv(za,zb,zc,zd));
	//	wrPoint(dat.back());
	}
	vector<pi6>vec;
	for(int i=0;i<num;i++)
	{
		for(int j=i+1;j<num;j++)
		{
			vec.push_back(make_pair(getsum(dat[i],dat[j]),getinc(dat[i],dat[j])));
		}
	}
	sort(vec.begin(),vec.end());
	pi4 nowsum=make_pair(make_pair(2000000000000000000LL,2000000000000000000LL),make_pair(2000000000000000000LL,2000000000000000000LL));
	vector<pii>now;
	ll ret=0;
	for(int i=0;i<vec.size();i++)
	{
		if(nowsum!=vec[i].first)
		{
			if(!now.empty())
			{
				ret+=calc(now);
				ret%=mod;
			}
			now.clear();
			now.push_back(vec[i].second);
			nowsum=vec[i].first;
		}
		else
		{
			now.push_back(vec[i].second);
		}
	}
	ret+=calc(now);
	ret%=mod;
	//printf("%I64d\n",ret);
	cout << ret << endl;
}