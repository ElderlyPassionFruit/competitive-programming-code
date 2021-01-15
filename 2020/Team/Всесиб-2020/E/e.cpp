#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

bool LOCAL = false;

map<ll, ll> mem;
vector<int> myArray = {1, 0, 1, 0, 3};

int Q = 0;

ll ask(const ll& x) {
    if (LOCAL) {
        //cerr << "read " << x << endl;
        return myArray[x];
    } else {
        if (mem.count(x)) return mem[x];
        ++Q;
        assert(Q < 120000);
        cout << "read " << x << endl;
        ll res;
        cin >> res;
        return mem[x] = res;
    }
}

const int BUBEN = 50229;

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    ll n;
    if (LOCAL) {
        //n = myArray.size();
        cin >> n;
        myArray.resize(n);
        for (auto& i : myArray) {
            cin >> i;
        }
    } else {
        cin >> n;
    }
    vector<pair<ll, ll>> L;
    ll posNow = 0;
    while (posNow < n && L.size() < BUBEN) {
        L.push_back({posNow, ask(posNow)});
        posNow += L.back().second + 1;
        if (posNow < n && ask(posNow) == L.back().second) {
            L.push_back({posNow, ask(posNow)});
            ++posNow;
        } else {
            break;
        }
    }
    
    if (L.size() % 2 == 0 && !L.empty() && L.back().first == n - 1) {
        cout << "fix 0" << endl;
        exit(0);
    }

    vector<pair<ll, ll>> R;
    posNow = n - 1;
    
    while (posNow >= 0 && R.size() < BUBEN) {
        R.push_back({posNow, ask(posNow)});
        posNow -= R.back().second + 1;
        if (posNow >= 0 && ask(posNow) == R.back().second) {
            R.push_back({posNow, ask(posNow)});
            --posNow;
        } else {
            break;
        }
    }

    if (L.size() % 2 == 1) {
        // проверяем прыжок слева
        reverse(all(R));
        ll myJump = L.back().first + L.back().second + 1;
        if (myJump == n - 1) {
            cout << "fix 1\n";
            cout << myJump << " " << L.back().second << "\n";
            cout.flush();
            exit(0);
        }
        auto it = lower_bound(all(R), make_pair(myJump + 1, -1LL));
        if (it != R.end() && it->first == myJump + 1 && (R.end() - it) % 2 == 0) {
            cout << "fix 1" << "\n";
            cout << myJump << " " << L.back().second << "\n";
            cout.flush();
            exit(0);
        }
        reverse(all(R));
    }

    if (R.size() % 2 == 1) {
        // проверяем прыжок справа
        ll myJump = R.back().first - R.back().second - 1;
        if (myJump == 0) {
            cout << "fix 1\n";
            cout << myJump << " " << R.back().second << "\n";
            cout.flush();
            exit(0);
        }
        auto it = lower_bound(all(L), make_pair(myJump - 1, -1LL));
        if (it != L.end() && it->first == myJump - 1 && (it - L.begin()) % 2 == 1) {
            cout << "fix 1" << "\n";
            cout << myJump << " " << R.back().second << "\n";
            cout.flush();
            exit(0);
        }
    }

    cout << "fix 2\n";
    cout << "0 " << n - 2 << "\n";
    cout << n - 1 << " " << n - 2 << "\n";
    cout.flush();
	return 0;
}