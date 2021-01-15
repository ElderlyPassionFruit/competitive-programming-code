#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ld=long double;
const int maxn=1e5+1;
const int MX=2e6+1;

int ans[maxn];
int sieve[MX];
int h[maxn];
vector<pair<int,int>> v;
ll dp[20];
int p[5000];
bool used[4000][4000];
int notzero[4000];
int nothund[4000];
int main(){
    int n,k;
    cin>>n>>k;
    for(int i=1; i<=n; ++i)
        cin>>p[i];
    nothund[n+1]=true;
    for(int i=n; i>=1; --i){
        if (p[i]>0)
            notzero[i]=true;
        else
            notzero[i]=notzero[i+1];
        if (p[i]!=100)
            nothund[i]=nothund[i+1];
        else
            nothund[i]=false;
    }

    queue<tuple<int,int,int>> q;
    q.push(make_tuple(k,1,2));
    int ans=0;
    while(!q.empty()){
        tuple<int,int,int> z=q.front();
        ++ans;
        int curk;
        int a,b;
        tie(curk,a,b)=z;
        q.pop();
      //  cout<<a<<" "<<b<<"\n";
        if (curk>0 && b<n+1){
            if (p[a]!=100 && notzero[b] && !used[b][b+1]){
                used[b][b+1]=true;
                q.push(make_tuple(curk-1,b,b+1));
            }
            if (p[a]>0 && nothund[b] && !used[a][b+1]){
                used[a][b+1]=true;
                q.push(make_tuple(curk-1,a,b+1));
            }
            if (p[a]>0 && notzero[b] && !used[b+1][b+2]){
                used[b+1][b+2]=true;
                q.push(make_tuple(curk-1,b+1,b+2));
            }
        }
    }
    cout << ans << endl;
}
