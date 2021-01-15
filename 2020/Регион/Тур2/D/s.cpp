Alexander Nekrasov, [10.01.20 00:00]
#ifndef LOCAL
//#pragma GCC optimize("Ofast,inline,fast-math,unroll-loops,no-stack-protector")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,avx,avx2,abm,mmx,popcnt")
#endif
#include <bits/stdc++.h>
using namespace std;

typedef long double ldb;

#define max(a, b) (a < b) ? b : a

template<typename T>
istream &operator>>(istream &in, vector<T> &arr) {
  for (auto &el : arr) {
    in >> el;
  }
  return in;
}

template<typename T1, typename T2> 
istream &operator>>(istream &in, pair<T1, T2> &p) {
  in >> p.first >> p.second;
  return in;
}

template<typename T>
ostream &operator<<(ostream &out, vector<T> &arr) {
  for (auto &el : arr) {
    out << el;
  }
  return out;
}

template<typename T1, typename T2> 
ostream &operator>>(ostream &out, pair<T1, T2> &p) {
  out << p.first << " " << p.second;
  return out;
}

pair<ldb, ldb> project(pair<int, int> p1, pair<int, int> p2, int C) {
  ldb a1 = ldb(p1.second) * C / p1.first;
  ldb a2 = ldb(p2.second) * C / p2.first;
  return {min(a1, a2), max(a1, a2)};
}

int P;
int n;
vector<pair<int, int>> p1;
vector<pair<int, int>> p2;
vector<int> ans;

void swap() {
  for (int i = 0; i < n; i++) {
    swap(p1[i].first, p1[i].second);
    swap(p2[i].first, p2[i].second);
    swap(p1[i], p2[i]);
  }
}


bool check(int i) {
  int C = p1[i].first;
  vector<pair<ldb, ldb>> segs;
  for (int j = 0; j < n; j++) {
    if (i == j)
      continue;
    if (p1[j].first >= C)
      continue;
    pair<int, int> a1 = p1[j];
    pair<int, int> a3 = {min(C, p2[j].first), p2[j].second};
    auto pp = project(a1, a3, C);
    if (pp.second <= p2[i].second || pp.first >= p1[i].second)
      continue;
    if (P == 1) {
      return false;
    }
    pp.first = max(pp.first, p2[i].second);
    pp.second = min(pp.second, (ldb) p1[i].second);
    segs.push_back(pp);
  }
  if (P == 1) {
    return true;
  }
  int len = p1[i].second - p2[i].second;
  ldb len2 = 0;
  vector<pair<ldb, int>> evs;
  for (int i = 0; i < (int) segs.size(); i++) {
    evs.push_back({segs[i].first, 1});
    evs.push_back({segs[i].second, -1});
  }
  sort(evs.begin(), evs.end());
  if (evs.empty()) {
    return true;
  }
  ldb last = evs[0].first;
  int bal = 0;
  for (int i = 0; i < (int) evs.size(); i++) {
    if (bal) {
      len2 += evs[i].first - last;
    }
    last = evs[i].first;
    bal += evs[i].second;
  }
  return len2 < len;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> P;
  cin >> n;
  p1.resize(n);
  p2.resize(n);
  ans.resize(n);
  for (int i = 0; i < n; i++) {
    cin >> p1[i] >> p2[i];
    swap(p1[i].second, p2[i].second);
  }
  for (int i = 0; i < n; i++) {
    if (check(i)) {
      ans[i] = 1;
    }
  }
  swap();
  for (int i = 0; i < n; i++) {
    if (check(i)) {
      ans[i] = 1;
    }
  }
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    cnt += ans[i];
  }
  cout << cnt << endl;
}