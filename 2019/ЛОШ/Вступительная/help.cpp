#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <list>
#include <iostream>
using namespace std;
 
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define pb push_back
#define mp make_pair
#define TASKNAME "oaks"
 
typedef long long ll;
 
typedef vector<ll> vll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
 
const int INF = 1e9;
 
bool can(int h1, int h2, int h3) {
  if (h1 < h2 && h3 < h2) return true;
  if (h1 > h2 && h3 > h2) return true;
  return false;
}
 
vvi del;
vvi dyn, fr;
vi ans;

// a и b - границы интервала, на котором хотим срубить все деревья
void deleteAll(int a, int b) {
  assert(del[a][b] >= 0);
  if (del[a][b] == a) return;
  deleteAll(a, del[a][b]);
  deleteAll(del[a][b], b);
  ans.push_back(del[a][b]);
}

// аналогично
void restoreAns(int a, int b) {
  assert(fr[a][b] >= 0);
  if (fr[a][b] == a) {
    deleteAll(a, b);
    return;
  }
  restoreAns(a, fr[a][b]);
  restoreAns(fr[a][b], b);
}
       
int main() {
  int n;
  while (scanf("%d", &n) >= 1) {
    vi h(n);
    for (int i = 0; i < n; i++) scanf("%d", &h[i]);
 
    del = vvi(n, vi(n, -1));
    for (int a = 0; a + 1 < n; a++)
      del[a][a + 1] = a;
 
    for (int l = 2; l < n; l++)
      for (int a = 0; a + l < n; a++) {
        int b = a + l;
        for (int i = a + 1; i < b; i++)
          if (del[a][i] >= 0 && del[i][b] >= 0 && can(h[a], h[i], h[b])) {
            del[a][b] = i;
            break;
          }
      }
 
    dyn = vvi(n, vi(n, INF));
    fr = vvi(n, vi(n, -1));
    
    for (int l = 1; l < n; l++)
      for (int a = 0; a + l < n; a++) {
        int b = a + l;
        if (h[a] > h[b]) continue;
        if (del[a][b] >= 0) {
          dyn[a][b] = b - a - 1;
          fr[a][b] = a;
        }
 
        for (int i = a + 1; i < b; i++) {
          if (h[a] > h[i] || h[i] > h[b]) continue;
          int cans = dyn[a][i] + dyn[i][b];
          if (dyn[a][b] > cans) {
            dyn[a][b] = cans;
            fr[a][b] = i;
          }
        }
      }
 
      cout << "dp = " << endl;
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          cout << dyn[i][j] << " ";
        }
        cout << endl;
      }

      cout << "fans = " << endl;
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          cout << fr[i][j] << " ";
        }
        cout << endl;
      }

      cout << "del = " << endl;
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          cout << del[i][j] << " ";
        }
        cout << endl;
      }

    int a = 0, b = n - 1;
    if (fr[0][n - 1] < 0) printf("-1\n");
    else {
      ans = vi();
      restoreAns(a, b);
      printf("%d\n", (int)ans.size());
      for (int i = 0; i < ans.size(); i++)
        printf("%d\n", ans[i] + 1);
    }
  }
  return 0;
}