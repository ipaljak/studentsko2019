#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

#define PB push_back

using namespace std;

typedef long long ll;

const int ALP = 26;
const int N = 105;
const int MOD = 1e9 + 7;

int n, T;
vector < string > v, kraj;
int res[N][N], pom[N][N], mat[N][N], gotov[N];

bool match(string x, string y){
	if((int)y.size() > (int)x.size()) return 0;
	for(int i = 1;i <= (int)y.size();i++)
		if(y[(int)y.size() - i] != x[(int)x.size() - i])
			return 0;
	return 1;
}

inline int add(const int &A,const int &B){
    if(A + B >= MOD) return A + B - MOD;
    return A + B;
}

inline int mul(const int &A, const int &B){
    return (ll)A * (ll)B % (ll)MOD;
}

void kvadriraj(){
    memset(pom, 0, sizeof(pom));
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            for(int k = 0;k < n;k++){
                pom[i][j] = add(pom[i][j], mul(mat[i][k], mat[k][j]));
            }
        }
    }
    for(int i = 0;i < n;i++)
        for(int j = 0;j < n;j++)
            mat[i][j] = pom[i][j];
}

void dodaj(){
    memset(pom, 0, sizeof(pom));
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            for(int k = 0;k<n;k++){
                pom[i][j] = add(pom[i][j], mul(mat[i][k], res[k][j]));
            }
        }
    }
    for(int i = 0;i < n;i++)
        for(int j = 0;j < n;j++)
            res[i][j] = pom[i][j];
}


void potenciraj(){
    for(int i = 0;i < n;i++) res[i][i] = 1;
    for(;T > 0; T /= 2){
        if(T & 1) dodaj();
        kvadriraj();
    }
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> T;
	for(int i = 0;i < n;i++){
		string s; cin >> s;
		string cur = "";
		for(int i = 0;i < (int)s.size();i++)
			cur.PB(s[i]), v.PB(cur);
		kraj.PB(cur);
	}
	v.PB("");
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	for(string s : kraj){
		gotov[lower_bound(v.begin(), v.end(), s) - v.begin()] = 1;
	}
	n = (int)v.size();
	for(int _ = 0;_ < 3;_++)
		for(int i = 0;i < n;i++)
			for(int j = 0;j < n;j++)
				if(gotov[j] && match(v[i], v[j])) gotov[i] = 1;
	for(int i = 0;i < n;i++){
		if(gotov[i]) continue;
		for(char c = 'a'; c < 'a' + ALP;c++){
			int cur = 0;
			for(int j = 1;j < n;j++){
				string nw = v[i]; nw.PB(c);
				if(v[j].size() > v[cur].size() && match(nw, v[j]))
					cur = j;
			}
			mat[i][cur]++;
		}
	}
	potenciraj();
	int sol = 0;
	for(int i = 0;i < n;i++)
		if(!gotov[i]) sol = add(sol, res[0][i]);
	printf("%d\n", sol);
}
