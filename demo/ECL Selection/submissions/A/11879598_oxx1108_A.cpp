#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

int main()
{
    freopen("Input.txt","r",stdin);
    freopen("Output.txt","w",stdout);
    int n,k;
    while(~scanf("%d%d",&n,&k))
    {
        if(n <= k) printf("2\n");
        else{
            if((2 * n) % k == 0) printf("%d\n",(2 * n)/k);
            else printf("%d\n",(2 * n) / k + 1);
        }
    }

    return 0;
}

