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
const int MAXN = 1e5+17;
int dp[MAXN][2];
int main(int argc, char const *argv[])
{
    //#ifdef GoodbyeMonkeyKing
    freopen("Input.txt","r",stdin);freopen("Output.txt","w",stdout);
    //#endif
    memset(dp, 0, sizeof(dp));
    string str;
    cin>>str;
    dp[0][0] = 1;
    dp[0][1] = 0;
    for (int i = 1; i <= str.length(); ++i)
    {
        if((str[i]=='E'||str[i]=='W')&&(str[i-1]=='N'||str[i-1]=='S'))
            dp[i][1] = (dp[i][1]+dp[i-1][0])%MOD;
        dp[i][0] = (dp[i][0]+dp[i-1][0] + dp[i-1][1])%MOD;
    }
    cout<<(dp[str.length()][0]+dp[str.length()][1])%MOD<<endl;
    return 0;
}