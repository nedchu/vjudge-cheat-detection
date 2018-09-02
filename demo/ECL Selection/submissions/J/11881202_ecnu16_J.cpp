#include <bits/stdc++.h>
using namespace std;
const int N = 1000;

int n, m;
vector<int> g[N];
int a[N], b[N];
int from[N], tot, use[N];

bool match(int x) {
    for (int v: g[x]) {
        if (!use[v]) {
            use[v] = 1;
            if (from[v] == -1 || match(from[v])) {
                from[v] = x;
                return 1;
            }
        }
    }
    return 0;
}

int hungary() {
    tot = 0;
    memset(from, -1, sizeof from);
    for (int i = 1; i <= n; ++i) {
        memset(use, 0, sizeof use);
        if (match(i)) ++tot;
    }
    return tot;
}

int ok(int a, int b) {
    if ((a / 100000) + (a / 10000) % 10 + (a / 1000) % 10 ==
        (b / 100) % 10 + (b / 10) % 10 + b % 10)
        return 1;
    return 0;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = 1; i <= m; ++i)
        cin >> b[i];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (ok(a[i], b[j]) || ok(b[j], a[i]))
                g[i].push_back(n + j);
    int ans = hungary();
    cout << ans << endl;
    int tot = 0;
    for (int j = 1; j <= m; ++j) {
        if (from[n + j] != -1) {
            int i = from[n + j];
            if (ok(a[i], b[j])) printf("AT %d %d\n", a[i], b[j]);
            else printf("TA %d %d\n", b[j], a[i]);\
            tot++;
        }
    }
    assert (tot == ans);
}
