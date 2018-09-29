#include <bits/stdc++.h>
using namespace std;

int h, w;
vector<pair<int,int> > ans;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int h, w; cin >> h >> w;
    if (h == 1 || w == 1) {
        puts("0");
        return 0;
    } else {
        if (h % 2 == 0) {
            for (int i = 1; i <= h; i += 2) {
                for (int j = 1; j <= w - 1; j++)
                    ans.push_back({i, j});
                if (i + 2 <= h) ans.push_back({i + 1, w - 1});
            }
        } else {
            for (int i = 1; i <= h - 3; i += 2) {
                for (int j = 1; j <= w - 1; j++)
                    ans.push_back({i, j});
                if (i + 2 <= h) ans.push_back({i + 1, w - 1});
            }
            for (int j = 1; j <= w - 1; j += 2) {
                ans.push_back({h - 2, j});
                ans.push_back({h - 1, j});
                if (j + 2 <= w) ans.push_back({h - 1, j + 1});
            }
        }
        cout << ans.size() << endl;
        for (pair<int, int> p: ans)
            printf("%d %d\n", p.first, p.second);
    }
}
