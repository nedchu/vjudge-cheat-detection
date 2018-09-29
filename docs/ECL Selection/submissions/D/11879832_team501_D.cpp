#include <bits/stdc++.h>
#define LL long long
using namespace std;
const LL mod = 1e9 + 7;
string s;

int check(int i) {
    if (s[i] == 'N' && s[i + 1] == 'E') return 1;
    if (s[i] == 'N' && s[i + 1] == 'W') return 1;
    if (s[i] == 'S' && s[i + 1] == 'E') return 1;
    if (s[i] == 'S' && s[i + 1] == 'W') return 1;
    return 0;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> s;
    int n = s.size();
    LL ans = 1;
    for (int i = 0; i < n - 1; ++i)
        if (check(i))
            ans = (ans * 2) % mod;
    cout << ans << endl;
    return 0;
}
