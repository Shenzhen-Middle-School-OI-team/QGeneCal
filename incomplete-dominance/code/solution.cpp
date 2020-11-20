#include <bits/stdc++.h>
#define MAXN 20
#define MAXM 400000
#define MOD 998244353
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
Poly f[MAXM];
int N,M,D;
void FWT(Poly *f,int opr){
	for (int len=1;len<M;len*=3){
		for (int i=0;i<M;i+=len*3){
			for (int j=0;j<len;++j){
				Poly x=f[i+j],y=f[i+j+len],z=f[i+j+len*2];
				// cerr<<i+j<<" "<<i+j+len<<" "<<i+j+len*2<<endl;
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
char ch[MAXN*2];
bool isUpper(char ch){
    return 'A'<=ch&&ch<='Z';
}
int val[MAXM];
int b[MAXM];
void Split(int x){
	int top=0;
	while (x){
		b[++top]=x%3;
		x/=3;
	}
}
#undef int
int main(){
#define int long long 
    k=read(),n=read();
    N=k,M=1;
    for (int i=1;i<=k;++i) M*=3;
    D=ksm(3,MOD-2);
    int inv=ksm((1<<k),MOD-2);
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
                for (int i=now;i<now*2;++i) val[i]=val[i-now];
            }
            now*=3;
        }
        for (int i=0;i<now;++i){
            f[i].a0=(f[i].a0+1ll*val[i]*frequency%MOD*inv%MOD)%MOD;
            val[i]=0;
        }
    }
    FWT(f,1);
    for (int i=0;i<M;++i) f[i]=f[i]*f[i];
    FWT(f,-1);
    for (int i=0;i<M;++i){
    	Split(i);
    	for (int j=1;j<=k;++j){
    		if (b[j]==0) printf("%c",(char)('a'-1+j));
    		else if (b[j]==1) printf("%c%c",(char)('A'-1+j),(char)('a'-1+j));
    		else printf("%c",(char)('A'-1+j));
		}
		printf(" %lld\n",((f[i].a0-f[i].a1+MOD)%MOD+MOD)%MOD);
	}
}