#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

int main()
{
    freopen("Input.txt","r",stdin);
    freopen("Output.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        if(n <= 9){
            LL num = 8;
            n--;
            while(n--){
                num*=9;
            }
            printf("%lld\n",num);
            continue;
        }
        else{
            string s="344373768";
            n=n-9;
            while(n--){
                s+="0";
            }
            cout << s << endl;
        }

    }

    return 0;
}

