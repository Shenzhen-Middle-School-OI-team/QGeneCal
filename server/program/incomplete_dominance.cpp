#include <bits/stdc++.h>
#define MAXN 25
#define MAXM 500005
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
void Exit(string msg){
    cerr<<msg<<endl;
    exit(0);
}
struct Frac{
    int x,y;
    void Simp(){
        int g=__gcd(x,y);
        if (g==0) return ;
        x/=g,y/=g;
    }
    void Read(){
        if (scanf("%lld/%lld",&x,&y)==EOF) Exit("输入不完整");
        if (y==0) Exit("分母不能为 0");
        if (x<0||y<0) Exit("不能出现负数");
    }
    void Print(){
        printf("%lld/%lld\n",x,y);
    }
};
Frac operator * (Frac A,Frac B){
    Frac ans=Frac{A.x*B.x,A.y*B.y};
    ans.Simp();
    return ans;
}
Frac operator * (Frac A,int x){
    Frac ans=Frac{A.x*x,A.y};
    ans.Simp();
    return ans;
}
Frac operator / (Frac A,int x){
    Frac ans=Frac{A.x,A.y*x};
    ans.Simp();
    return ans;
}
Frac operator + (Frac A,Frac B){
    if (A.x==0&&A.y==0) return B;
    if (B.x==0&&B.y==0) return A;
    Frac ans=Frac{A.x*B.y+A.y*B.x,A.y*B.y};
    ans.Simp();
    return ans;
}
Frac operator - (Frac A,Frac B){
    return A+Frac{-B.x,B.y};
}
char ch[MAXN*2];
bool isUpper(char ch){
    return 'A'<=ch&&ch<='Z';
}
int n,k;
inline int ksm(int b,int k){
    int ans=1;
    while (k){
        if (k&1) ans=ans*b;
        b=b*b;
        k>>=1;
    }
    return ans;
}
namespace Trie{
    struct node{
        int ch[3];
        Frac end;
    }tree[MAXN*MAXM];
    #define ch(x,i) tree[x].ch[i]
    int tot=1;
    void Insert(Frac frequency){
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
        tree[now].end=tree[now].end+frequency;
    }
    vector<Frac>dfs(int node,int depth){
        vector<Frac>v;
        v.resize(1<<(k-depth));
        if (depth==k){
            v[0]=tree[node].end;
            return v;
        }
        for (int i=0;i<=2;++i){
            if (!ch(node,i)) continue;
            vector<Frac>child=dfs(ch(node,i),depth+1);
            if (i==0){
                for (int j=0;j<child.size();++j) v[j]=v[j]+Frac{child[j].x*2,child[j].y};
            }
            else if (i==1){
                for (int j=0;j<child.size();++j) v[j]=v[j]+child[j],v[j+child.size()]=v[j+child.size()]+child[j];
            }
            else if (i==2){
                for (int j=0;j<child.size();++j) v[j+child.size()]=v[j+child.size()]+Frac{child[j].x*2,child[j].y};
            }
        }
        return v;
    }
}
using namespace Trie;
struct Poly{
    Frac a0,a1,a2;
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
Poly operator * (const Poly &A,int d){
    return Poly{A.a0*d,A.a1*d,A.a2*d};
}
Poly operator / (const Poly &A,int d){
    return Poly{A.a0/d,A.a1/d,A.a2/d};
}
Poly f[MAXM];
int N,M;
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
                    f[i+j]=f[i+j]/3;
                    f[i+j+len]=f[i+j+len]/3;
                    f[i+j+len*2]=f[i+j+len*2]/3;
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
#undef int
int main(){
#define int long long
    if (scanf("%lld %lld\n",&k,&n)==EOF) Exit("输入不完整");
    N=k,M=1;
    for (int i=1;i<=k;++i) M*=3;
    Frac sum=Frac{0,1};
    while (n--){
        scanf("%s",ch+1);
        Frac frequency;
        frequency.Read();
        sum=sum+frequency;
        Insert(frequency);
    }
    if (sum.x!=sum.y) Exit("相加之和必须为 1");
    vector<Frac>ret=dfs(1,0);
    for (int i=0;i<(1<<N);++i){
        Split(i,2,k);
        int now=0;
        for (int j=k;j>=1;--j) now*=3,now+=b[j];
        f[now].a0=ret[i]/((int)(1<<N));
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
        putchar(' ');
        Frac ans=f[i].a0-f[i].a1;
        ans.Print();
    }
}