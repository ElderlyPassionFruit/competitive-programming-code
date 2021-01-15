#include <cstdio>
#include <cassert>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#define all(a) a.begin(), a.end()
#define set Set
using namespace std;
const int MAXN = 500005;

inline long long ask(int a, int b) {
    printf("swap %d %d\n", a, b);
    fflush(stdout);
    long long ret;
    scanf("%lld", &ret);
    return ret;
}

long long table[MAXN];
int tree[4 * MAXN];

void build(int v, int l, int r) {
    if (r - l == 1) {
        tree[v] = 1;
        return;
    }
    build(2 * v + 1, l, (l + r) / 2);
    build(2 * v + 2, (l + r) / 2, r);
    tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
}

int get(int v, int l, int r, int k) {
    assert(k < tree[v]);
    if (r - l == 1) {
        return l;
    }
    if (k < tree[2 * v + 1]) {
        return get(2 * v + 1, l, (l + r) / 2, k);
    } else {
        return get(2 * v + 2, (l + r) / 2, r, k - tree[2 * v + 1]);
    }
}

void set(int v, int l, int r, int x) {
    assert(l <= x && x < r);
    if (r - l == 1) {
        tree[v] = 0;
        return;
    }
    if (x < (l + r) / 2) {
        set(2 * v + 1, l, (l + r) / 2, x);
    } else {
        set(2 * v + 2, (l + r) / 2, r, x);
    }
    tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
}

int p[MAXN];
int answer[MAXN];

int main() {
    int n;
    long long inv;
    scanf("%d%lld", &n, &inv);

    int mx = 0;
    long long have = inv;
    
    vector<pair<int, int>> op;

    for (int i = 1; i < n; i++) {
        op.push_back({mx, i});
        long long tmp1 = ask(mx + 1, i + 1);
        long long tmp2 = have;
        if (tmp1 < tmp2) {
            mx = i;
        }
        have = tmp1;
    }

    inv = have;
    
    if (mx != 0) {
        op.push_back({0, mx});
        inv = ask(1, mx + 1);
    }

    for (int i = 1; i < n; i++) {
        long long cur = ask(1, i + 1);
        table[i] = (inv - cur + 1) / 2;
        ask(1, i + 1); 
    }
    
    build(0, 0, n);
    for (int i = n - 1; i >= 0; i--) {
        p[i] = get(0, 0, n, i - table[i]);
        assert(0 <= p[i] && p[i] < n);
        set(0, 0, n, p[i]);
    }
    for (int i = 0; i < n; i++) {
        answer[i] = p[i] + 1;
    }
    
    reverse(all(op));
    for (auto i : op) {
        swap(answer[i.first], answer[i.second]);
    }

    printf("answer");
    for (int i = 0; i < n; i++) {
        printf(" %d", answer[i]);
    }
    printf("\n");
    fflush(stdout);
    return 0;
}
