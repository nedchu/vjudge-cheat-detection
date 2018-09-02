/* Farewell. */
#include <iostream>
#include <vector>
#include <cstdio>
#include <stack>
#include <cstring>
#include <algorithm>
#include <queue>
#include <map>
#include <string>
#include <cmath>
#include <bitset>
#include <iomanip>
#include <set>
using namespace std;
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define MP make_pair
#define MT make_tuple
#define PB push_back
typedef long long  LL;
typedef unsigned long long ULL;
typedef pair<int,int > pii;
typedef pair<LL,LL> pll;
typedef pair<double,double > pdd;
typedef pair<double,int > pdi;
const int INF = 0x7fffffff;
const LL INFF = 0x7f7f7f7fffffffff;
#define debug(x) std::cerr << #x << " = " << (x) << std::endl
const int MAXM = 5e3+17;
const int MOD = 1e9+7;
const int MAXN = 1e3+17;
LL uN,vN;  //u,v数目
vector<int > G[MAXN];
int linker[MAXN];
int used[MAXN];
bool dfs(int u)
{
    for(int i = 0;i<G[u].size();++i)
    {
        int v = G[u][i];
        if(!used[v])
        {
            used[v]=1;
            if(linker[v]==-1||dfs(linker[v]))
            {
                linker[v]=u;
                return true;
            }    
        }  
    }
    return false;  
}    
int hungary()
{
    int res=0;
    int u;
    memset(linker,-1,sizeof(linker));
    for(u=0;u<uN;u++)
    {
        memset(used,0,sizeof(used));
        if(dfs(u))  res++;
    } 
    return res;   
}
int a[MAXN],t[MAXN];
int cal(int x)
{
    int sum  =0;
    while(x)
    {
        sum+=x%10;
        x/=10;
    }
    return sum;
}
int num[1000+17];
int main(int argc, char const *argv[])
{
    //#ifdef GoodbyeMonkeyKing
    freopen("Input.txt","r",stdin);freopen("Output.txt","w",stdout);
    //#endif
    memset(G, 0, sizeof(G));
    for(int i=1;i<1000;++i) num[i] = cal(i);
    int n,m;
    cin>>n>>m;
    uN = n;
    vN = m;
    for (int i = 0; i < n; ++i)
        cin>>a[i];
    for (int i = 0; i < m; ++i)
        cin>>t[i];
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            // debug(num[a[i]/1000]);
            // debug(num[t[j]%1000]);
            if((num[a[i]/1000]==num[t[j]%1000])||(num[a[i]%1000]==num[t[j]/1000]))
            {
                G[i].push_back(j);
            }
        }
    }
    int ans = hungary();
    cout<<ans<<endl;
    for (int i = 0;i<m;++i)
    {
        if(linker[i]==-1) continue;
        int x = a[linker[i]],y = t[i];
        if(num[x/1000]==num[y%1000])
            cout<<"AT "<<x<<" "<<y<<endl;
        else
            cout<<"TA "<<y<<" "<<x<<endl;
    }
    return 0;
}