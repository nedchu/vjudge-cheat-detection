#include<bits/stdc++.h>
using namespace std;
int n;
int cnt, p[200010];
bool is[200010];
const int N = 200000;
int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	for (int i=2; i<=N; ++i){
		if (!is[i]){
			p[cnt++] = i;
			for (int j=2*i; j<=N; j+=i)
				is[j] = true;
		}
	}
	scanf("%d", &n);
	bool ans = true;
	int c = 0;
	for (int i=0; i<cnt; ++i){
		if (n%p[i] == 0){
			++c; n/=p[i];
//			printf("%d\n", p[i]);
			if (c > 3){
				ans = false;
				break;
			}
			if (n%p[i] == 0){
				ans = false;
				break;
			}
		}
	}
	if (!ans){
		printf("NO\n");
	}else{
		if ((c == 2 && n>1) || (c == 3 && n == 1)){
			printf("YES\n");
		}else{
			printf("NO\n");
		}
	}
	return 0;
} 
			 
	