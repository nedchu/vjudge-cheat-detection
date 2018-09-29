#include<bits/stdc++.h>
using namespace std;
int n;
int ans[10];
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    ans[1]=8;
    cin>>n;
    for (int i=2;i<=9;i++) ans[i]=ans[i-1]*9;
    if (n<9){
        printf("%d\n",ans[n]);
    }else{
        printf("%d",ans[9]);
        n-=9;
        for (;n--;)printf("0");
        puts("");
    }
    return 0;
}
