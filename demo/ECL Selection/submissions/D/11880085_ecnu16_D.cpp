#include <bits/stdc++.h>
using namespace std;

const int modn = 1e9 + 7;
const int N = 1e5 + 10;
char s[N];
int n, dp[N];
char p[][4] = {"N", "NW", "W", "SW", "S", "SE", "E", "NE"};

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%s", s + 1);
    n = strlen(s + 1);
    dp[0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 8; ++j) {
            int pl = strlen(p[j]);
            if (strncmp(s + i + 1, p[j], pl) == 0) {
//                printf("%d %d %d\n", i, j, i+pl);
                (dp[i + pl] += dp[i]) %= modn;
//                printf("dp[%d]=%d\n", i+pl, dp[i+pl]);
            }
        }
    }
//    for (int i = 0; i <= n; ++i)
//        printf("%d\n", dp[i]);
    printf("%d\n", dp[n]);
}