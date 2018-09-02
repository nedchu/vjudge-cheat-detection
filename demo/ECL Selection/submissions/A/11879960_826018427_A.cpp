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

int main()
{
    freopen("Input.txt","r",stdin);freopen("Output.txt","w",stdout);
    int n,k;
    cin>>n>>k;
    if (n<=k) cout<<2<<endl;
    else{
    int ans=2*(n/k);
    int left=2*(n%k);
    if (left!=0){if (left<=k) ans++; else ans+=2;}
    cout<<ans<<endl;
    }
    return 0;
}