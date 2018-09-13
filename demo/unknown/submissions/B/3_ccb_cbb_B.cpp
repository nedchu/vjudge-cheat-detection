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
    //memset(dp,-1,sizeof(dp));
    for(int i=1;i<=n;i++){
        for(int j=0;j<=tolv;j++){
            if(W[i-1]>j)dp[i][j]= dp[i-1][j];
            else dp[i][j]= max(dp[i-1][j],dp[i-1][j-W[i-1]]+V[i-1]);
        }
    }
    printf("%d\n",dp[n][tolv]);
    memset(dp,0,sizeof(dp));
   }
    return 0;
}
