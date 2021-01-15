#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
mt19937 rnd(time(0));
 
const int MOD1 = 1148822869;
const int MOD2 = 1e9 + 9;
int base1 = 228 + rnd() % 10000;
int base2 = 1337 + rnd() % 10000;
 
int mul(int a, int b, int mod) {
    return (ll) a * b % mod;
}
 
int add(int a, int b, int mod) {
    a += b;
    if (a >= mod)
        a -= mod;
    return a;
}
 
int sub(int a, int b, int mod) {
    a -= b;
    if (a < 0)
        a += mod;
    return a;
}
 
struct fhash{
    int hash1, hash2;
    fhash() {
        hash1 = 0, hash2 = 0;
    }
    fhash(int a, int b) {
        hash1 = a, hash2 = b;
    }
};
 
bool operator<(const fhash & a, const fhash & b) {
    return tie(a.hash1, a.hash2) < tie(b.hash1, b.hash2);
}
 
struct segment{
    int l, r;
    segment() {}
    segment(int a, int b) {
        l = a, r = b;
    }
};
 
const int MAXN = 2e5 + 10;
int n;
segment a[MAXN];
 
fhash pref[MAXN * 2];
 
fhash Get(int l, int r) {
    fhash ans;
    ans.hash1 = sub(pref[r].hash1, (l > 0 ? pref[l - 1].hash1 : 0), MOD1);
    ans.hash2 = sub(pref[r].hash2, (l > 0 ? pref[l - 1].hash2 : 0), MOD2);
    return ans;
}
 
fhash add(const fhash & a, const fhash & b) {
    fhash ans;
    ans.hash1 = add(a.hash1, b.hash1, MOD1);
    ans.hash2 = add(a.hash2, b.hash2, MOD2);
    return ans;
}
 
fhash sub(const fhash & a, const fhash & b) {
    fhash ans;
    ans.hash1 = sub(a.hash1, b.hash1, MOD1);
    ans.hash2 = sub(a.hash2, b.hash2, MOD2);
    return ans;
}
 
struct segment_tree{
    int n;
    vector<fhash> tree;
    vector<int> mod;
 
    segment_tree() {}
 
    segment_tree(int sz) {
        n = sz;
        tree.resize(4 * n, {});
        mod.resize(4 * n, 0);
    }
     
    void push(int v, int l, int r) {
        if (r < l) return;
        if (!mod[v]) return;
        tree[v] = sub(Get(l, r), tree[v]);
        mod[v * 2] ^= 1;
        mod[v * 2 + 1] ^= 1;
        mod[v] = 0;
    }
 
    fhash get_val(int v, int l, int r) {
        if (r < l) return {};
        if (mod[v]) {
            return sub(Get(l, r), tree[v]);
        }
        else {
            return tree[v];
        }
    }
 
    void upd(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            mod[v] ^= 1;
            return;
        }
        push(v, tl, tr - 1);
        int tm = (tl + tr) / 2;
        upd(v * 2, tl, tm, l, r);
        upd(v * 2 + 1, tm, tr, l, r);
        tree[v] = add(get_val(v * 2, tl, tm - 1), get_val(v * 2 + 1, tm, tr - 1));
    }
 
    void upd(int l, int r) {
        upd(1, 0, n, l, r + 1);
        //for (int i = l; i <= r; i++) {
        //  tree[i] = sub(Get(i, i), tree[i]);
        //}
    }
 
    fhash get() {
        return get_val(1, 0, n - 1);
        //fhash ans = {0, 0};
        //for (int i = 0; i < n; i++)
        //  ans = add(ans, tree[i]);
        //return ans;
    }
 
    void wr() {
        cout << "tree = " << endl;
        for (int i = 0; i < n; i++)
            cout << tree[i].hash1 << " ";
        cout << endl;
        for (int i = 0; i < n; i++)
            cout << tree[i].hash2 << " ";
        cout << endl;
    }
};
 
segment_tree tree;
 
void build() {
    vector<int> have;
    for (int i = 0; i < n; i++)
        have.push_back(a[i].l), have.push_back(a[i].r);
    sort(all(have));
    have.resize(unique(all(have)) - have.begin());
    for (int i = 0; i < n; i++) {
        a[i].l = lower_bound(all(have), a[i].l) - have.begin();
        a[i].r = lower_bound(all(have), a[i].r) - have.begin();
    }
    tree = segment_tree(have.size());
    pref[0] = {1, 1};
    for (int i = 1; i < (int)have.size(); i++) {
        pref[i].hash1 = mul(base1, pref[i - 1].hash1, MOD1);
        pref[i].hash2 = mul(base2, pref[i - 1].hash2, MOD2);
    }
    for (int i = 1; i < (int)have.size(); i++) {
        pref[i] = add(pref[i], pref[i - 1]);
    }
}
 
ll ans = 0;
 
void solve() {
    map<fhash, int> L;
    for (int i = 0; i < n; i++) {
        tree.upd(a[i].l, a[i].r);
        L[tree.get()]++;
    }
    /*cout << "L = " << endl;
    for (auto i : L) {
    	cout << i.second << " ";
    }
    cout << endl;*/
    for (auto i : L) {
    	if (i.first.hash1 == 0 && i.first.hash2 == 0)
    		ans += i.second;
    	ans += (ll) i.second * (i.second - 1) / 2;
    }
}
 
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.precision(20);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i].l >> a[i].r;
        a[i].r--;
    }
    build();
    solve();
    cout << ans << endl;
    return 0;
}