#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 5e5 + 5;
// LCA
vector<int> S[N];
int n, m, s;
int deep[N];
int f[N][30];
void dfs(int dep, int i)
{
    deep[i] = dep;
    for (int j : S[i])
    {
        if(j==f[i][0]){
            continue;
        }
        f[j][0]=i;
        dfs(dep + 1, j);
    }
}
int LCA(int a,int b){
    if(deep[a]<deep[b]){
        swap(a,b);
    }
    int dep=deep[a]-deep[b];
    int cnt=0;
    while(dep>0){
        if(dep%2==1){
            a=f[a][cnt];
        }
        dep>>=1;
        cnt++;
    }
    if(a==b){
        return a;
    }
    for(int h=20;h>=0;h--){
        if(f[a][h]!=f[b][h]){
            a=f[a][h];
            b=f[b][h];
        }
    }
    return f[a][0];
}
signed main()
{
    cin >> n >> m >> s;
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        S[u].push_back(v);
        S[v].push_back(u);
    }
    dfs(0,s);  
    for (int j = 1; j <= 20; j++)
    {
        for (int i = 1; i <= n; i++)
        {
            f[i][j] = f[f[i][j - 1]][j - 1];
        }
        
    }
    for(int q=1;q<=m;q++){
        int u,v;
        cin>>u>>v;
        cout<<LCA(u,v)<<endl;
    }
    return 0;
}
