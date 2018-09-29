#include<bits/stdc++.h>
using namespace std;
int main(){
  int n,m;
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  scanf("%d%d",&m,&n);
  printf("%d\n",max(2,(m*2+n-1)/n));
}
