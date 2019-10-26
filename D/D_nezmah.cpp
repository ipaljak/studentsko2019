#include<bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
const int LOG = 20;

int n, k, ofs = (1 << 17), tot;
int x[MAXN], y[MAXN], a[MAXN];
int g[2][MAXN], t[MAXN * 4], upd[MAXN];
int sol[MAXN], bt[LOG], rep[LOG];
vector <int> v[MAXN], basis;

void update (int pos, int val) {
    pos += ofs;
    t[pos] = max(t[pos], val);
    pos /= 2;
    while (pos > 0) {
        t[pos] = max(t[pos * 2], t[pos * 2 + 1]);
        pos /= 2;
    }
}

int upit (int x, int from, int to, int lo, int hi) {
    if (from <= lo && hi <= to) return t[x];
    if (to < lo || hi < from) return -1;
    return max(upit(2*x, from, to, lo, (lo + hi) / 2), upit(2*x+1, from, to, (lo + hi) / 2 + 1, hi));
}

void precompute_grundy () {
    for (int cx = 0; cx < MAXN; cx++) {
        for (auto i : v[cx]) {
            int h = (i > 0 ? y[i] : x[-i]) - 1;
            if (h < y[upd[cx]]) g[i < 0][abs(i)] = upit(1, 0, h, 0, ofs - 1) + 1;
        }
        if (upd[cx] != 0) update(y[upd[cx]], g[0][upd[cx]]);
        for (auto i : v[cx]) {
            int h = (i > 0 ? y[i] : x[-i]) - 1;
            if (h >= y[upd[cx]]) g[i < 0][abs(i)] = upit(1, 0, h, 0, ofs - 1) + 1;
        }
    }
}

void ubaci (int ind, int val) {
    int siz = basis.size();
    int mask = (1 << siz);
    for (int i = 0; i < LOG; i++) {
        if ((val & (1 << i)) == 0) continue;
        if (!bt[i]) {
            basis.push_back(ind);
            bt[i] = val;
            rep[i] = mask;
            return;
        }
        val ^= bt[i];
        mask ^= rep[i];
    }
}

void ispis (int val) {
    int mask = 0;
    for (int i = 0; i < LOG; i++) {
        if ((val & (1 << i)) == 0) continue;
        if (!bt[i]) {
            cout << "nemoguce\n";
            return;
        }
        val ^= bt[i];
        mask ^= rep[i];
    }
    for (int i = 0; i < LOG; i++) {
        if (mask & (1 << i)) sol[basis[i]] = 1;
    }
    for (int i = 1; i <= k; i++) cout << sol[i];
	cout << "\n";
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    memset(t, -1, sizeof t);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
        upd[x[i]] = i;
        v[x[i] - 1].push_back(i);
        v[y[i] - 1].push_back(-i);
    }
    precompute_grundy();
    //for(int i = 1;i <= n;i++)
    //	printf("%d %d\n", g[0][i], g[1][i]);
    for (int i = 1; i <= k; i++) {
        cin >> a[i];
        int lef = g[0][a[i]], rig = g[1][a[i]];
        tot ^= lef;
        if (lef != rig) ubaci(i, lef ^ rig);
    }
    ispis(tot);
    return 0;
}
