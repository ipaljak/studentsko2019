#include<bits/stdc++.h>

using namespace std;

const int MAXN = 40005;

int n, q;
int p[MAXN];
bitset <MAXN> bt[MAXN], tmp;

void precompute () {
    for (int i = 1; i <= n; i++) {
        bt[i] = bt[i - 1];
        bt[i][p[i]] = 1;
    }
}

int upit (int ll, int rr) {
    if ((rr - ll + 1) * 2 > n) return 1;
    tmp = bt[rr] ^ bt[ll - 1];
    int sol = MAXN, last = -MAXN;
    for (int i = tmp._Find_first(); i < MAXN; i = tmp._Find_next(i)) {
        sol = min(sol, i - last);
        last = i;
    }
    return sol;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    precompute();
    for (int i = 0; i < q; i++) {
        int ll, rr;
        cin >> ll >> rr;
        cout << upit(ll, rr) << endl;
    }
    return 0;
}
