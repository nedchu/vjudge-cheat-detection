#include<bits/stdc++.h>

using namespace std;
const int MAXN = 300;
int n,m,V;
int pre[MAXN],post[MAXN];

vector<int>G[MAXN];
int match[MAXN];
bool used[MAXN];
char s[MAXN][10];
void add_edge(int u,int v)
{
    G[u].push_back(v);
    G[v].push_back(u);
}

bool dfs(int v)
{
    used[v] = true;
    for(int i = 0;i < G[v].size();i++){
        int u = G[v][i],w = match[u];
        if(w < 0 || !used[w] && dfs(w)){
            match[v] = u;
            match[u] = v;
            return true;
        }
    }
    return false;
}
int bipartite_matching()
{
    int res = 0;
    memset(match,-1,sizeof(match));
    for(int v = 1;v <= V;v++){
        if(match[v] < 0){
            memset(used,0,sizeof(used));
            if(dfs(v))
                res++;
        }
    }
    return res;
}

int main(){
    freopen("Input.txt","r",stdin);
    freopen("Output.txt","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    V = n + m;
    for(int i = 1;i <= n;i++){
        scanf("%s",s[i]);
        pre[i] = s[i][0] + s[i][1] + s[i][2];
        post[i] = s[i][3] + s[i][4] + s[i][5];
    }
    for(int i = n + 1;i <= n + m;i++){
        scanf("%s",s[i]);
        pre[i] = s[i][0] + s[i][1] + s[i][2];
        post[i] = s[i][3] + s[i][4] + s[i][5];
    }
    for(int i = 1;i <= n;i++){
        for(int j = n + 1;j <= n + m;j++){
            if(pre[i] == post[j])
                add_edge(i,j);
            else if(pre[j] == post[i])
                add_edge(i,j);
        }
    }
    int ans = bipartite_matching();
    printf("%d\n",ans);
    for(int i = 1;i <= n;i++){
        int v = match[i];
        if(v < 0 || match[v] != i) continue;
        if(pre[i] == post[v])
            printf("AT %s %s\n",s + i,s + v);
        else printf("TA %s %s\n",s + v,s + i);
    }
    return 0;
}
