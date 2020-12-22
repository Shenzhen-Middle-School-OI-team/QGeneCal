#include <bits/stdc++.h>
#define MAXN 20
#define MAXM 400000
#define int long long
using namespace std;
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
Frac f[MAXM],ans[MAXM];
char ch[MAXN*2];
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
int N,M;
bool isUpper(char ch){
    return 'A'<=ch&&ch<='Z';
}
void FMT(Frac *f,int opr){
    for (int i=1;i<=N;++i){
        for (int j=0;j<M;++j){
            if (j&(1<<(i-1))){
                if (opr==1) f[j]=f[j]+f[j^(1<<(i-1))];
                else f[j]=f[j]-f[j^(1<<(i-1))];
            }
        }
    }
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
                for (int j=0;j<(int)child.size();++j) v[j]=v[j]+child[j]*2;
            }
            else if (i==1){
                for (int j=0;j<(int)child.size();++j) v[j]=v[j]+child[j],v[j+child.size()]=v[j+child.size()]+child[j];
            }
            else if (i==2){
                for (int j=0;j<(int)child.size();++j) v[j+child.size()]=v[j+child.size()]+child[j]*2;
            }
        }
        return v;
    }
}
using namespace Trie;
#undef int
int main(){
#define int long long
    if (scanf("%lld %lld\n",&k,&n)==EOF) Exit("输入不完整");
    N=k,M=(1<<N);
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
    for (int i=0;i<M;++i) f[i]=ret[i]/M;
    FMT(f,1);
    for (int i=0;i<M;++i) f[i]=f[i]*f[i];
    FMT(f,-1);
    for (int i=0;i<M;++i){
        for (int j=1;j<=k;++j){
            if (i&(1<<(j-1))) putchar('A'+j-1);
            else putchar('a'+j-1);
        }
        putchar(' ');
        f[i].Print();
    }
    return 0;
}