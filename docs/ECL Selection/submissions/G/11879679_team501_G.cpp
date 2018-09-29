#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

bool check(int n) {
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0)
            return 0;
    return 1;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    cin >> n;
    int a = -1, b = -1;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0 && check(i)) {
            if (a == -1)
                a = i;
            else if (b == -1)
                b = i;
        }
        if (a != -1 && b != -1) break;
    }
    n /= a;
    n /= b;
    if (a == -1 || b == -1) puts("NO");
    else if (check(n) && n != a && n != b) puts("YES");
    else puts("NO");
    return 0;
}
