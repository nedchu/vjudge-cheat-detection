#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<bitset>
#include<cstdlib>
#include<cmath>
#include<set>
#include<list>
#include<deque>
#include<map>
#include<queue>

using namespace std;
const int maxnum=1000;
int n,tolv;
int W[maxnum];
int V[maxnum];
int dp[maxnum][maxnum];

int dfs(int i,int j){
    int res;
    if (dp[i][j]>=0)return dp[i][j];
    if(i==n)res=0;
    else if(W[i]>j)res= dfs(i+1,j);
    else res= max(dfs(i+1,j),dfs(i+1,j-W[i])+V[i]);
    dp[i][j]=res;
    return res;
}

int main()
{
   int t;
   scanf("%d",&t);
   for(int i=0;i<t;i++){
    scanf("%d%d",&n,&tolv);
    for(int j=0;j<n;j++){int v;scanf("%d",&v);V[j]=v;}
    for(int j=0;j<n;j++){
        int w;
        scanf("%d",&w);
        W[j]=w;
    }
    memset(dp,-1,sizeof(dp));
    printf("%d\n",dfs(0,tolv)) ;
   }
    return 0;
}
