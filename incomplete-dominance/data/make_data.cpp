#include <bits/stdc++.h>
#define MAXN 18000000
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
int Rand(){
	return rand()|(rand()<<15);
}
int random(int l,int r) {
	return l+Rand()%(r-l+1);
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
int buc[MAXN];
string str[MAXN];
int main(){
	freopen("data10.in","w",stdout);
    srand(time(NULL));
    int k=13,n=ksm(3,13)*2/3;
    printf("%d %d\n",k,n);
    int all=10000000;
    for (int i=1;i<=all;++i) buc[random(0,n-1)]++;
    int m=ksm(3,k);
    for (int t=0;t<m;++t){
    	string s="";
    	int gene=t;
        for (int i=1;i<=k;++i){
            if (gene%3==0) s+=('a'+i-1),s+=('a'+i-1);
            else if (gene%3==1) s+=('A'+i-1),s+=('a'+i-1);
            else s+=('A'+i-1),s+=('A'+i-1);
            gene/=3;
        }
        str[t]=s;
	}
	random_shuffle(str,str+m);
    for (int id=0;id<n;++id){
    	cout<<str[id];
        printf(" %d\n",1ll*buc[id]*ksm(all,MOD-2)%MOD);
    }
    return 0;
}
