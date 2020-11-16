#include <bits/stdc++.h>
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
int random(int l,int r) {
	return l+rand()%(r-l+1);
}
const int MOD=998244353;
inline int ksm(int b,int k){
    int ans=1;
    while (k){
        if (k&1) ans=1ll*ans*b%MOD;
        b=1ll*b*b%MOD;
        k>>=1;
    }
    return ans;
}
int buc[15];
int main(){
    srand(time(NULL));
    int k=15,n=min(15,ksm(3,k));
    printf("%d %d\n",k,n);
    int all=100000;
    for (int i=1;i<=all;++i) buc[random(1,n)]++;
    for (int id=1;id<=n;++id){
        int gene=random(0,ksm(3,k)-1);
        for (int i=1;i<=k;++i){
            if (gene%3==0) putchar('a'+i-1),putchar('a'+i-1);
            else if (gene%3==1) putchar('A'+i-1),putchar('a'+i-1);
            else putchar('A'+i-1),putchar('A'+i-1);
            gene/=3;
        }
        printf(" %d\n",1ll*buc[id]*ksm(all,MOD-2)%MOD);
    }
    return 0;
}
