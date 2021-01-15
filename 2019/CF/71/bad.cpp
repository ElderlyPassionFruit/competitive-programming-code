#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<queue>
#include<vector>
#include<ctime>
#include<map>
#include<bitset>
#include<set>
#define LL long long
#define mp(x,y) make_pair(x,y)
#define pll pair<long long,long long>
#define pii pair<int,int>
using namespace std;
inline LL read()
{
  LL f=1,x=0;char ch=getchar();
  while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
  while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
  return x*f;
}
int stack[20];
template<typename T>inline void write(T x)
{
  if(x<0){putchar('-');x=-x;}
    if(!x){putchar('0');return;}
    int top=0;
    while(x)stack[++top]=x%10,x/=10;
    while(top)putchar(stack[top--]+'0');
}
template<typename T>inline void pr1(T x){write(x);putchar(' ');}
template<typename T>inline void pr2(T x){write(x);putchar('\n');}
const int MAXN=55;
int a[MAXN][MAXN],b[MAXN][MAXN],n,m;
bool no[MAXN][MAXN];
bool in(int x,int y){return x>=1&&x<=n&&y>=1&&y<=m;}
int main()
{
  n=read();m=read();
  for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)a[i][j]=read();
  for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(!a[i][j])
  {
    if(in(i-1,j-1))no[i-1][j-1]=1;
    if(in(i-1,j))no[i-1][j]=1;
    if(in(i,j-1))no[i][j-1]=1;
    if(in(i,j))no[i][j]=1;
  }
  int cnt=0;
  for(int i=1;i<=n-1;i++)for(int j=1;j<=m-1;j++)if(!no[i][j])b[i][j]=b[i+1][j]=b[i+1][j+1]=b[i][j+1]=1,++cnt;
  for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(a[i][j]!=b[i][j])return puts("-1"),0;
  pr2(cnt);
  for(int i=1;i<=n-1;i++)for(int j=1;j<=m-1;j++)if(!no[i][j])pr1(i),pr2(j);
  return 0;
}

//xgcxgc666