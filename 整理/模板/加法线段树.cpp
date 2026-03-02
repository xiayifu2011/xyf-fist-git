#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e5+5;
int n;
int a[N];
struct TREE{
    int l,r,val,sum,tag;
    //左区间,右区间,最大值,区间和,懒标记
    void make_tag(int k){//给该节点所代表区间加上k
        sum+=(l-r+1)*k;
        val+=k;
        tag+=k;
    }
}D[N*4];//线段树的花语:数组开四倍
void push_up(int u){//用子节点的数据更新父节点
    D[u].val=max(D[u*2].val,D[u*2+1].val);
    D[u].sum=D[u*2].sum+D[u*2+1].sum;
}
void push_down(int u){//将父节点的懒标记数据下放给子节点
    D[u*2].make_tag(D[u].tag);
    D[u*2+1].make_tag(D[u].tag);
    D[u].tag=0;//下放懒标记后清零
}
void build_tree(int u,int L,int R){//递归建树
//L是目前处理的左区间,R是目前处理的右区间,u是目前处理到的线段树节点的编号
    if(L==R){//到叶节点了
        D[u].l=L;
        D[u].r=R;
        D[u].val=D[u].sum=a[L];
        return ;
    }
    D[u].l=L;
    D[u].r=R;
    int mid=(L+R)>>1;
    build_tree(u*2,L,mid);
    build_tree(u*2+1,mid+1,R);//左右子树
    push_up(u);//处理该节点数据
}
void D_add(int u,int L,int R,int k){//给[L,R]区间加上k
    if(D[u].l>R||D[u].r<L){//目前节点所代表区间与目标区间不重合
        return;//不对该区间操作
    }
    if(L<=D[u].l&&D[u].r<=R){//目前节点所代表区间被目标区间完全重合
        D[u].make_tag(k);//整个区间加k
        return;
    }
    //如果目前区间与目标区间有重合或目标区间被目前区间包含
    //那么将目前区间砍半递归处理
    //即递归其左右子树
    push_down(u);//先下放
    D_add(u*2,L,R,k);
    D_add(u*2+1,L,R,k);
    push_up(u);//在更新该节点
    //如果目前区间与目标区间只有部分重合
    //那么在处理目前区间是是否需要考虑不在目前区间而在目标区间内的部分呢
    //显然是不用的
    //我们只需要保证最开始的区间完全包含目标区间即可
    //最简单最通用的方式就是直接从[1,n]开始递归
    //显然[1,n]区间的树节点编号为1
}
int D_max_ask(int u,int L,int R){//查询区间最大值
    if(D[u].l>R||D[u].r<L){//完全不在目标区间内
        return LONG_LONG_MIN;//为防止其对答案造成影响
    }
    if(L<=D[u].l&&D[u].r<=R){//目前节点所代表区间被目标区间完全重合
        return D[u].val;//返回最值
    }
    //与区间加法同理
    push_down(u);
    return max(D_max_ask(u*2,L,R),D_max_ask(u*2+1,L,R));
}
int D_sum_ask(int u,int L,int R){//区间求和
//与区间最值一毛一样
    if(D[u].l>R||D[u].r<L){
        return 0;
    }
    if(L<=D[u].l&&D[u].r<=R){
        return D[u].sum;
    }
    push_down(u);
    return D_sum_ask(u*2,L,R)+D_sum_ask(u*2+1,L,R);
}
signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];//原序列
    }
    build_tree(1,1,n);//建树
    int q;
    cin>>q;//查询次数
    for(int i=1;i<=q;i++){
        string op;
        cin>>op;
        if(op=="add"){
            int L,R,k;
            cin>>L>>R>>k;
            D_add(1,L,R,k);
        }else if(op=="max"){
            int L,R;
            cin>>L>>R;
            cout<<D_max_ask(1,L,R)<<endl;
        }else if(op=="sum"){
            int L,R;
            cin>>L>>R;
            cout<<D_sum_ask(1,L,R)<<endl;
        }
    }
  return 0;
}
