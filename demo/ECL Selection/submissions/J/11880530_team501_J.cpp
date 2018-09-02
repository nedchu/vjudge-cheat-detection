#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 111;
int n, m;
int g[N][N], link[N], vis[N];
char a[N][10], b[N][10];

bool dfs(int u) {
    for (int v = 1; v <= m; ++v) {
        if (g[u][v] && !vis[v]) {
            vis[v] = 1;
            if (link[v] == -1 || dfs(link[v])) {
                link[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

int MaxMatch() {
    int ret = 0;
    memset(link, -1, sizeof link);
    for (int u = 1; u <= n; ++u) {
        memset(vis, 0, sizeof vis);
        if (dfs(u))
            ++ret;
    }
    return ret;
}

int judge(int i, int j) {
    int L = a[i][0] + a[i][1] + a[i][2] - 3 * '0';
    int R = b[j][3] + b[j][4] + b[j][5] - 3 * '0';
    if (L == R) return 1;
    L = a[i][3] + a[i][4] + a[i][5] - 3 * '0';
    R = b[j][0] + b[j][1] + b[j][2] - 3 * '0';
    if (L == R) return 2;
    return 0;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%s", a[i]);
    for (int i = 1; i <= m; ++i)
        scanf("%s", b[i]);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (judge(i, j) > 0)
                g[i][j] = 1;
    int k = MaxMatch();
    printf("%d\n", k);
    for (int i = 1; i <= m; ++i) {
        if (link[i] != -1) {
            int u = link[i], v = i;
            if (judge(u, v) == 1)
                printf("AT %s %s\n", a[u], b[v]);
            else
                printf("TA %s %s\n", b[v], a[u]);
        }
    }
    return 0;
}
