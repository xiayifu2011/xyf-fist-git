#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 5e5 + 5;
int n,q,r,mod;//n个节点,操作数
int point_w[N],dfs_w[N];//
int dfn[N];//
int top[N];
vector<int>S[N];
int deep[N],fa[N],siz[N],son[N];
struct TREE{
    int ls,rs;
    int val,tag;
    void make_tag(int k){
        val+=((rs-ls+1)*k)%mod;
        tag+=k;
        tag%=mod;
    }
    
}D[N*4];
void push_up(int u){
    D[u].val=(D[u*2].val+D[u*2+1].val)%mod;
}
void push_down(int u){
    if(D[u].tag!=0){
        D[u*2].make_tag(D[u].tag);
        D[u*2+1].make_tag(D[u].tag);
        D[u].tag=0;
    }
}
void build_tree(int u,int l,int r){
    D[u].ls=l;
    D[u].rs=r;
    if(l==r){
        D[u].val=dfs_w[l];
        return;
    }
    int mid =(l+r)>>1;
    build_tree(u*2,l,mid);
    build_tree(u*2+1,mid+1,r);
    push_up(u);
}

void D_add(int u,int L,int R,int k){
    if(D[u].ls>R||D[u].rs<L){
        return;
        //目前找到的区间与目标区间完全不重合
    }
    if(L<=D[u].ls&&D[u].rs<=R){
        D[u].make_tag(k);//目前找到的区间与目标区间完全重合
    }else{//目前找到的区间与目标区间部分重合
        push_down(u);//下
        D_add(u*2,L,R,k);
        D_add(u*2+1,L,R,k);
        push_up(u); 
    }
}

int D_ask(int u,int L,int R){
    if(D[u].ls>R||D[u].rs<L){
        return 0;
    }
    if(L<=D[u].ls&&D[u].rs<=R){
        D[u].val%=mod;
        return D[u].val;
    }else{
        push_down(u);
        return (D_ask(u*2,L,R)+D_ask(u*2+1,L,R))%mod;
    }
}

//

void dfs_first(int u,int f,int cnt){

    fa[u]=f;
    deep[u]=cnt;
    siz[u]=1;
    int max_siz=0;//
    for(int i:S[u]){
        if(i==fa[u]){
            continue;
        }//
        dfs_first(i,u,cnt+1);
        siz[u]+=siz[i];
        if(siz[i]>max_siz){
            max_siz=siz[i];
            son[u]=i;
        }//
    }
}
int dfs_id=0;
void dfs_second(int u,int topfa){//
    dfn[u]=++dfs_id;
    top[u]=topfa;
    dfs_w[dfs_id]=point_w[u];
    if(!son[u]){
        return;//
    }
    dfs_second(son[u],topfa);
    for(int i:S[u]){
        if(i==son[u]||i==fa[u]){
            continue;
        }
        dfs_second(i,i);
    }
}
void lian_add(int x,int y,int k){
    while(top[x]!=top[y]){
        if(deep[top[x]]<deep[top[y]]){
            swap(x,y);
        }
        D_add(1,dfn[top[x]],dfn[x],k);
        x=fa[top[x]];
    }
    if(deep[x]>deep[y]){
        swap(x,y);
    }
    D_add(1,dfn[x],dfn[y],k);
}
int lian_ask(int x,int y){
    int ans=0;
    while(top[x]!=top[y]){
        if(deep[top[x]]<deep[top[y]]){
            swap(x,y);
        }
        ans+=D_ask(1,dfn[top[x]],dfn[x]);
        ans%=mod;
        x=fa[top[x]];
    }
    if(deep[x]>deep[y]){
        swap(x,y);
    }
    ans+=D_ask(1,dfn[x],dfn[y]);
    ans%=mod;
    return ans;
}
signed main()
{
    cin>>n>>q>>r>>mod;
    for(int  i=1;i<=n;i++){
        cin>>point_w[i];
    }
    for(int i=1;i<n;i++){
        int x,y;
        cin>>x>>y;
        S[x].push_back(y);
        S[y].push_back(x);
    }
    dfs_first(r,0,0);
    dfs_second(r,r);
    build_tree(1,1,n);
    while(q--){
        int op;
        cin>>op;
        int x,y,z;

        if(op==1){
            cin>>x>>y>>z;
            lian_add(x,y,z);
        }else if(op==2){
            cin>>x>>y;
            cout<<lian_ask(x,y)<<endl;
        }else if(op==3){
            cin>>x>>z;
            D_add(1,dfn[x],dfn[x]+siz[x]-1,z);
        }else{
            cin>>x;
            cout<<D_ask(1,dfn[x],dfn[x]+siz[x]-1)<<endl;
        }
    }
  return 0;
}
