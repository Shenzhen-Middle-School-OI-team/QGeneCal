/*
Trie ×ö·¨ 
*/ 

#include <bits/stdc++.h>
#define MAXN 20
#define MAXM 400000
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
const int MOD=998244353;
int f[MAXM],ans[MAXM];
char ch[MAXN*2];
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
int N,M;
bool isUpper(char ch){
    return 'A'<=ch&&ch<='Z';
}
void FMT(int *f,int opr){
	for (int i=1;i<=N;++i){
		for (int j=0;j<M;++j){
			if (j&(1<<(i-1))){
				f[j]=((f[j]+f[j^(1<<(i-1))]*opr)%MOD+MOD)%MOD;
			}
		}
	}
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
		v.resize(1<<(k-depth));
//		cerr<<"resize:"<<(1<<(k-depth))<<endl;
		if (depth==k){
			v[0]=tree[node].end;
			return v;
		}
		for (int i=0;i<=2;++i){
			if (!ch(node,i)) continue;
			vector<int>child=dfs(ch(node,i),depth+1);
			if (i==0){
				for (int j=0;j<child.size();++j) v[j]=(v[j]+2*child[j])%MOD;
			}
			else if (i==1){
				for (int j=0;j<child.size();++j) v[j]=(v[j]+child[j])%MOD,v[j+child.size()]=(v[j+child.size()]+child[j])%MOD;
			}
			else if (i==2){
				for (int j=0;j<child.size();++j) v[j+child.size()]=(v[j+child.size()]+2*child[j])%MOD;
			}
		}
		return v;
	}
}
using namespace Trie;
#undef int
int main(){
#define int long long 
    k=read(),n=read();
    N=k,M=(1<<N);
    int inv=ksm(M,MOD-2);
    while (n--){
        scanf("%s",ch+1);
        int frequency=read();
        Insert(frequency);
    }
    vector<int>ret=dfs(1,0);
    for (int i=0;i<M;++i) f[i]=1ll*ret[i]*inv%MOD;
    FMT(f,1);
    for (int i=0;i<M;++i) f[i]=1ll*f[i]*f[i]%MOD;
    FMT(f,-1);
    for (int i=0;i<M;++i){
        for (int j=1;j<=k;++j){
            if (i&(1<<(j-1))) putchar('A'+j-1);
            else putchar('a'+j-1);
        }
        putchar(' ');
        printf("%lld\n",f[i]);
    }
    return 0;
}

/*
2 2
AaBb 332748118
Aabb 665496236
*/
