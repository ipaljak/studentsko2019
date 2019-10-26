#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstring>
 
#define PB push_back
 
using namespace std;
 
typedef long long ll;
 
const int N = 1e6 + 500;
const int MOD = 998244353;
const int INF = 0x3f3f3f3f;

inline int add(const int &A, const int &B){
	if(A + B >= MOD) return A + B - MOD;
	return A + B;
}

inline int mul(const int &A, const int &B){
	return (ll)A * B % MOD;
}

inline int sub(const int &A, const int &B){
	if(A - B < 0) return A - B + MOD;
	return A - B;
}

inline int pot(const int &A, int B){
	int cur = A, ret = 1;
	for(;B;B >>= 1){
		if(B & 1) ret = mul(ret, cur);
		cur = mul(cur, cur);
	}
	return ret;
}

struct node{
    node* CH[30];
    node* bk;
    node* par;
    int len, cnt, dp0, dp1, dp2, dp3, odu;
} *n0, *n1;
 
bool cmp(node* X, node* Y){
    return X -> len > Y -> len;
}
 
char s[N];
int n, sol;
ll mx;
vector < node* > v;

void obradi(node* cur){
	cur -> dp1 = add(1 , cur -> par -> dp3);
	cur -> dp2 = add(cur -> bk -> dp0, cur -> bk -> dp0);	
	cur -> dp0 = add(cur -> bk -> dp0, cur -> dp1);
	cur -> dp3 = add(add(cur -> par -> dp3, cur -> dp1), cur -> dp2);
}
 
void precompute(){
    n1 = new node(); n0 = new node();
    n1 -> len = -1, n0 -> len = 0;
    n0 -> bk = n1; n1 -> bk = n1;
    node* cur = n0;
    for(int i = 0;i < n;i++){
        for(; cur->len + 1 > i || s[i - cur->len - 1] != s[i]; cur = cur -> bk);
        node *rmb = cur -> bk;
        if(cur -> CH[s[i] - 'a'] == NULL){
            cur -> CH[s[i] - 'a'] = new node();
            cur -> CH[s[i] - 'a'] -> par = cur;
        	v.PB(cur -> CH[s[i] - 'a']);
        }
        cur -> CH[s[i] - 'a'] -> len = cur -> len + 2;
        cur = cur -> CH[s[i] - 'a'];
        cur -> cnt++;
        for(; rmb -> len + 1 > i || s[i - rmb->len - 1] != s[i]; rmb = rmb -> bk);
        if(cur -> len == 1)
            cur -> bk = n0;
        else{
            if(rmb -> CH[s[i] - 'a'] == NULL)
                rmb -> CH[s[i] - 'a'] = new node(), v.PB(rmb -> CH[s[i] - 'a']);
            cur -> bk = rmb -> CH[s[i] - 'a'];
        }
        if(cur -> cnt == 1)
        	obradi(cur);
    }
}
 
 
 
int main(){
    scanf("%s", s);
    n = strlen(s);
    precompute();
    reverse(v.begin(), v.end());
    for(node* x : v){
 		x -> bk -> cnt += x -> cnt;   
 		//printf("len = %d dp 0: %d 1: %d 2: %d\n", x -> len, x -> dp0, x -> dp1, x -> dp2);
		sol = add(mul(x -> cnt , x -> dp1), sol);
    }
    printf("%d\n", sol);
}




