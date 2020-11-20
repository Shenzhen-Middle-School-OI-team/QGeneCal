#include <bits/stdc++.h>
#define MAXN 20
#define MAXM 400000
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
double add(double x,double y){
	return x+y;
}
double mul(double x,double y){
	return x*y;
}
struct Poly{
	double a0,a1,a2;
};
Poly operator + (const Poly &A,const Poly &B){
	return Poly{A.a0+B.a0,A.a1+B.a1,A.a2+B.a2};
}
Poly operator * (const Poly &A,const Poly &B){
	return Poly{
		A.a0*B.a0+A.a1*B.a2+A.a2*B.a1,
		A.a0*B.a1+A.a1*B.a0+A.a2*B.a2,
		A.a0*B.a2+A.a1*B.a1+A.a2*B.a0
	};
}
Poly operator * (const Poly &A,double d){
	return Poly{mul(A.a0,d),mul(A.a1,d),mul(A.a2,d)};
}
int n,k;
Poly f[MAXM];
int N,M;
double D;
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
	// if (opr==-1){
	// 	for (int i=0;i<M;++i){
	// 		f[i].a0=mul(f[i].a0,D);
	// 	}
	// }
}
char ch[MAXN*2];
bool isUpper(char ch){
    return 'A'<=ch&&ch<='Z';
}
double val[MAXM];
int b[MAXM];
void Split(int x){
	int top=0;
	while (x){
		b[++top]=x%3;
		x/=3;
	}
	// reverse(b+1,b+1+top);
}
void Out(int x){
	Split(x);
	for (int j=1;j<=k;++j){
		if (b[j]==0) printf("%c",(char)('a'-1+j));
		else if (b[j]==1) printf("%c%c",(char)('A'-1+j),(char)('a'-1+j));
		else printf("%c",(char)('A'-1+j));
	}
}
int main(){
    k=read(),n=read();
    N=k,M=1;
    for (int i=1;i<=k;++i) M*=3;
    D=1.00/3.00;
    double inv=1.00/((double)(1<<k));
    while (n--){
        scanf("%s",ch+1);
        int now=1;
        val[0]=1;
		double frequency;
		cin>>frequency;
        for (int t=1;t<=k;++t){
            if (!isUpper(ch[t*2-1])&&!isUpper(ch[t*2])){
                for (int i=0;i<now;++i) val[i]=val[i]*2,val[i+now]=0;
            }
            if (isUpper(ch[t*2-1])&&isUpper(ch[t*2])){
                for (int i=now;i<now*2;++i) val[i]=val[i-now]*2,val[i-now]=0;
            }
            if (isUpper(ch[t*2-1])&&!isUpper(ch[t*2])){
                for (int i=now;i<now*2;++i) val[i]=val[i-now];
            }
            now*=3;
        }
        for (int i=0;i<now;++i){
            f[i].a0+=val[i]*frequency*inv;
            val[i]=0;
        }
    }
	for (int i=0;i<M;++i){
		printf("%lf\n",f[i].a0);
	}
    FWT(f,1);
    for (int i=0;i<M;++i) f[i]=f[i]*f[i];
    FWT(f,-1);
	double sum=0;
    for (int i=0;i<M;++i){
		Out(i);
		printf(" %lf\n",f[i].a0-f[i].a1);
		sum+=f[i].a0-f[i].a1;
	}
	cerr<<sum<<endl;
}
/*
2 2
AaBb 0.333333
Aabb 0.666667
*/