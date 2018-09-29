#include <bits/stdc++.h>

using namespace std;
const int Maxn = 1e5 + 5;
typedef long long LL;
LL a[Maxn] = {};
void output(LL t){
    if (t) cout << "YES" << endl;
    else cout << "KEK" << endl;
    exit(0);
}
int main()
{
    LL n, k;
    freopen ("input.txt", "r", stdin);
    freopen ("output.txt", "w", stdout);
    while (cin >> n >> k){
        LL ma = 0, manum = 0;
        for (LL i = 1; i <= n; i++){
            scanf("%I64d", &a[i]);
            if (a[i] > ma) ma = a[i], manum = i;
        }
        if (manum - 1 > k) output(0);
        LL sum = 0;
        for (LL i = 1; i < manum; i++){
            sum += a[i];
        }
        if (sum >= k) output(1);
        LL l = manum - 1, r = sum;
        sum = 0;
        for (LL i = 1; i <= n; i++){
            sum += a[i];
        }
        LL x = n - 1 + ma, y = sum;
        //cout << l << " " << x << " " << r << " " << y << endl;
        //cout << (k - l - 1) / x << " " << (k - r - 1) / y << endl;
        if ((k - l) / x > (k - r - 1) / y) output(1);
        else output(0);
    }
    return 0;
}
