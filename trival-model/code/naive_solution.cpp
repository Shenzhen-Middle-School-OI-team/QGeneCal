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
int f[MAXM];
int N,M;
void FMT(int *f,int opr){
	for (int i=1;i<=N;++i){
		for (int j=0;j<M;++j){
			if (j&(1<<(i-1))){
				f[j]=((f[j]+f[j^(1<<(i-1))]*opr)%MOD+MOD)%MOD;
			}
		}
	}
}
char ch[MAXN*2];
bool isUpper(char ch){
    return 'A'<=ch&&ch<='Z';
}
int val[MAXM];
#undef int
int main(){
#define int long long 
    k=read(),n=read();
    N=k,M=(1<<N);
    int inv=ksm(M,MOD-2);
    while (n--){
        scanf("%s",ch+1);
        int now=1;
        val[0]=1;
        int frequency=read();
        for (int i=1;i<=k;++i){
            if (!isUpper(ch[i*2-1])&&!isUpper(ch[i*2])){
                for (int i=0;i<now;++i) val[i]=val[i]*2,val[i+now]=0;
            }
            if (isUpper(ch[i*2-1])&&isUpper(ch[i*2])){
                for (int i=now;i<now*2;++i) val[i]=val[i-now]*2,val[i-now]=0;
            }
            if (isUpper(ch[i*2-1])&&!isUpper(ch[i*2])){
                for (int i=now;i<now*2;++i) val[i]+=val[i-now];
            }
            now<<=1;
        }
        for (int i=0;i<now;++i){
            cerr<<val[i]<<" ";
            f[i]=(f[i]+1ll*val[i]*frequency%MOD*inv%MOD)%MOD;
            val[i]=0;
        }
        cerr<<endl;
    }
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
