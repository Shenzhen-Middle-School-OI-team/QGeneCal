#include <bits/stdc++.h>
#define MAXN 25
#define MAXM 5000005
#define MOD 998244353
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
char ch[MAXN*2];
bool isUpper(char ch){
    return 'A'<=ch&&ch<='Z';
}
int n,k;
inline int ksm(int b,int k){
    int ans=1;
    while (k){
        if (k&1) ans=1ll*ans*b%MOD;
        b=1ll*b*b%MOD;
        k>>=1;
    }
    return ans;
}
namespace Trie{
	struct node{
		int ch[3];
		int end;
	}tree[MAXN*MAXM];
	#define ch(x,i) tree[x].ch[i]
	int tot=1;
	void Insert(int frequency){
		int now=1;
		for (int i=k;i>=1;--i){
			char First=ch[i*2-1],Second=ch[i*2];
			int c;
			if (!isUpper(First)&&!isUpper(Second)) c=0;
			if (isUpper(First)&&!isUpper(Second)) c=1;
			if (isUpper(First)&&isUpper(Second)) c=2;
			if (!ch(now,c)) ch(now,c)=++tot;
			now=ch(now,c);
		}
		tree[now].end+=frequency;
	}
	vector<int>dfs(int node,int depth){
		vector<int>v;
		v.resize(ksm(2,(k-depth)));
		if (depth==k){
			v[0]=tree[node].end;
			return v;
		}
		for (int i=0;i<=2;++i){
			if (!ch(node,i)) continue;
			vector<int>child=dfs(ch(node,i),depth+1);
			if (i==0){
				for (int j=0;j<(int)child.size();++j) v[j]=(v[j]+2*child[j])%MOD;
			}
			else if (i==1){
				for (int j=0;j<(int)child.size();++j) v[j]=(v[j]+child[j])%MOD,v[j+child.size()]=(v[j+child.size()]+child[j])%MOD;
			}
			else if (i==2){
				for (int j=0;j<(int)child.size();++j) v[j+child.size()]=(v[j+child.size()]+2*child[j])%MOD;
			}
		}
		return v;
	}
}
using namespace Trie;
int add(int x,int y){
	return (x+y)%MOD;
}
int mul(int x,int y){
	return 1ll*x*y%MOD;
}
struct Poly{
	int a0,a1,a2;
};
Poly operator + (const Poly &A,const Poly &B){
	return Poly{add(A.a0,B.a0),add(A.a1,B.a1),add(A.a2,B.a2)};
}
Poly operator * (const Poly &A,const Poly &B){
	return Poly{
		add(add(mul(A.a0,B.a0),mul(A.a1,B.a2)),mul(A.a2,B.a1)),
		add(add(mul(A.a0,B.a1),mul(A.a1,B.a0)),mul(A.a2,B.a2)),
		add(add(mul(A.a0,B.a2),mul(A.a1,B.a1)),mul(A.a2,B.a0)),
	};
}
Poly operator * (const Poly &A,int d){
	return Poly{mul(A.a0,d),mul(A.a1,d),mul(A.a2,d)};
}
Poly f[MAXM];
int N,M,D;
void FWT(Poly *f,int opr){
	for (int len=1;len<M;len*=3){
		for (int i=0;i<M;i+=len*3){
			for (int j=0;j<len;++j){
				Poly x=f[i+j],y=f[i+j+len],z=f[i+j+len*2];
				if (opr==1){
                    f[i+j]=x+y+z;
                    f[i+j+len]=x+Poly{y.a2,y.a0,y.a1}+Poly{z.a1,z.a2,z.a0};
                    f[i+j+len*2]=x+Poly{y.a1,y.a2,y.a0}+Poly{z.a2,z.a0,z.a1};
				}
				else{
                    f[i+j]=x+y+z;
                    f[i+j+len]=x+Poly{y.a1,y.a2,y.a0}+Poly{z.a2,z.a0,z.a1};
                    f[i+j+len*2]=x+Poly{y.a2,y.a0,y.a1}+Poly{z.a1,z.a2,z.a0};
					f[i+j]=f[i+j]*D;
					f[i+j+len]=f[i+j+len]*D;
					f[i+j+len*2]=f[i+j+len*2]*D;
				}
			}
		}
	}
}
int val[MAXM];
int b[MAXM];
void Split(int x,int base,int len){
	for (int i=1;i<=len;++i){
		b[i]=x%base;
		x/=base;
	}
}
int main(){
    k=read(),n=read();
    N=k,M=1;
    for (int i=1;i<=k;++i) M*=3;
    D=ksm(3,MOD-2);
    int inv=ksm((1<<N),MOD-2);
    while (n--){
        scanf("%s",ch+1);
        int frequency=read();
        Insert(frequency);
    }
    vector<int>ret=dfs(1,0);
	for (int i=0;i<(1<<N);++i){
		Split(i,2,k);
		int now=0;
		for (int j=k;j>=1;--j) now*=3,now+=b[j];
		f[now].a0=1ll*ret[i]*inv%MOD;
	}
    FWT(f,1);
    for (int i=0;i<M;++i) f[i]=f[i]*f[i];
    FWT(f,-1);
    for (int i=0;i<M;++i){
    	Split(i,3,k);
    	for (int j=1;j<=k;++j){
    		if (b[j]==0) putchar((char)('a'-1+j));
    		else if (b[j]==1) putchar((char)('A'-1+j)),putchar((char)('a'-1+j));
    		else putchar((char)('A'-1+j));
		}
		printf(" %d\n",((f[i].a0-f[i].a1+MOD)%MOD+MOD)%MOD);
	}
}
