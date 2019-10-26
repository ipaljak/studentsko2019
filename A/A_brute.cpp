#include <cstdio>
#include <vector>

#define X first
#define Y second
#define PB push_back

using namespace std;

typedef pair < int , int > pii;
typedef long long ll;

const int N = 1e5 + 500;

int cur = 0, n, st[N], mi[N];
ll ans = 0;
vector < pii > v[N];

void dfs(int x, int lst,int lim){
	//printf("x = %d\n", x);
	for(pii nxt : v[x])
		if(nxt.Y >= lim && lst != nxt.X)
			cur++, dfs(nxt.X, x, lim);
}



int main(){
	scanf("%d", &n);
	for(int i = 1;i < n;i++){
		int x, y, w; scanf("%d%d%d", &x, &y, &w);
		v[x].PB({y, w}), v[y].PB({x, w});
		st[i] = x, mi[i] = w;
	}
	for(int i = 1;i < n;i++){
		//printf("start %d %d\n", st[i], mi[i]);
		dfs(st[i], st[i], mi[i]);
		ans = max(ans, (ll)mi[i] * cur); 
		cur = 0;
	}
	printf("%lld\n", ans);
}
