#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

LL ans,n;

int main()
{
	LL i;
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%lld",&n);
	ans=8; 
	if (n<10) 
	{
		for (i=1; i<=n-1; i++)ans*=9;
		printf("%lld\n",ans);
	}
	else
	{
		for (i=1; i<=8; i++)ans*=9;
		printf("%lld",ans);
		for (i=10; i<=n; i++)printf("0");
	}
	return 0;
}