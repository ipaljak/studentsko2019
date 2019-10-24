#include<bits/stdc++.h>

using namespace std;

typedef long long llint;

const int MAXN = 300005;

llint sol;
int n, q, brc, brz;
int a[MAXN], fen[2][MAXN];
string s;

void ubaci (int tip, int x, int k) {
    for (x++; x < MAXN; x += x&-x) fen[tip][x] += k;
}

int upit (int tip, int x) {
    int res = 0;
    for (x++; x > 0; x -= x&-x) res += fen[tip][x];
    return res;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q >> s;

    s = '.' + s;
    for (int i = 1; i <= n; i++) {
        if (s[i] == 'C') brc++;
        if (s[i] == 'Z') brz++;
    }
    ubaci(0, 0, brc);
    ubaci(1, 0, brz);

    for (int i = 1; i <= q; i++) {
        int x, d;
        cin >> x >> d;
        int tip = (s[x] == 'Z');

        int delta = upit(!tip, a[x] + d - !tip) - upit(!tip, a[x] - !tip);
        if (tip == 0) sol += delta; else sol -= delta;

        ubaci(tip, a[x], -1);
        a[x] += d;
        ubaci(tip, a[x], 1);

        cout << sol << '\n';
    }
    return 0;
}
