#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 1e5+10;

int a[N];
ll sum0, sum1;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n, k;
	scanf("%d%d", &n, &k);
	int vk = 0;
	for(int i = 1; i<=n; ++i) {
		scanf("%d", a+i);
		if(a[i]>a[vk]) vk = i;
	}
	for(int i = 1; i<vk; ++i) sum0+=a[i];
	sum1 = sum0;
	for(int i = vk+1; i<=n; ++i)sum1+=a[i];
	ll minv = vk-1, maxv = sum0;
	int t = (k-maxv)/(sum1+a[vk]);
	if(t>0) {
		minv+=1LL*t*(n-1+a[vk]);
		maxv+=1LL*t*(sum1+a[vk]);
	}
	while(maxv<k) {
		minv+=n-1+a[vk];
		maxv+=sum1+a[vk];
	}
	if(minv<=k) {
		puts("YES");
	} else puts("KEK");
	return 0;
} 