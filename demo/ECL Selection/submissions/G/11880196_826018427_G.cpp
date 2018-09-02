#include <iostream>
#include <vector>
#include <cstdio>
#include <stack>
#include <cstring>
#include <algorithm>
#include <queue>
#include <map>
#include <string>
#include <cmath>
#include <bitset>
#include <iomanip>
#include <set>
using namespace std;

int main()
{
    freopen("Input.txt","r",stdin);freopen("Output.txt","w",stdout);
    bool correct=true;
    int n,primenum=0;
    scanf("%d",&n);
    for (int i=2;i*i<=n;i++)
    if (n%i==0){
        primenum++;
        if (primenum>3){
            correct=false;
            break;
        }
        n/=i;
        if (n%i==0){
            correct=false;
            break;
        }
    }
    if (correct&&n!=1){
        primenum++;
    }
    if (primenum!=3) correct=false;
    if (correct) printf("YES\n");else printf("NO\n");
    return 0;
}