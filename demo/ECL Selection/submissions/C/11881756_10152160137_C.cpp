#include<bits/stdc++.h>

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
	int h, w;
	//cout << -1 / 2 << endl;
	cin >> h >> w;
	if(h <= 1 || w <= 1){
		cout << "0" << endl;
		return 0;
	}
	cout << (h * w - 2) / 2 << endl;
	if(w % 2 == 1){
		w--;
		for(int i = 1; i < h; i += 2)
			cout << i << " " << w << endl;
	}
	for(int i = h - 1; i > 1; i--)
		for(int j = 1; j < w; j += 2)
			cout << i << " " << j << endl;
	for(int i = w - 1; i >= 1; i--)
		cout << 1 << " " << i << endl;
		
    return 0;
}