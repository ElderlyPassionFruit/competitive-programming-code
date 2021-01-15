#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ld
const ld EPS = 1e-9;
struct point
{
	int x,y;
};
struct line
{
	int a,b,c;
};
ld det(ld a, ld b, ld c, ld d)
{
	return a * d - b * c;
}//call
line getln(point a, point b)
{
	line ans;
	ans.a = b.y-a.y;
	ans.b = a.x-b.x;
	ans.c = - (a.x * ans. a + a.y * ans.b);
	return ans;
}
point intersect(line a, line b)
{
	ld zn = det(a.a,a.b,b.a,b.b);
	if(abs(zn)<EPS)
	{
		return {1e17, 1e17};
	}
	point res;
	res.x = - det(a.c,a.b,b.c,b.b) / zn;
	res.y = -det(a.a,a.c,b.a,b.c) / zn;
	return res;
}
ld hyp(point a, point b)
{
	return sqrt((a.x - b.x) * (a.x-b.x)  + (a.y- b.y) * (a.y-b.y));
}
ld calc(point a, point b, point v1, point v2, ld m )
{
		point ta = {a.x + v1.x * m, a.y + v1.y *m};
		point tb = {b.x + v2.x *m , b.y + v2.y * m};
		return hyp(ta,tb);
}
signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	point a,b;
	point v1,v2;
	cin>>a.x>>a.y>>b.x>>b.y;
	cin>>v1.x>>v1.y>>v2.x>>v2.y;
	ld l = 0,r = 1e9;
	for(int cnt= 0 ;cnt <150;++cnt)
	{
		ld  m1 = (l*2 +r)/3;
		ld m2 = (l + 2*r)/3;
		if(calc(a,b,v1,v2,m1) <calc(a,b,v1,v2,m2))
		{
			r = m2;
		}
		else
		{
			l = m1;
		}
	}
	cout<< calc(a,b,v1,v2,r);
	return 0;
}