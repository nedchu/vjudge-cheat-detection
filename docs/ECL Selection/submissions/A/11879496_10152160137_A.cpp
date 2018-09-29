#include <bits/stdc++.h>
using namespace std;


int main(){
	freopen("input.txt","r", stdin);
	freopen("output.txt","w", stdout);
	int n,k;
	cin >> n >> k;
	if(n <= k) cout << 2 << endl;
	else{
		cout << ceil(2.0*n / k) << endl;
	}
	return 0;
}