#include<bits/stdc++.h>

using namespace std;

typedef long long llint;

const int MAXN = 1000005;
const int MOD = 998244353;

int n, cnt, suf;
string s;
llint dp[MAXN], sum[MAXN], sol;

struct node {
    int nxt[26];
    int len, suf, par;
    llint br;
} olbat[MAXN];

void init_olbat () {
    cnt = 2; suf = 2;
    olbat[1].len = -1; olbat[1].suf = 1;
    olbat[2].len = 0; olbat[2].suf = 1;
}

void add (int pos) {
    int curr = suf, c = s[pos] - 'a';
    while (1) {
        int len = olbat[curr].len;
        if (pos - 1 - len >= 0 && s[pos - 1 - len] == s[pos]) break;
        curr = olbat[curr].suf;
    }
    if (olbat[curr].nxt[c]) {
        suf = olbat[curr].nxt[c];
        olbat[suf].br++;
        return;
    }

    suf = ++cnt;
    olbat[cnt].len = olbat[curr].len + 2;
    olbat[cnt].br = 1;
    olbat[cnt].par = curr;
    olbat[curr].nxt[c] = cnt;

    if (olbat[cnt].len == 1) {
        olbat[cnt].suf = 2;
        return;
    }

    while (1) {
        curr = olbat[curr].suf;
        int len = olbat[curr].len;
        if (pos - 1 - len >= 0 && s[pos - 1 - len] == s[pos]) {
            olbat[cnt].suf = olbat[curr].nxt[c];
            break;
        }
    }
}

void calc_dp () {
    for (int i = 3; i <= cnt; i++) {
        if (olbat[i].len == 1) {
            dp[i] = 1;
            sum[i] = 1;
            sol = (sol + olbat[i].br) % MOD;
        } else if (olbat[i].len == 2) {
            dp[i] = 3;
            sum[i] = 2;
            sol = (sol + olbat[i].br) % MOD;
        } else {
            dp[i] = (1 + 2 * dp[olbat[i].par] + 2 * sum[olbat[i].suf]) % MOD;
            sum[i] = (1 + dp[olbat[i].par] + sum[olbat[i].suf]) % MOD;
            sol = (sol + (1 + dp[olbat[i].par]) * olbat[i].br) % MOD;
        }
    }
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> s;
    n = s.size();
    init_olbat();

    for (int i = 0; i < n; i++) {
        add(i);
    }
    for (int i = cnt; i > 1; i--) {
        int rod = olbat[i].suf;
        olbat[rod].br = (olbat[rod].br + olbat[i].br) % MOD;
    }
    calc_dp();
    cout << sol;
    return 0;
}
