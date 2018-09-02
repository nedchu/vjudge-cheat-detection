#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
	ll res = 8; int n;
	cin >> n;
	if (n <= 9){
		for (int i=2; i<=n; ++i) res *= 9;
		cout << res << endl;
	}else{
		for (int i=2; i<=9; ++i)
			res *= 9;
		cout << res;
		for (int i=10; i<=n; ++i)
		cout << '0';
		cout << endl;
	}
    return 0;
}