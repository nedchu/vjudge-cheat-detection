#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
map<int, int> have;
int p[N], k, w[N], vis[N], cnt;
char s[N];
vector<int> g[N];

struct node {
    int l, r;
    char c;
}a[N * N];

void process(char* s) {
    ++k;
    int n = strlen(s);
    int cur = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '>' || s[i] == '<' || s[i] == '=') {
            a[k].l = cur;
            cur = 0;
            a[k].c = s[i];
            continue;
        }
        cur = cur * 10 + s[i] - '0';
    }
    a[k].r = cur;
}

int find(int x) {
    return p[x] == x ? x : p[x] = find(p[x]);
}

int in[N],out[N];

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) p[i] = i;
    for (int i = 0; i < m; ++i) {
        scanf("%s", s);
        process(s);
        if (a[k].c == '=') {
            int x = find(a[k].l), y = find(a[k].r);
            if (x != y)
                p[x] = y;
        }
    }
    for (int i = 1; i <= k; ++i) {
        int l, r;
        if (a[i].c == '<') {
            l = a[i].l, r = a[i].r;
        } else {
            l = a[i].r, r = a[i].l;
        }
        if (a[i].c == '=') continue;
        r = find(r);
        l = find(l);
        g[r].push_back(l);
        in[l]++;
        out[r]++;
    }
    for (int i = 1; i <= n; ++i)
        if (in[i]>0&&out[i]>0) w[i]=2;

    for (int i = 1; i <= k; ++i) {
        int l, r;
        if (a[i].c == '<') {
            l = a[i].l, r = a[i].r;
        } else {
            l = a[i].r, r = a[i].l;
        }
        if (a[i].c == '=') continue;
        r = find(r);
        l = find(l);
        if (w[l]==2) w[r]=1;
        if (w[r]==2) w[l]=3;
    }
    for (int i = 1; i <= n; ++i) {
        int fa = find(i);
        if (w[fa] == 0) putchar('?');
        if (w[fa] == 1) putchar('W');
        if (w[fa] == 2) putchar('R');
        if (w[fa] == 3) putchar('B');
    }
    puts("");
    return 0;
}
