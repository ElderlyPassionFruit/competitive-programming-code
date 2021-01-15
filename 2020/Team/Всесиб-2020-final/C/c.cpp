#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct Pt{
    int x, y;
    Pt() {}
    Pt(int _x, int _y) {
        x = _x, y = _y;
    }
};

Pt operator-(const Pt& a, const Pt& b) {
    return Pt(a.x - b.x, a.y - b.y);
}

int operator^(const Pt& a, const Pt& b) {
    return a.x * b.y - a.y - b.x;
}

int operator*(const Pt& a, const Pt& b) {
    return a.x * b.x + a.y * b.y;
}

int dist(const Pt& a) {
    return a.x * a.x + a.y * a.y;
}

ld get(Pt p, Pt cur) {
    Pt v1(-p.x, -p.y);
    Pt v2 = cur - p;
    //ld phi = atan2(v1 ^ v2, v1 * v2);
    //return cos(phi) / dist(v2);
    int num = dist(cur) - dist(v1) - dist(v2);
    ld denum = 2 * sqrt((ll)dist(v1) * dist(v2));
    return (ld)num / (denum * dist(v2));
}

ld P = 100;
Pt X = {1, 0};
bool LOCAL = false;

ld query(Pt a) {
    cout << "? " << a.x << " " << a.y << " " << -a.x << " " << -a.y << endl;
    ld ans;
    if (LOCAL) {
        ans = get(a, X) * P;
    } else {
        cin >> ans;
    }
    return ans;
}

void outAns(Pt a) {
    cout << "? " << a.x << " " << a.y << " " << -a.x << " " << -a.y << endl;
    if (LOCAL) {
        assert(a.x == X.x && a.y == X.y);
    } else {
        int ans;
        cin >> ans;
        //assert(ans == -1);
    }
    exit(0);
}

vector<Pt> p;
vector<ld> myFans;
    
ld relax(const Pt& x) {
    ld minVal = 1e30;
    ld maxVal = -1e30;
    int it = 0;
    for (auto myP : p) {
        ld val = get(myP, x) / myFans[it++];
        if (minVal > val) {
            minVal = val;
        }
        if (maxVal < val) {
            maxVal = val;
        }
    }
    //cout << minVal << " " << maxVal << endl;
    /*if (fabs(maxVal - minVal) < 1e-6) {
        outAns(x);
    }*/
    return fabs(minVal - maxVal);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    vector<int> d = {1001, -1001};
    for (auto x : d) {
        for (auto y : d) {
            if (x == 0 && y == 0) {
                continue;
            }
            p.push_back({x, y});
            myFans.push_back(query({x, y}));
        }
    }

    //relax(X);
    //exit(0);

    ld myAns = 1e30;
    Pt ans(0, 0);

    for (int x = -1000; x <= 1000; ++x) {
        for (int y = -1000; y <= 1000; ++y) {
            ld have = relax({x, y});
            if (have < myAns) {
                myAns = have;
                ans = {x, y};
            }
        }
    }
    outAns(ans);
    //assert(false);
	return 0;
}