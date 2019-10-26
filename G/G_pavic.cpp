#include <cstdio>
#include <vector>

#define PB push_back

using namespace std;

const int N = 1e6 + 500;

vector < int > v[N];
int bio[N], boj[N], n;

void dfs(int x,int lst){
	if(bio[x]) return;
	boj[x] = !boj[lst]; bio[x] = 1;
	for(int y : v[x])
		dfs(y, x);
}

int main(){
	scanf("%d", &n);
	for(int i = 1;i <= n;i++){
		int x, y; scanf("%d%d", &x, &y);
		v[x].PB(y); v[y].PB(x);
	}
	for(int i = 1;i <= n;i++){
		v[2 * i - 1].PB(2 * i);
		v[2 * i].PB(2 * i - 1);
	}
	for(int i = 1;i <= 2 * n;i++)
		if(!bio[i]) dfs(i, i);
	for(int i = 1;i <= 2 * n;i++)
		printf("%c", 'A' + !boj[i]);
	printf("\n");
	return 0;
}




