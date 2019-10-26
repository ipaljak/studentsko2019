#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

#define X first
#define Y second
#define PB push_back


using namespace std;

typedef pair < int, int > pii;

const int N = 1e6 + 500;

int col[N], n, gdje[N];

int main(){
	scanf("%d", &n);
	for(int i = 0;i < n;i++){
		int x, y; scanf("%d%d", &x, &y);
		col[--x] = 2, col[--y] = 2;
		gdje[x] = y, gdje[y] = x;
	}
	for(int i = 0;i < 2 * n;i++){
		if(col[i] < 2) continue;
		if(i >= 2 && col[i - 2] == col[i - 1])
			col[i] = rand() % 2;
		else if(i < 2)
			col[i] = rand() % 2;
		else
			col[i] = !col[i - 1];
		col[gdje[i]] = !col[i];
	}
	
	for(int i = 0;i < 2 * n;i++)
		printf("%c", 'A' + col[i]);
	printf("\n");
	return 0;
}
