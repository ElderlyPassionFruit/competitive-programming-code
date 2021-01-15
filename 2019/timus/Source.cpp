#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define MAXN 200000
#define MAXQ 200000
#define MOD 1000000007
 
int msum(int a)
{
	if(a >= MOD) return a-MOD;
	return a;
}
 
 
int N,K,Q;
int A[MAXN];
int l[MAXQ], r[MAXQ];
int qid[MAXQ];
int qans[MAXQ];
 
int lans[MAXN][21];
int rans[MAXN][21];
int cnt[21];
 
void countLeft(int a,int b)
{
	for(int i=a;i<=b;i++)
		for(int k=1;k<=K;k++)
			lans[i][k] = 0;
	for(int k=K;k>=1;k--)
	{
		for(int j=k;j<=K;j++)
			cnt[j] = 0;
		for(int i=b;i>=a;i--)
		{
			if(A[i] == k)
			{
				cnt[k] = msum(2*cnt[k] + 1);
				for(int j=k+1;j<=K;j++)
					cnt[j] = msum(msum(2*cnt[j]) + lans[i][j]);
			}
			for(int j=k;j<=K;j++)
				lans[i][j] = msum(lans[i][j] + cnt[j]);
		}
	}
}
 
void countRight(int a,int b)
{
	for(int i=a;i<=b;i++)
		for(int k=1;k<=K;k++)
			rans[i][k] = 0;
	for(int k=1;k<=K;k++)
	{
		for(int j=1;j<=k;j++)
			cnt[j] = 0;
		for(int i=a;i<=b;i++)
		{
			if(A[i] == k)
			{
				cnt[k] = msum(2*cnt[k] + 1);
				for(int j=1;j<k;j++)
					cnt[j] = msum(msum(2*cnt[j]) + rans[i][j]);
			}
			for(int j=1;j<=k;j++)
				rans[i][j] = msum(rans[i][j] + cnt[j]);
		}
	}
}
 
int split(int qa,int qb, int m)
{
	int i = qa;
	int j = qb;
	while(i<j)
	{
		if(r[qid[i]] > m && r[qid[j]] <= m)
		{
			swap(qid[i],qid[j]);
			i++, j--;
		}
		else if(r[qid[i]] > m)
			j--;
		else if(r[qid[j]] <= m)
			i++;
		else
			i++, j--;
	}
	if(i > j) return j;
	else if(r[qid[i]] <= m) return i;
	else return i-1;
}
 
void solve(int a,int b,int qa,int qb)
{
	if(a>b || qa>qb) return;
	if(a == b)
	{
		for(int i=qa;i<=qb;i++)
			qans[qid[i]] = 1;
		return;
	}
	int m = (a+b)/2;
	countLeft(a,m);
	countRight(m+1,b);
	for(int i=m+1;i<=b;i++)
		for(int k=K-1;k>=1;k--)
			rans[i][k] = msum(rans[i][k] + rans[i][k+1]);
	int qDone = 0;
	for(int i=qa;i<=qb;i++)
	{
		int q = qid[i];
		if(r[q] > m && l[q] <= m)
		{
			qans[q] = 0;
			for(int k=1;k<=K;k++)
				qans[q] = msum(qans[q] + (lans[l[q]][k]*((long long)rans[r[q]][k]))%MOD);
			for(int k=1;k<=K;k++)
				qans[q] = msum(qans[q] + lans[l[q]][k]);
			qans[q] = msum(qans[q] + rans[r[q]][1]);
			qDone++;
		}
		else if(qDone>0)
			qid[i-qDone] = qid[i];
	}
	qb -= qDone;
	int qm = split(qa,qb,m);
	solve(a,m,qa,qm);
	solve(m+1,b,qm+1,qb);
}
 
int main()
{
	freopen("nondec.in","r",stdin);
	freopen("nondec.out","w",stdout);
	cin >> N >> K;
	for(int i=0;i<N;i++)
		cin >> A[i];
	cin >> Q;
	for(int i=0;i<Q;i++)
	{
		cin >> l[i] >> r[i];
		l[i]--,r[i]--;
		qid[i] = i;
	}
	solve(0,N-1,0,Q-1);
	for(int i=0;i<Q;i++)
		cout << qans[i]+1 << '\n';
}
