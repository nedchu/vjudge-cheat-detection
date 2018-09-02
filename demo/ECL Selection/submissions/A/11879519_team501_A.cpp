#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, k;
    scanf("%d%d", &n, &k);
    if(k>=n) {
        puts("2");
    } else {
        printf("%d\n", (n*2+k-1)/k);
    }
    return 0;
}
