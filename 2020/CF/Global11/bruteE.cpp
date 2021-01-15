#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

int n;

void read() {
    cin >> n;
}



mt19937 rnd(228);


vector<int> have;
set<int> now;

int last;

bool check() {
    int x = last;
    for (auto i : have) {
        if (i & 1) {
            if (i * 1.2 <= x) {
                return true;
            }
        }
    }
    return false;
}

int get() {
    int x = 1e9;
    for (auto i : have) {
        if (i & 1) {
            chkmin(x, i);
        }
    }
    return x;
}

vector<string> ans;

void Add(int a, int b) {
    ans.push_back(to_string(a) + " + " + to_string(b));
}

void Xor(int a, int b) {
    ans.push_back(to_string(a) + " ^ " + to_string(b));
}

int mx;

bool tryAdd(int a, int b) {
    int x = a + b;
    //cout << "add = " << a << " " << b << endl;

    if (x == 0 || x > mx) return false;
    /*cout << "add = " << a << " " << b << endl;
    for (auto i : now) {
        cout << i << " ";
    }
    cout << endl;*/
    if (now.count(x)) return false;
    have.push_back(x);
    now.insert(x);
    Add(a, b);
    //cout << "add = " << a << " " << b << endl;
    return true;
}

bool tryXor(int a, int b) {
    int x = a ^ b;
    if (x == 0 || x > mx) return false;
    if (now.count(x)) return false;
    have.push_back(x);
    now.insert(x);
    Xor(a, b);
    //cout << "Xor = " << a << " " << b << endl;
    return true;    
}

vector<int> pows1 = {3, 5, 9};
vector<int> pows2 = {15, 20, 100, 200, 300, 400, 500};
vector<int> pows3 = {1000};
bool solve(int it) {
    //cout << "it = " << it << endl;
    int myP;
    if (it <= 5) { 
        shuffle(all(pows1), rnd);
        myP = pows1[0];
    } else if (it <= 8) {
        shuffle(all(pows2), rnd);
        myP = pows2[0];
    } else {
        myP = 1000;
    }
    ans.clear();
    have.clear();
    last = n;
    mx = n * myP;
    have.assign(1, n);
    now.clear();
    now.insert(n);
    while (true) {
        if (now.count(1)) return true;
        if (check()) { 
            //cout << "puhh" << endl;       
            last = get();
            have = {last};
            now.clear();
            now.insert(last);
            mx = last * myP;
        }
        /*cout << "have = " << endl;
        for (auto i : have) {
            cout << i << " ";
        }
        cout << endl;*/
        
        bool ok = false;
        shuffle(all(have), rnd);
        for (int i = 0; i < have.size(); ++i) {
            for (int j = 0; j < have.size(); ++j) {
                if (rnd() % 2 == 0) {
                    ok |= tryAdd(have[i], have[j]);
                    if (ok) break;
                    ok |= tryXor(have[i], have[j]);
                } else {    
                    ok |= tryXor(have[i], have[j]);
                    if (ok) break;
                    ok |= tryAdd(have[i], have[j]);
                }
                if (ok) break;
                
            }
            if (ok) break;
        }
        if (!ok) break;
    }
    return now.count(1);
}

void run() {
    //int it = 0;
    int mx = 0;
    for (int it = 0; ; ++it) {
        if (solve(it)) break;
        chkmax(mx, it);
        cerr << mx << endl;
    }
}

void write() {
    //assert();
    //cout << (find(all(have), 1) != have.end()) << endl;
    /*sort(all(have));
    for (auto i : have) {
        cout << i << " ";
    }
    cout << endl;*/
    assert(ans.size() <= 100000);
    cout << ans.size() << "\n";
    for (auto i : ans) {
        cout << i << "\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}