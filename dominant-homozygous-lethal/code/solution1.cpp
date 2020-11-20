#include <bits/stdc++.h>
#define MAXN (1<<17)+5
#define U 18
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int cnt[MAXN];
int n,m;
int a[MAXN],b[MAXN],c[MAXN];
int F[U][MAXN],G[U][MAXN],H[U][MAXN];
void FMT(int *f,int op){
	/*
	op=1：快速莫比乌斯变换
	op=-1：快速莫比乌斯反演
	*/
	for (int i=0;i<n;++i){
		for (int j=0;j<m;++j){
			if ((j&(1<<i))==0){
				f[j|(1<<i)]=f[j|(1<<i)]+op*f[j];
			}
		}
	}
}
#define lowbit(x) (x&(-x))
void Init(){
	cnt[0]=0;
	for (int i=1;i<MAXN;++i){
		cnt[i]=cnt[i-lowbit(i)]+1;
	}
}
void SubsetMul(int *f,int *g,int *h){
	for (int S=0;S<m;++S) F[cnt[S]][S]=f[S],G[cnt[S]][S]=g[S];
	for (int i=0;i<=n;++i){
		FMT(F[i],1),FMT(G[i],1);
		for (int S=0;S<m;++S){
			for (int j=0;j<=i;++j){
				H[i][S]+=F[j][S]*G[i-j][S];
			}
		}
		FMT(H[i],-1);
	}
	for (int S=0;S<m;++S) h[S]=H[cnt[S]][S];
}
#undef int
int main(){
#define int long long
	Init();
	n=read(),m=(1<<n);
	for (int i=0;i<m;++i) a[i]=read();
	for (int i=0;i<m;++i) b[i]=read();
	SubsetMul(a,b,c);
	for (int i=0;i<m;++i) printf("%lld ",c[i]);
	return 0;
}
