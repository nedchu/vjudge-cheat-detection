#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 10;
int is_prime[N];

bool is_prime_too(int n) {
    int sqr = (int) sqrt(n + 0.5);
    for (int i = 2; i <= sqr; ++i)
        if (n % i == 0)
            return false;
    return true;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    for (int i = 2; i < N; ++i)
        is_prime[i] = 1;
    for (int i = 2; i < N; ++i) {
        if (is_prime[i]) {
            for (int j = i + i; j < N; j += i)
                is_prime[j] = 0;
        }
    }
    int n; cin >> n;
    for (int i = 2; i < N; ++i)
        for (int j = i + 1; j < N; ++j)
        if (is_prime[i] && is_prime[j]) {
            int t = i * j;
            if (n % t == 0) {
                int u = n / t;
                if (u <= j) continue;
                if (is_prime_too(u)) {
//                    printf("%d %d %d\n", i, j, u);
                    puts("YES");
                    return 0;
                }
            }
        }
    puts("NO");
}
