#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

typedef vector<int> vi;
typedef vector<pair<int, int > > vii;
typedef vector<ll> vll;
typedef vector<string> vs;
typedef vector<ld> vld;

typedef vector<vi> vvi;
typedef vector<vii> vvii;
typedef vector<vll> vvll;
typedef vector<vs> vvs;

typedef map<int, int> mpii;
typedef map<int, string> mpis;
typedef map<string, int> mpsi;
typedef map<string, string> mpss;

#define all(a) (a).begin(),(a).end()
#define rall(a) (a).rbegin(),(a).rend()
#define sz(a) (int)((a).size())
#define len(a) (int)((a).length())

#define forr(i,n) for (int i = 0; i < (n); ++i)
#define fori(n) forr(i,n)
#define forj(n) forr(j,n)
#define fork(n) forr(k,n)
#define forin fori(n)
#define forjn forj(n)
#define forjm forj(m)
#define forkm fork(m)
#define foria(a) fori(sz(a))
#define foriv foria(v)
#define foris fori(len(s))
#define forja(a) forj(sz(a))
#define forjv forj(v)
#define forjs forj(len(s))

#define read cin>>
#define write cout<<
#define writeln write endl

#define readt int aaa; read aaa;
#define gett (bbb+1)
#define fort forr(bbb,aaa)

#define issa(a,s) istringstream a(s);
#define iss(s) issa(ss,s);

ld dis(ld x, ld y) {return sqrt(x*x+y*y);}
const ld PI = acos(ld(0.0))*2;
const ld pi = PI;

ll gcd(ll a, ll b){return b ? gcd(b,a%b) : a;}

template<class T>
struct makev
{
    vector<T> v;
    makev& operator << (const T& x)
    {
        v.push_back(x);
        return *this;
    }
    operator vector<T>& ()
    {
        return v;
    }
};

//void assert(bool b)
//{
//    if (!b)
//        throw 0;
//}

pair<string, string> hackHashInit()
{
	return pair<string, string>("a", "b");
}

ll getHash(const string &s, ll a, ll p)
{
	ll res = 0;
	foris res = (res * a + s[i]) % p;
	return res;
}

bool hackHash(pair<string, string> v, pair<string, string> &ans, ll a, ll p)
{
	const int len = 22;
	map<ll, string> mp;

	fori((1<<len))
	{
		string s;
		s.reserve(len * v.first.length());
		forj(len) 
			if (i & (1 << j))
				s += v.first;
			else
				s += v.second;
		
		ll h = getHash(s, a, p);
		if (mp.find(h) != mp.end())
		{
			ans.first = mp[h];
			ans.second = s;
			return true;
		}

		mp.insert(make_pair(h, s));
	}
	return false;
}

const ll p1 = 127, p2 = 127, p3 = 447, p4 = 53;
const ll MOD1 = 1e9 + 7, MOD2 = 1e9 + 9, MOD3 = 1e9 + 7, MOD4 = 998244353;


int main() 
{
#ifdef _MSC_VER
    //freopen("input.txt", "rt", stdin);
    //freopen("output.txt", "wt", stdout);
	ifstream cin("input.txt");
	ofstream cout("output.txt");
#else
	//ifstream cin("input.txt");
	//ofstream cout("output.txt");
#endif

	pair<string, string> collision;
	std::cerr << "kek" << endl;
	if (!hackHash(hackHashInit(), collision, p1, MOD1))
	{
		cout << "FAIL!" << endl;
		return 0;
	}
	std::cerr << "First OK!" << endl;
	if (!hackHash(collision, collision, p2, MOD2))
	{
		cout << "FAIL!";
		return 0;
	}
	std::cerr << "Second OK!" << endl;
	/*
	if (!hackHash(collision, collision, p3, MOD3)) {
		cout << "FAIL!";
		return 0;
	}
	//std::cout << "Third OK!" << endl;
	
	if (!hackHash(collision, collision, p4, MOD4)) {
		cout << "FAIL!";
		return 0;
	}*/
	//cout << collision.first.length() + collision.second.length() << endl;
	cout << 2 << endl;
	//reverse(all(collision.first));
	//reverse(all(collision.second));
	cout << collision.first << " " << collision.second << endl;

	//cout << collision.first << endl;
	//cout << getHash(collision.first,  p1, MOD1) << endl;
	//cout << getHash(collision.first,  p2, MOD2) << endl;
	
	//cout << collision.second << endl;
	//cout << getHash(collision.second,  p1, MOD1) << endl;
	//cout << getHash(collision.second,  p2, MOD2) << endl;

    return 0;
}