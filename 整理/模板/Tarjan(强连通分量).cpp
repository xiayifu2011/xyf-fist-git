#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
vector<int>S[N];
int dfn[N],low[N];
/*
dfn为深搜时节点编号，即dfs序

low为在dfs树中用一条返祖边能找到最早的祖宗编号
*/
int root=0;//dfs树的根
bool in_stack[N];
int n,m;
int cnt;

void dfs_buildtree(int i){	
	in_stack[i]=1;//标记为放入栈中
	/*
	由于dfs搜索顺序
	栈中节点在dfs树上均在同一条由根结点起始的链上
	即直系血亲
	祖宗——曾孙 关系
	*/
	++cnt;
	low[i]=dfn[i]=cnt;//当前dfs到第cnt个点
	for(int nex:S[i]){
		if(!dfn[nex]){//以前没搜到过，该点在其子树中
			dfs_buildtree(nex);//深搜
			low[i]=min(low[i],low[nex]);//如若子树中存在某点可以找到更小dfn的祖宗，那么该点自然也可以
		}else if(in_stack[nex]){//搜到祖宗了，是返祖边
			low[i]=min(low[i],dfn[nex]);
			/*为防止在之前有子树中的返祖边更新过其low值使其更小，故取min
			  注意low定义，选用min(low[i],dfn[nex])而非min(low[i],low[nex]);
			*/
		//以下三行可以不写
		}else{
			continue;//既不是祖宗，以前又搜到过，说明早处理过了
			//low值的定义为用返祖边能找到最小dfn的祖宗，该情况下既不是子树又不是祖宗对dfn完全没有影响
		}
	}
	in_stack[i]=0;//标记为弹出，回溯的时候该节点子树已经搜完了，栈里不会再有其子孙，故弹出
}

//有向图强连通分量
vector<vector<int>>scc_node;//scc_node[i]中存储所有第i个连通分量的点
int scc_scc[N];//scc_scc[i]表示i节点所属第几个连通分量
//通常以上两种选一个就够了
int scc_num;//目前连通分量的个数，给连通分量计数用
stack<int>st;//之前我们只管节点是否在栈中，这次我们还关注其栈中顺序（原理见下文）
void dfs_scc(int i){//
/*
	前半部分与dfs_builtree几乎一样
	只是记得将节点入栈
*/
	in_stack[i]=1;
	st.push(i);
	++cnt;
	low[i]=dfn[i]=cnt;
	for(int nex:S[i]){
		if(!dfn[nex]){
			dfs_scc(nex);
			low[i]=min(low[i],low[nex]);
		}else if(in_stack[nex]){
			low[i]=min(low[i],dfn[nex]);
		}else{
			continue;
		}
	}
	/*
	在强连通分量中，必然有一个点在dfs中是最先遍历的
	在该连通分量不存在点dfn比其dfn更小
	又因其在该强连通分量，所以它不能通过某边找到更小dfn的点
	故其low值与dfn相同
	反之亦然
	因其low值与dfn相同
	故它不能通过某边找到更小dfn的点
	故在其存在的连通分量不存在点dfn比其dfn更小
	故其是在其所在连通分量中dfs最先遍历的
	那么显然：low值等于该点dfn值且属于该点子树的所有点都有办法到达该点
	所以这些点在该点的连通分量中
	又因为这些点均为该点子树
	所以直接弹出dfs栈中该点上方的点并且处理即可
	*/
	if(low[i]==dfn[i]){//找到新连通分量的根了
		int j;
		scc_num++;//连通分量数加一
		/*取出该点的子树中还剩的点
		为什么该点的子树中还剩的点就在该点的连通分量中呢
		因为不在该点的连通分量中又在该点的子树中的点
		一定在搜到它并回溯的时候就找到了它的连通分量并弹出栈了
		*/
		while(1){
			j=st.top();//取点
			st.pop();
			in_stack[j]=0;//标记
			scc_node[scc_num].push_back(j);//
			scc_scc[j]=scc_num;//处理
			//为防止该点所在连通分量只有该点本身，
			//故至少做一次
			if(j==i){
				break;
			}
		}
	}
}
int main() {
	//
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		S[u].push_back(v);
		//S[v].push_back(u);
		S[0].push_back(u);
		S[0].push_back(v);//建立超级根接点0，以防图不连通
	}
	scc_node.resize(n+2);
	root=0;
	dfs_scc(root);
	cout<<scc_num-1<<endl;
	for(int i=1;i<scc_num;i++){
		cout<<i<<":"<<endl;
		for(int j:scc_node[i]){
			cout<<j<<" ";
		}
		cout<<endl;
	}

	return 0;
}
 