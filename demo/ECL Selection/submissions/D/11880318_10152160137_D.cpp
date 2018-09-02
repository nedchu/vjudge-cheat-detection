#include<bits/stdc++.h>

using namespace std;
const int MOD = 1e9+7;
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
	long long ans = 1;
	string s;
	cin >> s;
	int len = s.length();
	for(int i = 0; i < len; i++){
		char ch = s[i];
		if(ch == 'N'){
			if(s[i+1] == 'W' || s[i+1] == 'E'){
				ans = ( ans * 2 ) % MOD;
				i++;
			}
		}
		else if(ch == 'S'){
			if(s[i+1] == 'W' || s[i+1] == 'E'){
				ans = ( ans * 2 ) % MOD;
				i++;
			}
		}
	}
	cout << ans << endl;
    return 0;
}