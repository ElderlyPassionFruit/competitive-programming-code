#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <utility>
#include <fstream>
#define ll long long

using namespace std;

struct obj {
    ll p;
    int ind;
    ll last = 0;
    obj(ll _p, int _ind): p(_p), ind(_ind), last(0) {}
};

bool operator<(const obj& A, const obj& B) {
    if (A.p != B.p) {
        return B.p < A.p;
    }
    return A.ind < B.ind;
}

int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, t;
    cin >> n >> t;
    vector<ll> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }
    set<obj> s;
    for (int i = 0; i < n; ++i) {
        obj A(p[i], i);
        s.insert(A);
    }
    ll now = 0;
    vector<ll> cnt(n);
    while (now != t) {
        auto u = *s.begin();
        //for (auto elem : s) {
        //    cerr << elem.p << "/" << elem.ind << "/" << elem.last << " ";
        //}
        //cerr << "\n";
        s.erase(u);
        cnt[u.ind]++;
        //cerr << u.ind << " " << u.p << "!\n";
        u.p -= (now - u.last + 1);
        u.last = now + 1;
        s.insert(u);
        now++;
    }
    for (auto elem : cnt) {
        cout << elem << " ";
    }
    cout << "\n";
}