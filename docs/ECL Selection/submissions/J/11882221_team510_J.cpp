#include<bits/stdc++.h>
using namespace std;
const int N = 105;
int n1a[N], n1b[N], n2a[N], n2b[N];
int x;
int n, m;
int ans1[N*N][2], ans2[N*N][2];
const int INF = 1e9;
struct edge{
    int to, cap, rev, ki;
};
vector<edge> G[5*N];
int level[5*N];
int iter[5*N];

void add_edge(int from, int to, int cap, int ki){
    G[from].push_back((edge){to, cap, G[to].size(), ki});
    G[to].push_back((edge){from, 0, G[from].size()-1, 2});
}
void bfs(int s){
    memset(level, -1, sizeof(level));
    queue<int> que;
    level[s] = 0;
    que.push(s);
    while(!que.empty()){
        int v = que.front(); que.pop();
		for (int i=0; i<G[v].size(); ++i){
			edge &e = G[v][i];
			if (e.cap > 0 && level[e.to] < 0){
				level[e.to] = level[v] + 1;
				que.push(e.to);
			}
		}
    }
}
int dfs(int v, int t, int f){
	if (v == t) return f;
	for (int &i = iter[v]; i<G[v].size(); ++i){
		edge &e = G[v][i];
		if(e.cap>0 && level[v] < level[e.to]){
			int d = dfs(e.to, t, min(f, e.cap));
			if (d > 0){
				e.cap -= d;
				G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
} 
int max_flow(int s, int t){
	int flow = 0;
	for (;;){
		bfs(s);
		if (level[t]<0) return flow;
		memset(iter, 0, sizeof(iter));
		int f;
		while((f = dfs(s, t, INF)) > 0){
			flow += f;
		}
	}
}
int a[N], b[N];
int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i=0; i<n; ++i){
		scanf("%d", &x);
		a[i] = x;
		int s1 = x%10, s2 = x/10%10, s3 = x/100%10;
		n1b[i] = s1+s2*10+s3*100;
		s1 = x/1000%10, s2 = x/10000%10, s3 = x/100000%10;
		n1a[i] = s1+s2*10+s3*100;

	}
	for (int i=0; i<m; ++i){
		scanf("%d", &x);
		b[i] = x;
		int s1 = x%10, s2 = x/10%10, s3 = x/100%10;
		n2b[i] = s1+s2*10+s3*100;
		s1 = x/1000%10, s2 = x/10000%10, s3 = x/100000%10;
		n2a[i] = s1+s2*10+s3*100;
	}
//	for (int i=0; i<n; ++i)
//		printf("%d %d ", n1a[i], n1b[i]);
//	printf("\n");
//	for (int i=0; i<m; ++i)
//		printf("%d %d ", n2a[i], n2b[i]);
	int cnt1 = 0, cnt2 = 0;
	for (int i=0; i<n; ++i){
		for (int j=0; j<m; ++j){
			int s1 = n1a[i]/100 + n1a[i]/10%10 + n1a[i]%10,
			s2 = n2b[j]/100 + n2b[j]/10%10 + n2b[j]%10;
			if (s1 == s2){
				ans1[cnt1][0] = i;
				ans1[cnt1++][1] = j;
			}
			s1 = n1b[i]/100 + n1b[i]/10%10 + n1b[i]%10;
			s2 = n2a[j]/100 + n2a[j]/10%10 + n2a[j]%10;
			if (s1 == s2){
				ans2[cnt2][0] = j;
				ans2[cnt2++][1] = i;
			}
		}
	}
	
//	for (int i=0; i<cnt1; ++i)
//		printf("%d %d\n", ans1[i][0], ans1[i][1]);
//	for (int i=0; i<cnt2; ++i)
//		printf("%d %d\n", ans2[i][0], ans2[i][1]);
	int S = 0, T = n+m+1;
	for (int i=1; i<=n; ++i)
		add_edge(S, i, 1, -1);
	for (int i=n+1; i<=n+m; ++i)
		add_edge(i, T, 1, -1);
//	printf("a=%d b=%d\n", cnt1, cnt2);
	for(int i=0; i<cnt1; ++i){
		int u, v;
		u = ans1[i][0]+1, v = ans1[i][1]+n+1;
		add_edge(u, v, 1, 0);
//		printf("%d %d 0\n", u, v);
	}
	for (int i=0; i<cnt2; ++i){
		int u, v;
		u = ans2[i][0]+n+1; v = ans2[i][1]+1;
		add_edge(v, u, 1, 1);
//		printf("%d %d 1\n", v, u, 1);
	}
	int ans = max_flow(S, T);
	cout << ans << endl;
	for (int i=1; i<=n; ++i){
		for (int j=0; j<G[i].size(); ++j){
			edge &e = G[i][j];
			if (e.to >= n+1 && e.to <= n+m && e.ki != 2 && e.cap == 0){
				if (e.ki == 0)
					printf("AT %d %d\n", a[i-1], b[e.to-1-n]);
				else
					printf("TA %d %d\n", b[e.to-1-n], a[i-1]);
			}
		}
	}
				

	return 0;
}