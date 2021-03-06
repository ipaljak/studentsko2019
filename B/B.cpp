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

typedef pair < int, int > pii;

const int N = 3e4 + 500;
const int OFF = (1 << 15);
const int BUK = 300;

int L[N], R[N], c_l = 0, c_r = 0;
int l[2 * OFF], r[2 * OFF], ans[2 * OFF], ima[2 * OFF];
int n, q, p[N], sol[N], a[N];

bool cmp(const int &A, const int &B){
	if(L[A] / BUK == L[B] / BUK)
		return R[A] < R[B];
	return L[A] < L[B];
}

inline void mrg(int A,int B,int C){
	l[C] = l[A]; r[C] = r[B];
	if(l[C] < 0) l[C] = l[B];
	if(r[B] < 0) r[C] = r[A];
	ans[C] = min(ans[A], ans[B]);
	if(l[B] > 0 && r[A] > 0)
		ans[C] = min(l[B] - r[A], ans[C]);
}

void update(int x,int y){
	x += OFF;
	if(y) l[x] = x, r[x] = x;
	else l[x] = -1, r[x] = -1; 
	for(x /= 2; x ; x /= 2)
		mrg(2 * x, 2 * x + 1, x);
}

void build(){
	for(int i = OFF;i < 2 * OFF;i++) 
		ans[i] = 2 * N, l[i] = -1, r[i] = -1;
	for(int i = OFF - 1; i ;i--){
		mrg(2 * i, 2 * i + 1, i);
	}
}

int solve(int ll,int rr){
	while(ll < c_l) update(a[--c_l], 1);
	while(rr > c_r) update(a[++c_r], 1);
	while(ll > c_l) update(a[c_l++], 0);
	while(rr < c_r) update(a[c_r--], 0);
	return ans[1];
}

int main(){
	scanf("%d%d", &n, &q);
	for(int i = 0;i < n;i++)
		scanf("%d", a + i);
	for(int i = 0;i < q;i++)
		scanf("%d%d", L + i, R + i), p[i] = i;
	sort(p, p + q, cmp);
	build();
	update(a[0], 1);
	for(int i = 0;i < q;i++)
		sol[p[i]] = solve(L[p[i]] - 1, R[p[i]] - 1);
	for(int i = 0;i < q;i++)
		printf("%d\n", sol[i]);
	return 0;
}
