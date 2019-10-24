#include<bits/stdc++.h>

using namespace std;

typedef long long llint;

const int MAXN = 105;
const int ALFA = 26;
const int LOG = 32;
const int MOD = 1000000007;

int n, m, cnt = 1;
int p[ALFA][MAXN], par[MAXN], last[MAXN], dep[MAXN];
int ima[MAXN], suf[MAXN];
int dp[MAXN][MAXN][LOG * 2 + 10];
vector <int> red;

void ubaci (string s) {
    int len = s.size(), curr = 1;
    for (int i = 0; i < len; i++) {
        int c = s[i] - 'a';
        if (p[c][curr] == 0) {
            p[c][curr] = ++cnt;
            par[p[c][curr]] = curr;
            last[p[c][curr]] = c;
            dep[p[c][curr]] = dep[curr] + 1;
        }
        curr = p[c][curr];
    }
    ima[curr] = 1;
}

bool cmp (int a, int b) {
    return dep[a] < dep[b];
}

void poredaj () {
    for (int i = 1; i <= cnt; i++) red.push_back(i);
    sort(red.begin(), red.end(), cmp);
}

void precompute () {
    for (auto i : red) {
        if (i == 1) continue;
        if (par[i] == 1) {
            suf[i] = 1;
        } else {
            int curr = suf[par[i]];
            while (curr > 1 && p[last[i]][curr] == 0) curr = suf[curr];
            if (p[last[i]][curr] != 0) suf[i] = p[last[i]][curr]; else suf[i] = 1;
        }
    }

    for (auto i : red) {
        if (i == 1) continue;
        ima[i] |= ima[par[i]];
        int curr = suf[i];
        while (curr > 0) {
            ima[i] |= ima[curr];
            for (int j = 0; j < ALFA; j++) {
                if (p[j][i] == 0) p[j][i] = p[j][curr];
            }
            curr = suf[curr];
        }
    }

    for (int i = 1; i <= cnt; i++) {
        for (int j = 0; j < ALFA; j++) {
            if (p[j][i] == 0) p[j][i] = 1;
        }
    }

    for (int i = 1; i <= cnt; i++) {
        dp[i][i][0] = 1;
        if (ima[i]) continue;
        for (int j = 0; j < ALFA; j++) {
            dp[i][p[j][i]][1]++;
        }
    }
}

void mul (int x, int y, int z) {
    for (int i = 1; i <= cnt; i++) {
        for (int j = 1; j <= cnt; j++) {
            int res = 0;
            for (int k = 1; k <= cnt; k++) {
                res = (res + 1LL * dp[i][k][x] * dp[k][j][y]) % MOD;
            }
            dp[i][j][z] = res;
        }
    }
}

void calc () {
    for (int i = 2; i < LOG; i++) {
        mul(i - 1, i - 1, i);
    }

    int ind = LOG;
    mul(0, 0, ind);

    int pot = 1;
    while (m > 0) {
        if (m & 1) {
            mul(ind, pot, ind + 1);
            ind++;
        }
        m /= 2;
        pot++;
    }

    int sol = 0;
    for (int i = 1; i <= cnt; i++) {
        if (!ima[i]) sol = (sol + dp[1][i][ind]) % MOD;
    }
    cout << sol << endl;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        string s; cin >> s;
        ubaci(s);
    }
    poredaj();
    precompute();
    calc();
    return 0;
}
