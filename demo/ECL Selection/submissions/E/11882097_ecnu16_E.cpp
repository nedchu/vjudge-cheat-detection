#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
typedef long long LL;

int n, k;
int a[N];
LL s[N];

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> n >> k;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    int x = 1;
    for (int i = 1; i <= n; ++i)
        if (a[i] > a[x]) x = i;
    int xx = a[x];
    for (int i = 1; i <= n; ++i)
        s[i] = s[i - 1] + a[i];
    LL lb = x - 1, ub = s[x - 1];
    LL lb2 = n - 1, ub2 = s[n] - xx;
    for (int round = 1; ; ++round) {
        LL L = lb + lb2 * (round - 1) + 1LL * (round - 1) * xx;
        LL R = ub + ub2 * (round - 1) + 1LL * (round - 1) * xx;
        if (L <= k && R >= k) {
            puts("YES");
            return 0;
        } else if (L > k)
            break;
    }
    puts("KEK");
    return 0;
}
