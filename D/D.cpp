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

typedef pair < int, bool > pib;

const int N = 2e5 + 500;
const int LOG = 20;

int n, k, S[N], D[N];			 // unos
int tlo[N], grun[N], loga[N];    // racunanje Grundy-a
int bz[LOG], ind[LOG];			 // racunanje Gauss-a
int sol[N], pmt[N];						 // ispis
vector < int >  v, baza;

bool cmp(const int &A, const int &B){
	if(S[A] != S[B]) 
		return S[A] < S[B];
	if(D[A] == D[B])
		return A > B;
	return D[A] > D[B];
}

void add(int x,int y){ x += 10;
	for(; x < N; x += x & -x)
		loga[x] = max(loga[x], y + 1);
}

int get(int x){ x += 10;
	int ret = 0;
	for(; x ; x -= x & -x)
		ret = max(loga[x], ret);
	return ret - 1;
}

void ubaci(int msk,int koj){
	pmt[koj] = msk;
	for(int i = 0;i < LOG;i++){
		if(!(msk & (1 << i))) continue;
		if(!bz[i]){
			bz[i] = msk;
			baza.PB(koj);
			return;
		}
		msk ^= bz[i];
	}
}

int main(){
	memset(bz, 0, sizeof(bz));
	scanf("%d%d", &n, &k);
	for(int i = 0;i < n;i++){
		scanf("%d%d", S + i, D + i);
		D[n + i] = S[i], S[n + i] = D[i];
		v.PB(i); v.PB(n + i);
	}
	sort(v.begin(), v.end(), cmp);
	for(int i = 0;i < 2 * n;i++){
		//if(v[i] >= n) continue;
		grun[v[i]] = get(D[v[i]] - 1) + 1;
		if(v[i] < n)
			add(D[v[i]], grun[v[i]]);
	}
	//for(int i = 0;i < n;i++){
	//	printf("%d %d\n", grun[i], grun[n + i]);
	//}
	int zl = 0;
	for(int i = 0;i < k;i++){
		int x; scanf("%d", &x);x--;
		ubaci(grun[x] ^ grun[n + x], i); 
		zl ^= grun[x];
	}
	int naso = 0;
	for(int msk = 0;msk < (1 << (int)baza.size());msk++){
		int cur = 0;
		for(int i = 0;i < (int)baza.size();i++){
			if(msk & (1 << i))
				cur ^= pmt[baza[i]];
		}
		if(cur == zl){
			for(int i = 0;i < (int)baza.size();i++)
				if(msk & (1 << i)) sol[baza[i]] = 1;
			naso = 1;
			break;
		}
	}		
	if(!naso){
		printf("nemoguce\n");
		return 0;
	}
	for(int i = 0;i < k;i++)
		printf("%d", sol[i]);
	printf("\n");
	return 0;
}







