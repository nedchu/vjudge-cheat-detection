#include<bits/stdc++.h>
using namespace std;
int n,m,x=1,y=1;
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
const int N=505*505;
int qx[N],qy[N],ans;
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cin>>n>>m;
    if (n==1||m==1){
        puts("0");
        return 0;
    }
    bool flag=0;
    if (n%2==1&&m%2==0){
        swap(n,m);
        flag=1;
    }
    if (n%2==1&&m%2==1){
        for (int i=1;i<n-3;i+=2){
            for (int j=1;j<m;j++)
                qx[++ans]=i,qy[ans]=j;
            if (i+2<=n)
                qx[++ans]=i+1,qy[ans]=m-1;
        }
        for (int j=1;j<m;j+=2){
            for (int i=n-2;i<=n-1;i++)
                qx[++ans]=i,qy[ans]=j;
            if (j+2<=m)
                qx[++ans]=n-1,qy[ans]=j+1;
        }
    }else{
        for (int i=1;i<n;i+=2){
            if (i!=1)
                qx[++ans]=i-1,qy[ans]=m-1;
            for (int j=1;j<m;j++)
                qx[++ans]=i,qy[ans]=j;
        }
    }
    if (flag)
        for (int i=1;i<=ans;i++) swap(qx[i],qy[i]);
    printf("%d\n",ans);
    for (int i=1;i<=ans;i++)
        printf("%d %d\n",qx[i],qy[i]);
    return 0;
}
