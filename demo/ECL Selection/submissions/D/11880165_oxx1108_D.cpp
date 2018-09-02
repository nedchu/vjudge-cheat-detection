#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
const int modd = 1e9 + 7;
const int MAXN = 1e5 + 100;
LL dp[MAXN];
char s[MAXN];
int main()
{
    freopen("Input.txt","r",stdin);
    freopen("Output.txt","w",stdout);
    while(~scanf("%s",s + 1)){
        int len = strlen(s + 1);
        dp[0] = dp[1] = 1;
        for(int i = 2;i <= len;i++){
            if(s[i] == 'E' && (s[i - 1] == 'N' || s[i - 1] == 'S'))
                dp[i] = (dp[i - 1] + dp[i - 2]) % modd;
            else if(s[i] == 'W' && (s[i - 1] == 'N' || s[i - 1] == 'S'))
                dp[i] = (dp[i - 1] + dp[i - 2]) % modd;
            else dp[i] = dp[i - 1];
        }
        printf("%lld\n",dp[len]);
    }

    return 0;
}

