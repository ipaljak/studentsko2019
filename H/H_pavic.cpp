#include <cstdio>
#include <cmath>
#include <vector>
#include <complex>

#define X first
#define Y second
#define PB push_back

using namespace std;

typedef long long ll;
typedef pair < int, int > pii;
typedef pair < ll, ll > pt;

const int N = 2e5 + 500;
int a[N], n, nxt;

ll sol[N];
vector < int > st, v[N];
pt hull[N], tko[N];
int gd[N], ol_sz[N], sz, pr[N];


ll f(pt A, ll B){
	return A.X * B + A.Y;
}

ll ccw(pt A, pt B, pt C){
	return A.X * (B.Y - C.Y) + B.X * (C.Y - A.Y) + C.X * (A.Y - B.Y); 
}

inline void ubaci(pt A,int i){
	int lo = 0, hi = sz - 1;
	ol_sz[i] = sz;
	while(lo < hi){
		int mi = (lo + hi) / 2;
		if(ccw(hull[mi], hull[mi + 1], A) >= 0)
			hi = mi;
		else
			lo = mi + 1;
	}
	sz = hi + 2;
	tko[i] = hull[sz - 1];
	hull[sz - 1] = A;
	gd[i] = sz - 1;
}

inline void makni(int i){
	hull[gd[i]] = tko[i];
	sz = ol_sz[i];
}

inline ll get(int x){
	int lo = 0, hi = sz - 1;
	while(lo < hi){
		int mi = (lo + hi) / 2;
		if(f(hull[mi], x) < f(hull[mi + 1], x))
			lo = mi + 1;
		else
			hi = mi;
	}
	return f(hull[lo], x);
}

void dfs(int i){
	ubaci({a[i], -(ll)(pr[i] + 1) * a[i]}, i);
	sol[i] = get(i + 1);
	for(int nxt : v[i])
		dfs(nxt);
	makni(i);
}


int main(){
	scanf("%d", &n);
	st.PB(n);
	for(int i = 0;i < n;i++){
		scanf("%d", a + i);
		while(a[i] <= a[st.back()]) st.pop_back();
		v[st.back()].PB(i); pr[i] = st.back();
		if(pr[i] == n) pr[i] = -1;
		st.PB(i); 
	}
	dfs(n);

	for(int i = 0;i < n;i++){
		if(i) sol[i] = max(sol[i], sol[i - 1]);
		printf("%lld ", sol[i]);
	}
	printf("\n");
	return 0;
}




