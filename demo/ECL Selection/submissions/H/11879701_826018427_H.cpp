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
const int MOD = 998244353;
const int MAXN = 5e5+17;
int main(int argc, char const *argv[])
{
    //#ifdef GoodbyeMonkeyKing
    freopen("Input.txt","r",stdin);freopen("Output.txt","w",stdout);
    //#endif
    vector<int > ans(17);
    ans[1] = 8;
    for (int i = 2; i <= 9; ++i)
        ans[i] = ans[i-1]*9;
    int n;
    cin>>n;
    cout<<ans[min(n,9)];
    for (int i = 10; i <= n; ++i)
        cout<<0;
    cout<<endl;
    return 0;
}