#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
const int MAXN = 10;
int a[MAXN],b[MAXN];
int tot;
bool factor(int n)
{
    int temp,i,now;
    temp = (int)((double)sqrt(n) + 1);
    tot = 0;
    now = n;
    for(i = 2;i <= temp;++i) if(now % i == 0){
        a[++tot] = i;
        b[tot] = 0;
        if(tot > 3) return false;
        while(now % i == 0){
            ++b[tot];
            now /= i;
            if(b[tot] > 1)return false;
        }
    }
    if(now!= 1){
        a[++tot] = now;
        b[tot] = 1;
    }
    if(tot == 3) return true;
    else return false;
}
int main()
{
    freopen("Input.txt","r",stdin);
    freopen("Output.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        if(factor(n)) printf("YES\n");
        else printf("NO\n");
    }

    return 0;
}

