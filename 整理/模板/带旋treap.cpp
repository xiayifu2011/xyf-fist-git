#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
// #define  ls(x) D[D[x].ls]
// #define  rs(x) D[D[x].rs]
int root;
int n;

struct TREAP{
    int val,pri;
    int siz;
    int ls=0,rs=0;
    int id;
}D[N];
void push_up(int u){
    D[u].siz=D[D[u].ls].siz+D[D[u].rs].siz+1;
}

void right_rotate(int &u){
    int tmp=D[u].ls;
    D[u].ls=D[tmp].rs;
    D[tmp].rs=u;
    if(u!=0){
        push_up(u);
    }
    if(tmp!=0){
        push_up(tmp);
    }
    u=tmp;
}
void left_rotate(int &u){
    int tmp=D[u].rs;
    D[u].rs=D[tmp].ls;
    D[tmp].ls=u;
    if(u!=0){
        push_up(u);
    }
    if(tmp!=0){
        push_up(tmp);
    }
    u=tmp;
}

int cnt=0;
void insert(int &u,int num){
    if(u!=0){
        D[u].siz++;
    }
    if(u==0){
        cnt++;
        TREAP &nex=D[cnt];
        nex.val=num;
        nex.pri=(rand()+INT_MAX)%INT_MAX;
        nex.siz=1;
        u=cnt;
        return;
    }

    if(num>=D[u].val){
        insert(D[u].rs,num);
    }else{
        insert(D[u].ls,num);
    }

    if(D[u].ls!=0&&D[u].pri>D[D[u].ls].pri){
        right_rotate(u);
    }
    if(D[u].rs!=0&&D[u].pri>D[D[u].rs].pri){
        left_rotate(u);
    }
   push_up(u);
}

void del(int &u,int num){
    if(D[u].val==num){
        if(D[u].ls==0&&D[u].rs==0){
            u=0;
            return;
        }
        if(D[u].ls==0){
            u=D[u].rs;
            return;
        }
        if(D[u].rs==0){
            u=D[u].ls;
            return;
        }
        if(D[D[u].ls].pri<D[D[u].rs].pri){
            right_rotate(u);
            del(D[u].rs,num);
             push_up(u);
        return;
        }else{
            left_rotate(u);
            del(D[u].ls,num);
             push_up(u);
        return;
        }
       
    }
    D[u].siz--;
    if(num>=D[u].val){
        del(D[u].rs,num);
    }else{
        del(D[u].ls,num);
    }
    push_up(u);
}


int ask(int u,int num){
    if(u==0){
        return 0;
    }
    if(num<=D[u].val){
        return ask(D[u].ls,num);
    }else{
        return ask(D[u].rs,num)+1+D[D[u].ls].siz;
    }
}

int find(int u,int gaol){
    if(gaol==D[D[u].ls].siz+1){
        return D[u].val;
    }
    if(gaol>D[D[u].ls].siz+1){
        return find(D[u].rs,gaol-(D[D[u].ls].siz+1));
    }
    return find(D[u].ls,gaol);
}

int fron(int x){
    int u=root;
    int ans=0;
    while(u!=0){
        if(x>D[u].val){
            ans=u;
            u=D[u].rs;
        }else{
            u=D[u].ls;
        }
    }
    return D[ans].val;
}
int bac(int x){
    int u=root;
    int ans=0;
    while(u!=0){
        if(x<D[u].val){
            ans=u;
            u=D[u].ls;
        }else{
            u=D[u].rs;
        }
    }
    return D[ans].val;
}


signed main()
{
    srand(time(NULL));
    cin>>n;
    for(int i=1;i<=n;i++){
        int opt,x;
        cin>>opt>>x;
        if(opt==1){
            insert(root,x);
        }
        if(opt==2){
            del(root,x);
        }
        if(opt==3){
            cout<<ask(root,x)+1<<endl;
        }
        if(opt==4){
            cout<<find(root,x)<<endl;
        }
        if(opt==5){
            cout<<fron(x)<<endl;
        }
        if(opt==6){
           cout<<bac(x)<<endl;
        }
    }
    return 0;
}