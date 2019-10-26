#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>

#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>

#define X first
#define Y second
#define PB push_back


using namespace std;

typedef long long ll;
typedef pair < int, int > pii;

const int N = 1e5 + 500;
int n, par[N], siz[N];
vector < pair < int, pii > > v;

int pr(int x){
	if(x == par[x]) return x;
	return par[x] = pr(par[x]);
}

void mrg(int x,int y){
  x = pr(x), y = pr(y);
	if(x == y) return;
	par[y] = x;
	siz[x] += siz[y];
}

int main(){
	scanf("%d", &n);
	for(int i = 1;i <= n;i++) par[i] = i, siz[i] = 1;
	for(int i = 1;i < n;i++){
		int x, y, z; scanf("%d%d%d", &x, &y, &z);
		v.PB({z, {x, y}});
	}	
	sort(v.rbegin(), v.rend());
	ll sol = 0;
	for(int i = 0;i + 1 < n;i++){
		mrg(v[i].Y.X, v[i].Y.Y);
		sol = max(sol, (ll)v[i].X * (siz[pr(v[i].Y.X)] - 1));
	}
	printf("%lld\n", sol);
	return 0;
}






