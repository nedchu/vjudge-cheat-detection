#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
const LL maxn = 100005;
LL rec[maxn];
LL sum[maxn];
LL N,K,maxi,maxp;
void solve(){
    if((maxp - 1) > K){printf("KEK\n");return ;}
    else if(sum[maxp - 1] >= K) {printf("YES\n");return ;}

    LL tot = rec[maxp] + N - 1;
    LL leftt = sum[maxp - 1] - (maxp - 1);
    LL kk = (K - (maxp - 1)) / tot;
    LL modd = (K - (maxp - 1)) % tot;
    modd -= leftt;
    if(modd <= 0) {printf("YES\n");return ;}
    LL hsf = sum[N] - rec[maxp] - (N - 1);
    if(modd <= hsf * kk) {printf("YES\n");return ;}
    printf("KEK\n");return ;
}

int main(){
    freopen("Input.txt","r",stdin);
    freopen("Output.txt","w",stdout);

    scanf("%lld%lld",&N,&K);
    maxi = 0;maxp = 1;sum[0] = 0;
    for(LL i = 1;i <= N;i++){
        scanf("%lld",&rec[i]);
        sum[i] = sum[i - 1] + rec[i];
        if(rec[i] > maxi){
            maxi = rec[i];
            maxp = i;
        }
    }
    solve();
    return 0;
}
